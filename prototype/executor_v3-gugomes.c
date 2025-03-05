/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_v3-gugomes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:32:34 by marvin            #+#    #+#             */
/*   Updated: 2025/03/05 00:52:54 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

// ===================== DECLARAÇÕES DE FUNÇÕES ======================
static void setup_input(int input_fd);
static void setup_output(int pipe_fd[2], int has_next);
static void handle_child(t_msh *msh, int pipe_fd[2],
						 int input_fd, int has_next);
static void handle_parent(int *input_fd, int pipe_fd[2], int has_next);
static void process_command(t_msh *msh, int pipe_fd[2], int *input_fd);
static int apply_redirections(t_command *cmd);
static char *get_command_path(char *cmd, t_list *env);
static char *check_direct_path(char *cmd);
static char **get_paths_from_env(t_list *env_list);
static char *find_command_in_paths(char *cmd, char **paths);
static void free_array(char **array);
static void execute_command(t_command *cmd, t_list *env_vars);
static int is_builtin(t_command *cmd);
static void handle_error(char *message, int exit_code);
static char **ft_lst_to_array(t_list *lst);
static char *check_direct_path(char *cmd);
static char **get_paths_from_env(t_list *env_list);
static char *find_command_in_paths(char *cmd, char **paths);

// ===================== IMPLEMENTAÇÃO DO PIPELINE ======================
static void execute_pipeline(t_msh *msh)
{
	int pipe_fd[2];
	int input_fd;
	int status;

	input_fd = STDIN_FILENO;
	while (msh->commands)
		process_command(msh, pipe_fd, &input_fd);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			msh->last_status = WTERMSIG(status) + 128;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

static void process_command(t_msh *msh, int pipe_fd[2], int *input_fd)
{
	int has_next;
	pid_t pid;

	has_next = (msh->commands->next != NULL);
	if (has_next && pipe(pipe_fd) == -1)
		handle_error("pipe error", 1);
	if (is_builtin((t_command *)msh->commands->content) && !has_next)
	{
		launch_builtin(msh, (t_command *)msh->commands->content);
		msh->commands = msh->commands->next;
		return;
	}
	pid = fork();
	if (pid == 0)
		handle_child(msh, pipe_fd, *input_fd, has_next);
	else
	{
		handle_parent(input_fd, pipe_fd, has_next);
		msh->commands = msh->commands->next;
	}
}

// ===================== MANIPULAÇÃO DE FD ======================
static void setup_input(int input_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}

static void setup_output(int pipe_fd[2], int has_next)
{
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static void handle_child(t_msh *msh, int pipe_fd[2], int input_fd, int has_next)
{
	t_command *cmd;

	cmd = (t_command *)msh->commands->content;
	if (!apply_redirections(cmd))
		exit(1);
	setup_input(input_fd);
	setup_output(pipe_fd, has_next);
	execute_command(cmd, msh->env_vars);
}

static void handle_parent(int *input_fd, int pipe_fd[2], int has_next)
{
	if (has_next)
		close(pipe_fd[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = pipe_fd[0];
}

// ===================== REDIRECIONAMENTOS ======================
static int apply_redirections(t_command *cmd)
{
	t_list *redir_node;
	t_redirection *redir;
	int flags;

	redir_node = cmd->redirections;
	while (redir_node)
	{
		redir = (t_redirection *)redir_node->content;
		if (ft_strncmp(redir->type, ">", 1) == 0)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (ft_strncmp(redir->type, ">>", 2) == 0)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			return (0);
		cmd->output_fd = open(redir->target, flags, 0644);
		if (cmd->output_fd == -1)
			return (perror("minishell"), 0);
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
		redir_node = redir_node->next;
	}
	return (1);
}

// ===================== RESOLUÇÃO DE COMANDOS ======================
static void execute_command(t_command *cmd, t_list *env)
{
	char **envp;
	char **args;
	char *path;

	envp = get_envp(env);
	args = ft_lst_to_array(cmd->arguments);
	path = get_command_path(args[0], env);
	if (execve(path, args, envp) == -1)
		(perror("minishell"), free_array(envp), free(path), free_array(args), exit(126));
}

static char *get_command_path(char *cmd, t_list *env)
{
	char *direct_path;
	char **paths;
	char *command_path;

	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	paths = get_paths_from_env(env);
	if (!paths)
		return (ft_strdup(cmd));
	command_path = find_command_in_paths(cmd, paths);
	if (command_path)
		return (command_path);
	free_array(paths);
	return (ft_strdup(cmd));
}

// ===================== FUNÇÕES AUXILIARES ======================

static char *find_command_in_paths(char *cmd, char **paths)
{
	int i;
	char *full_path;
	char *temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

static char **get_paths_from_env(t_list *env_list)
{
	t_env_var *path_var;

	path_var = get_env_var(env_list, "PATH");
	if (!path_var || !path_var->value)
		return (NULL);
	return (ft_split(path_var->value, ':'));
}

static char *check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static void free_array(char **array)
{
	int i;

	if (!array)
		return;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

static void handle_error(char *message, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

char **ft_lst_to_array(t_list *lst)
{
	char **array;
	int i;
	int size;

	size = ft_lstsize(lst);
	i = 0;
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup((char *)lst->content);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

// ===================== FUNÇÕES BUILTIN (EXEMPLO) ======================
static int is_builtin(t_command *cmd)
{
	char *name;

	if (!cmd->arguments || !cmd->arguments->content)
		return (0);
	name = (char *)cmd->arguments->content;
	if ((ft_strncmp(name, "echo", 4) == 0 && name[4] == '\0') || (ft_strncmp(name, "pwd", 3) == 0 && name[3] == '\0') || (ft_strncmp(name, "cd", 2) == 0 && name[2] == '\0') || (ft_strncmp(name, "env", 3) == 0 && name[3] == '\0') || (ft_strncmp(name, "export", 6) == 0 && name[6] == '\0') || (ft_strncmp(name, "unset", 5) == 0 && name[5] == '\0') || (ft_strncmp(name, "exit", 4) == 0 && name[4] == '\0'))
		return (1);
	return (0);
}

// ===================== MAIN ======================

int main(int argc, char **argv, char **envp)
{
	t_msh msh;

	(void)argc;
	(void)argv;
	init_minishell(&msh, envp);
	if (!msh.env_vars)
		return (1);
	while (1)
	{
		msh.input = readline("\033[0;31mGUGOMES EXECUTOR V3 $ \033[0m");
		if (msh.input == NULL)
			break;
		if (process_input(&msh))
			execute_pipeline(&msh);
		if (!ft_strall(msh.input, ft_isspace))
			add_history(msh.input);
		free_minishell_loop(&msh);
	}
	destroy_minishell(&msh);
	return (0);
}

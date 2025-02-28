/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate-executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:17:31 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/28 06:02:52 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int	is_fd_open(int fd, char *target)
{
	char	*error_message;

	if (fd != -1)
		return (1);
	error_message = ft_strjoin("minishell: ", target);
	if (!error_message)
		perror("minishell: ");
	else
	{
		perror(error_message);
		free(error_message);
	}
	return (0);
}

int	open_output_redirections(t_redirection *redir, int *output_fd)
{
	char	*type;
	int		flags;
	int		fd;

	type = redir->type;
	if (ft_strncmp(type, ">", 1) == 0 && type[1] == '\0')
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (ft_strncmp(type, ">>", 2) == 0 && type[2] == '\0')
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (0);
	fd = open(redir->target, flags, 0644);
	if (!is_fd_open(fd, redir->target))
		return (1);
	*output_fd = fd;
	return (1);
}

int	open_input_redirections(t_redirection *redir, int *input_fd)
{
	char	*type;
	int		fd;

	type = redir->type;
	if (ft_strncmp(type, "<", 1) == 0 && type[1] == '\0')
	{
		fd = open(redir->target, O_RDONLY, 0644);
		if (!is_fd_open(fd, redir->target))
			return (0);
		*input_fd = fd;
	}
	else if (ft_strncmp(type, "<<", 2) == 0 && type[2] == '\0')
		printf("heredoc\n");
	else
		return (0);
	return (1);
}

int	open_redirections(t_command *cmd)
{
	t_list			*redir_list;
	t_redirection	*redir;

	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = (t_redirection *)redir_list->content;
		if (is_input_redirection(redir->type))
		{
			if (cmd->input_fd != -1)
				close(cmd->input_fd);
			if (!open_input_redirections(redir, &cmd->input_fd))
				return (0);
		}
		if (is_output_redirection(redir->type))
		{
			if (cmd->output_fd != -1)
				close(cmd->output_fd);
			if (!open_output_redirections(redir, &cmd->output_fd))
				return (0);
		}
		redir_list = redir_list->next;
	}
	return (1);
}

int	is_builtin(t_command *cmd)
{
	char	*cmd_name;

	if (!cmd->arguments || !cmd->arguments->content)
		return (0);
	cmd_name = (char *)cmd->arguments->content;
	if ((ft_strncmp(cmd_name, "echo", 4) == 0 && cmd_name[4] == '\0')
		|| (ft_strncmp(cmd_name, "pwd", 3) == 0 && cmd_name[3] == '\0')
		|| (ft_strncmp(cmd_name, "cd", 2) == 0 && cmd_name[2] == '\0')
		|| (ft_strncmp(cmd_name, "env", 3) == 0 && cmd_name[3] == '\0')
		|| (ft_strncmp(cmd_name, "export", 6) == 0 && cmd_name[6] == '\0')
		|| (ft_strncmp(cmd_name, "unset", 5) == 0 && cmd_name[5] == '\0')
		|| (ft_strncmp(cmd_name, "exit", 4) == 0 && cmd_name[4] == '\0'))
		return (1);
	return (0);
}

int	backup_fds(t_minish *msh)
{
	msh->saved_fd[0] = dup(STDIN_FILENO);
	if (msh->saved_fd[0] == -1)
	{
		perror("minishell: redirection:");
		return (-1);
	}
	msh->saved_fd[1] = dup(STDOUT_FILENO);
	if (msh->saved_fd[1] == -1)
	{
		perror("minishell: redirection:");
		close(msh->saved_fd[0]);
		return (-1);
	}
	return (1);
}

void	restore_fds(t_minish *msh)
{
	if (msh->saved_fd[0] != -1)
	{
		if (dup2(msh->saved_fd[0], STDIN_FILENO) == -1)
			perror("minishell: restore input:");
		if (close(msh->saved_fd[0]) == -1)
			perror("minishell: close input:");
		msh->saved_fd[0] = -1;
	}
	if (msh->saved_fd[1] != -1)
	{
		if (dup2(msh->saved_fd[1], STDOUT_FILENO) == -1)
			perror("minishell: restore output:");
		if (close(msh->saved_fd[1]) == -1)
			perror("minishell: close output:");
		msh->saved_fd[1] = -1;
	}
}

int	apply_input_redirection(int input_fd)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: input redirection: ");
			return (0);
		}
		if (close(input_fd) == -1)
		{
			perror("minishell: input redirection: ");
			return (0);
		}
	}
	return (1);
}

int	apply_output_redirection(int output_fd)
{
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: output redirection: ");
			return (0);
		}
		if (close(output_fd) == -1)
		{
			perror("minishell: output redirection: ");
			return (0);
		}
	}
	return (1);
}

int	apply_redirections(t_command *cmd)
{
	int	input_fd;
	int	output_fd;

	if (!open_redirections(cmd))
		return (0);
	input_fd = cmd->input_fd;
	output_fd = cmd->output_fd;
	if (!apply_input_redirection(input_fd))
		return (0);
	cmd->input_fd = -1;
	if (!apply_output_redirection(output_fd))
		return (0);
	cmd->output_fd = -1;
	return (1);
}

void	child_process(t_minish *msh, t_list *cmd_node, int pipe_fd[2], int *input_fd,
	int (*launcher)(t_minish *, t_command *))
{
	t_command	*cmd;
	int			exit_code;

	cmd = (t_command *)cmd_node->content;
	if (*input_fd != STDIN_FILENO)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	if (cmd_node->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (!apply_redirections(cmd))
		exit(1);
	exit_code = launcher(msh, cmd);
	destroy_minishell(msh);
	exit(exit_code);
}

void	parent_process(t_list *cmd_node, pid_t pid,
		int *input_fd, int pipe_fd[2])
{
	t_command	*cmd;

	cmd = (t_command *)cmd_node->content;
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd_node->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
	{
		close(pipe_fd[0]);
		*input_fd = STDIN_FILENO;
	}
	cmd->pid = pid;
}

int	launch_process(t_minish *msh, t_list *cmd_node,
		int (*launcher)(t_minish *, t_command *))
{
	static int			input_fd = STDIN_FILENO;
	int					pipe_fd[2];
	pid_t				pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe:");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork:");
		exit(1);
	}
	if (pid == 0)
		child_process(msh, cmd_node, pipe_fd, &input_fd, launcher);
	else
		parent_process(cmd_node, pid, &input_fd, pipe_fd);
	return (1);
}

char	*get_full_path(char *token, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(token, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*search_path(char *path, char *cmd)
{
	char	*token;
	char	*full_path;

	token = ft_strtok(path, ":");
	while (token)
	{
		full_path = get_full_path(token, cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*get_command_path(t_list *env, char *cmd)
{
	t_env_var	*path_env;
	char		*path;
	char		*full_path;

	if (cmd[0] == '/' || ft_strncmp("./", cmd, 2) == 0
		|| ft_strncmp("../", cmd, 2) == 0)
	{
		full_path = ft_strdup(cmd);
		if (!full_path)
			return (NULL);
		return (full_path);
	}
	path_env = get_env_var(env, "PATH");
	if (!path_env || (path_env && !path_env->value))
		return (NULL);
	path = ft_strdup(path_env->value);
	if (!path)
		return (NULL);
	full_path = search_path(path, cmd);
	free(path);
	if (full_path)
		return (full_path);
	return (NULL);
}

void	free_execution(char *path, char **argv, char **envp)
{
	if (argv)
		ft_free_nt_matrix((void **) argv);
	if (envp)
		ft_free_nt_matrix((void **) envp);
	if (path)
		free(path);
}

int is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

int	get_exec_error(char *path, char **argv)
{
	if (argv && argv[0])
		ft_putstr_fd(argv[0], 2);
	else
		ft_putstr_fd("minishell", 2);
	if (!path)
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	if (is_directory(path))
	{
		ft_putendl_fd(": is a directory", 2);
		return (126);
	}
	if (access(path, F_OK) != 0)
	{
		ft_putendl_fd(": no such file or directiory", 2);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putendl_fd(": Permission Denied", 2);
		return (126);
	}
	return (0);
}

int	launch_executable(t_minish *msh, t_command *cmd)
{
	char	**envp;
	char	**argv;
	char	*path;
	int		exit_code;

	envp = get_envp(msh->env_vars);
	argv = get_argv(cmd->arguments);
	if (!argv)
	{
		free_execution(NULL, argv, envp);
		return (0);
	}
	path = get_command_path(msh->env_vars, argv[0]);
	if (!path || execve(path, argv, envp) == -1)
	{
		exit_code = get_exec_error(path, argv);
		free_execution(path, argv, envp);
		return (exit_code);
	}
	return (0);
}

void wait_chilren_process(t_minish *msh, pid_t last_pid,int num_commands)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (i < num_commands)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			perror("minishell: waitpid");
			msh->last_status = 1;
			return ;
		}
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				msh->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				msh->last_status = WTERMSIG(status) + 128;
		}
		i++;
	}
}

int	execute_pipeline(t_minish *msh, int num_commands)
{
	t_list		*cmd_list;
	t_command	*cmd;

	cmd_list = msh->commands;
	while (cmd_list)
	{
		cmd = (t_command *)cmd_list->content;
		if (is_builtin(cmd))
			launch_process(msh, cmd_list, launch_builtin);
		else
			launch_process(msh, cmd_list, launch_executable);
		cmd_list = cmd_list->next;
	}
	wait_chilren_process(msh, cmd->pid, num_commands);
	return (msh->last_status);
}

int	execute_single(t_minish *msh)
{
	t_command	*cmd;
	int			status;

	cmd = (t_command *)msh->commands->content;
	if (is_builtin(cmd))
	{
		if (!backup_fds(msh))
			return (1);
		if (!apply_redirections(cmd))
			return (1);
		status = launch_builtin(msh, cmd);
		restore_fds(msh);
	}
	else
	{
		if (launch_process(msh, msh->commands, launch_executable))
		{
			wait(&status);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
		}
	}
	return (status);
}

int	execute_commands(t_minish *msh)
{
	int	num_commands;
	int	status;

	num_commands = ft_lstsize(msh->commands);
	status = 0;
	if (num_commands == 1)
		status = execute_single(msh);
	else
		status = execute_pipeline(msh, num_commands);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;

	(void)argc;
	(void)argv;
	init_minishell(&msh, envp);
	if (!msh.env_vars)
		return (1);
	while (1)
	{
		msh.input = readline("\033[0;31mUltimate $ \033[0m");
		if (msh.input == NULL)
			break ;
		if (process_input(&msh))
			msh.last_status = execute_commands(&msh);
		if (!ft_strall(msh.input, ft_isspace))
			add_history(msh.input);
		free_minishell_loop(&msh);
	}
	destroy_minishell(&msh);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate-executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:17:31 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/27 18:13:39 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
			return (1);
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

int	init_redirections(t_list *commands)
{
	t_command	*cmd;

	while (commands)
	{
		cmd = (t_command *)commands->content;
		if (!open_redirections(cmd))
			return (0);
		commands = commands->next;
	}
	return (1);
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

void	child_process(t_minish *msh, t_command *cmd, int pipe_fd[2],
	int (*launcher)(t_minish *, t_command *))
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	if (!apply_redirections(cmd))
		exit(1);
	launcher(msh, cmd);
}

void	parent_process(int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
}

int	launch_process(t_minish *msh, t_command *cmd, int (*launcher)(t_minish *, t_command *))
{
	int		pipe_fd[2];
	pid_t	pid;

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
		child_process(msh, cmd, pipe_fd, launcher);
	else
		parent_process(pipe_fd);
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

	path_env = get_env_var(env, "PATH");
	if (!path_env || (path_env && !path_env->value))
		return (ft_strdup(cmd));
	path = ft_strdup(path_env->value);
	if (!path)
		return (NULL);
	full_path = search_path(path, cmd);
	free(path);
	if (full_path)
		return (full_path);
	return (ft_strdup(cmd));
}

void exit_execution(char **argv, char **envp, char *path, int exit_code)
{
	if (exit_code == 1)
	{
		if (argv && argv[0])
			ft_putstr_fd(argv[0], 2);
		else
			ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": fail execution\n", 2);
	}
	if (exit_code == 127)
	{
		if (argv && argv[0])
			ft_putstr_fd(argv[0], 2);
		else
			ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (argv)
		ft_free_nt_matrix((void **) argv);
	if (envp)
		ft_free_nt_matrix((void **) envp);
	if (path)
		free(path);
	exit(exit_code);
}

int	launch_executable(t_minish *msh, t_command *cmd)
{
	char	**envp;
	char	**argv;
	char	*path;

	envp = get_envp(msh->env_vars);
	argv = get_argv(cmd->arguments);
	if (!argv)
	{
		destroy_minishell(msh);
		exit_execution(argv, envp, NULL, 1);
	}
	path = get_command_path(msh->env_vars, argv[0]);
	if (!path)
	{
		destroy_minishell(msh);
		exit_execution(argv, envp, NULL, 127);
	}
	if (execve(path, argv, envp) == -1)
	{
		destroy_minishell(msh);
		perror(argv[0]);
		exit_execution(argv, envp, path, 126);
	}
	return (0);
}

int	execute_single(t_minish *msh)
{
	t_command	*cmd;
	int	status;

	cmd = (t_command *)msh->commands->content;
	if(!backup_fds(msh))
		return (1);
	if (is_builtin(cmd))
	{
		if (!apply_redirections(cmd))
			return (1);
		cmd->status = launch_builtin(msh, cmd);
	}
	else
	{
		if (launch_process(msh, cmd, launch_executable))
		{
			wait(&status);
			if (WIFEXITED(status))
				cmd->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cmd->status = WTERMSIG(status) + 128;
		}
	}
	restore_fds(msh);
	return (cmd->status);
}

int	execute_commands(t_minish *msh)
{
	int	num_commands;
	int	status;

	num_commands = ft_lstsize(msh->commands);
	status = 0;
	if (!init_redirections(msh->commands))
		return (1);
	if (num_commands == 1)
		status = execute_single(msh);
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

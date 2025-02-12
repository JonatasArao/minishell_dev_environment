/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command-gugomes-.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:26:17 by gugomes-          #+#    #+#             */
/*   Updated: 2025/02/12 17:03:33 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
typedef struct s_command
{
	char	*cmd;
	char	*args;
}	t_command;

void free_commands(char **commands)
{
	int j = 0;
	while (commands[j])
	{
		free(commands[j]);
		j++;
	}
	free(commands);
}

char **parse_pipe_commands(char *line)
{
	char **commands = ft_split(line, '|');
	return (commands);
}

t_command	parse_command(char *line)
{
	t_command	command;

	command.cmd = ft_strtok(line, " ");
	command.args = ft_strtok(NULL, "");
	printf("--------------------\nacabou o parse\n");
	return (command);
}

char	*read_input(void)
{
	char	*line;
	char	*newline_pos;

	line = get_next_line(0); // 0 is the file descriptor for stdin
	if (line == NULL)
	{
		return (NULL);
	}
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos != NULL)
		*newline_pos = '\0';
	return (line);
}
void builtin_echo(t_command command)
{
	if (command.args && ft_strncmp(command.args, "-n ", 3) == 0)
		ft_putstr_fd(command.args + 3, 1);
	else if (command.args)
	{
		ft_putstr_fd(command.args, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
}

void builtin_cd(t_command command)
{
	if (command.args == NULL)
	{
		dprintf(2, "cd: missing argument\n");
		return;
	}
	if (chdir(command.args) != 0)
		perror("cd");
}

void builtin_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		perror("pwd");
}

void builtin_export(t_command command)
{
	if (command.args == NULL)
	{
		dprintf(2, "export: missing argument\n");
		return;
	}
	if (putenv(command.args) != 0)
		perror("export");
}

void builtin_unset(t_command command)
{
	if (command.args == NULL)
	{
		dprintf(2, "unset: missing argument\n");
		return;
	}
	if (unsetenv(command.args) != 0)
		perror("unset");
}

void builtin_env(void)
{
	extern char **environ;
	for (char **env = environ; *env != 0; env++)
		ft_putendl_fd(*env, 1);
}

void builtin_exit(void)
{
	exit(0);
}
void 	builtin_print_hello(void)
{
	ft_putstr_fd("Hello, world!\n", 1);
}

int	is_builtin(t_command command)
{
	if (ft_strncmp(command.cmd, "echo", sizeof("echo")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "cd", sizeof("cd")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "pwd", sizeof("pwd")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "export", sizeof("export")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "unset", sizeof("unset")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "env", sizeof("env")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "exit", sizeof("exit")) == 0)
		return (1);
	if (ft_strncmp(command.cmd, "hello", sizeof("hello")) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_command command)
{
	printf("\n\nis_builtin\n\n");
	if (ft_strncmp(command.cmd, "echo", sizeof("echo")) == 0)
		builtin_echo(command);
	else if (ft_strncmp(command.cmd, "cd", sizeof("cd")) == 0)
		builtin_cd(command);
	else if (ft_strncmp(command.cmd, "pwd", sizeof("pwd")) == 0)
		builtin_pwd();
	else if (ft_strncmp(command.cmd, "export", sizeof("export")) == 0)
		builtin_export(command);
	else if (ft_strncmp(command.cmd, "unset", sizeof("unset")) == 0)
		builtin_unset(command);
	else if (ft_strncmp(command.cmd, "env", sizeof("env")) == 0)
		builtin_env();
	else if (ft_strncmp(command.cmd, "exit", sizeof("exit")) == 0)
		builtin_exit();
	else if (ft_strncmp(command.cmd, "hello", sizeof("hello")) == 0)
		builtin_print_hello();
}

char *find_command_in_path(char *cmd)
{
	char *path_env = getenv("PATH");
	if (!path_env)
		return NULL;

	char *path_copy = strdup(path_env);
	char *dir = strtok(path_copy, ":");

	while (dir)
	{
		char *full_path = ft_calloc(strlen(dir) + strlen(cmd) + 2, sizeof(char));
		if (!full_path) {
			free(path_copy);
			return NULL;
		}
		ft_strlcpy(full_path, dir, strlen(dir) + 1);
		ft_strlcat(full_path, "/", strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, strlen(full_path) + strlen(cmd) + 1);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL;
}

void handle_child_process(char **commands, int i, int pipe_fds[2])
{
	if (i != 0)
		dup2(pipe_fds[0], STDIN_FILENO);
	if (commands[i + 1])
		dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	t_command command = parse_command(commands[i]);
	char *args[3] = {command.cmd, command.args, NULL};
	char *full_path = find_command_in_path(command.cmd);
	if (!full_path)
	{
		dprintf(2, "Error: command '%s' not found in PATH\n", command.cmd);
		_exit(1);
	}
	execve(full_path, args, NULL);
	perror("execve");
	_exit(1);
}

void handle_parent_process(int pipe_fds[2], pid_t pid, int *status)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid, status, 0);
}

void execute_pipe_commands(char *line)
{
	char **commands = parse_pipe_commands(line);
	int i = 0;
	int pipe_fds[2];
	pid_t pid;
	int status;

	while (commands[i])
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe");
			return;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
			handle_child_process(commands, i, pipe_fds);
		else
			handle_parent_process(pipe_fds, pid, &status);
		i++;
	}
	free_commands(commands);
}

void execute_command(t_command command)
{
	if (is_builtin(command))
		execute_builtin(command);
	else
	{
		char *args[3] = {command.cmd, command.args, NULL};
		char *full_path = find_command_in_path(command.cmd);
		if (!full_path)
		{
			dprintf(2, "Error: command '%s' not found in PATH\n", command.cmd);
			return;
		}
		pid_t pid = fork();
		if (pid == 0)
		{
			execve(full_path, args, NULL);
			perror("execve");
			_exit(1);
		}
		else if (pid > 0)
		{
			int status;
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork");
		}
		free(full_path);
	}
}

int	main(int argc, char **argv)
{
	t_command	command;
	char		*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = read_input();
		if (line == NULL)
			break;
		command = parse_command(line);
		execute_command(command);
		free(line);
	}
	return (0);
}
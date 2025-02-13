/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command-gugomes-.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:26:17 by gugomes-          #+#    #+#             */
/*   Updated: 2025/02/13 14:21:56 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

void handle_output_redirection(t_command *command);

void	builtin_echo(t_command *command)
{
    t_list	*arg;
    int		newline;

    arg = command->arguments->next;
    newline = 1;

    if (arg && ft_strncmp(arg->content, "-n", 3) == 0)
    {
        newline = 0;
        arg = arg->next;
    }
    handle_output_redirection(command);
    while (arg)
    {
        ft_putstr_fd(arg->content, STDOUT_FILENO);
        if (arg->next)
            ft_putchar_fd(' ', STDOUT_FILENO);
        arg = arg->next;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

void	builtin_cd(t_command *command)
{
	char	*path;
	char	cwd[1024];

	if (!command->arguments || !command->arguments->next)
	{
		fprintf(stderr, "Usage: cd <directory>\n");
		return;
	}
	path = command->arguments->next->content;
	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_putendl_fd(cwd, 1);
		else
			perror("getcwd() error");
	}
	else
		perror("chdir() error");
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		perror("pwd");
}
int	add_env_var(t_list **env_vars, const char *key, const char *value)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (-1);
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	if (!new_var->key || !new_var->value)
	{
		free(new_var->key);
		free(new_var->value);
		free(new_var);
		return (-1);
	}
	ft_lstadd_front(env_vars, ft_lstnew(new_var));
	return (0);
}

int	remove_env_var(t_list **env_vars, const char *key)
{
	t_list		*current;
	t_list		*prev;
	t_env_var	*env_var;

	current = *env_vars;
	prev = NULL;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		if (strcmp(env_var->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_vars = current->next;
			free(env_var->key);
			free(env_var->value);
			free(env_var);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

char *ft_strndup(const char *s, size_t n)
{
	char *result;
	size_t len = strnlen(s, n);

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	strncpy(result, s, len);
	result[len] = '\0';
	return (result);
}
void	builtin_export(t_minish *msh, t_command *command)
{
	char	*arg;
	char	*key;
	char	*value;
	
	if (!command->arguments || !command->arguments->next)
	{
		ft_putstr_fd("export: missing argument\n", 2);
		return;
	}
	arg = command->arguments->next->content;
	key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (perror("export"));
	}
	if (add_env_var(&msh->env_vars, key, value) != 0)
		perror("export");
	free(key);
	free(value);
}

void builtin_unset(t_minish *msh, t_command *command)
{
	if (!command->arguments || !command->arguments->next)
	{
		dprintf(2, "unset: missing argument\n");
		return;
	}
	if (remove_env_var(&msh->env_vars, command->arguments->next->content) != 0)
		perror("unset");
}

void	builtin_env(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
}

void	builtin_exit(t_minish *msh)
{
	if (msh->input)
		free(msh->input);
	if (msh->tokens)
		ft_lstclear(&msh->tokens, free);
	if (msh->commands)
		ft_lstclear(&msh->commands, free_command);
	exit(0);
}

void	builtin_print_hello(void)
{
	ft_putstr_fd("Hello, world!\n", 1);
}

int	is_builtin(t_command *command)
{
	const char	*cmd;

	cmd = command->arguments->content;
	if (ft_strncmp(cmd, "echo", sizeof("echo")) == 0
		|| ft_strncmp(cmd, "cd", sizeof("cd")) == 0
		|| ft_strncmp(cmd, "pwd", sizeof("pwd")) == 0
		|| ft_strncmp(cmd, "export", sizeof("export")) == 0
		|| ft_strncmp(cmd, "unset", sizeof("unset")) == 0
		|| ft_strncmp(cmd, "env", sizeof("env")) == 0
		|| ft_strncmp(cmd, "exit", sizeof("exit")) == 0
		|| ft_strncmp(cmd, "hello", sizeof("hello")) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minish *msh, t_command *command)
{
	const char	*cmd;

	cmd = command->arguments->content;
	if (ft_strncmp(cmd, "echo", sizeof("echo")) == 0)
		builtin_echo(command);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		builtin_cd(command);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd, "export", 6) == 0)
		builtin_export(msh, command);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		builtin_unset(msh, command);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		builtin_env();
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		builtin_exit(msh);
	else if (ft_strncmp(cmd, "hello", 5) == 0)
		builtin_print_hello();
}

char *ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);
	result = malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	strcat(result, s2);
	strcat(result, s3);
	return (result);
}
void ft_free_split(char **split)
{
	int i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
char *find_command_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void handle_input_redirection(t_command *command)
{
    t_list *node;
    t_redirection *redir;
    int fd;

    node = command->input_redir;
    while (node)
    {
        redir = (t_redirection *)node->content;
        if (is_input_redirection(redir->type))
        {
            fd = open(redir->target, O_RDONLY);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(fd);
        }
        node = node->next;
    }
}

void handle_output_redirection(t_command *command)
{
    t_list *node;
    t_redirection *redir;
    int fd;

    node = command->output_redir;
    while (node)
    {
        redir = (t_redirection *)node->content;
        if (is_output_redirection(redir->type))
        {
            if (ft_strncmp(redir->type, ">", 1) == 0)
                fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (ft_strncmp(redir->type, ">>", 2) == 0)
                fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(fd);
        }
        node = node->next;
    }
}
void handle_redirections(t_command *command)
{
    handle_input_redirection(command);
    handle_output_redirection(command);
}


void handle_child_process(t_command *command, int pipe_fds[2], int i, int num_commands)
{
    if (i != 0)
        dup2(pipe_fds[0], STDIN_FILENO);
    if (i != num_commands - 1)
        dup2(pipe_fds[1], STDOUT_FILENO);
    close(pipe_fds[0]);
    close(pipe_fds[1]);

    handle_redirections(command);

    char *args[3];
    args[0] = command->arguments->content;
    if (command->arguments->next)
        args[1] = command->arguments->next->content;
    else
        args[1] = NULL;
    args[2] = NULL;

    char *full_path = find_command_in_path(command->arguments->content);
    if (!full_path)
    {
        printf("Error: command '%s' not found in PATH\n", (char *)command->arguments->content);
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

void execute_pipe_commands(t_list *commands)
{
	int i = 0;
	int pipe_fds[2];
	pid_t pid;
	int status;
	int num_commands = ft_lstsize(commands);

	while (commands)
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
			handle_child_process(commands->content, pipe_fds, i, num_commands);
		else
			handle_parent_process(pipe_fds, pid, &status);
		commands = commands->next;
		i++;
	}
}

void execute_command(t_minish *msh, t_command *command, int is_pipeline)
{
	if (is_builtin(command))
	{
		if (is_pipeline)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				handle_redirections(command);
				execute_builtin(msh, command);
				_exit(0);
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
		}
		else
		{
			execute_builtin(msh, command);
		}
	}
	else
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			handle_redirections(command);

			char *args[3];
			args[0] = command->arguments->content;
			if (command->arguments->next)
				args[1] = command->arguments->next->content;
			else
				args[1] = NULL;
			args[2] = NULL;

			char *full_path = find_command_in_path(command->arguments->content);
			if (!full_path)
			{
				printf("Error: command '%s' not found in PATH\n", (char *)command->arguments->content);
				_exit(1);
			}

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
	}
}

void process_commands(t_minish *msh)
{
	t_list *command_node;
	int is_pipeline = ft_lstsize(msh->commands) > 1;

	command_node = msh->commands;
	while (command_node)
	{
		execute_command(msh, command_node->content, is_pipeline);
		command_node = command_node->next;
	}
	ft_lstclear(&msh->commands, free_command);
}


void process_inputs(t_minish *msh)
{
	msh->tokens = extract_tokens(msh->input);
	if (!is_token_list_valid(msh->tokens))
	{
		ft_lstclear(&msh->tokens, free);
		free(msh->input);
		return;
	}
	msh->commands = extract_commands(msh->tokens);
	ft_lstclear(&msh->tokens, free);
	process_commands(msh);
	add_history(msh->input);
	free(msh->input);
}

int main(int argc, char **argv)
{
	t_minish msh;

	(void)argc;
	(void)argv;
	while (1)
	{
		msh.input = readline("minishell> ");
		if (!msh.input)
			break;
		process_inputs(&msh);
	}
	return (0);
}

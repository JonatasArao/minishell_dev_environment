/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_v2-gugomes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:13:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 19:04:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/workspace/minishell/inc/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

void		free_array(char **array);
char		**ft_lst_to_array(t_list *lst);
char		*get_command_path(char *cmd, char **env);
static void	handle_error(char **args, char *message, int exit_code);
static void	execute_command(t_command *cmd, char **env);
static void	execute_pipeline(t_list *commands, char **env);
int			open_file(const char *filepath, int flags);

static void	handle_error(char **args, char *message, int exit_code)
{
	ft_putstr_fd(message, 2);
	if (args && args[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(args[0], 2);
	}
	ft_putstr_fd("\n", 2);
	free_array(args);
	exit(exit_code);
}

void	free_array(char **array)
{
	int	i;

	i= 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_lst_to_array(t_list *lst)
{
	char	**array;
	int		i;
	int		size;

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

static t_list	*convert_env_to_list(char **env)
{
	return (extract_env_vars(env));
}

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	**get_paths_from_env(t_list *env_list)
{
	t_env_var	*path_var;

	path_var = get_env_var(env_list, "PATH");
	if (!path_var || !path_var->value)
		return NULL;
	return ft_split(path_var->value, ':');
}

static char	*find_command_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*temp;

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

char	*get_command_path(char *cmd, char **env)
{
	t_list	*env_list;
	char	**paths;
	char	*direct_path;
	char	*command_path;

	env_list = convert_env_to_list(env);
	direct_path = check_direct_path(cmd);
	if (direct_path)
	{
		ft_lstclear(&env_list, free_env_var);
		return (direct_path);
	}
	paths = get_paths_from_env(env_list);
	if (!paths)
	{
		ft_lstclear(&env_list, free_env_var);
		return (cmd);
	}
	command_path = find_command_in_paths(cmd, paths);
	if (command_path)
	{
		ft_lstclear(&env_list, free_env_var);
		return (command_path);
	}
	free_array(paths);
	ft_lstclear(&env_list, free_env_var);
	return (cmd);
}

static int	apply_redirections(t_command *cmd)
{
	t_list			*redir_node;
	t_redirection	*redir;
	int				flags;

	redir_node = cmd->output_redir;
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
		{
			perror("minishell");
			return (0);
		}
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
		redir_node = redir_node->next;
	}
	return (1);
}
static void	execute_command(t_command *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_lst_to_array(cmd->arguments);
	if (!args || !args[0])
		handle_error(args, "minishell: command not found", 127);
	if (!args[0][0])
		handle_error(args, "minishell: syntax error", 2);
    path = get_command_path(args[0], env);
	if (!path)
		handle_error(args, "minishell: command not found", 127);
	execve(path, args, env);
	handle_error(args, "minishell: execve error", 126);
}

static void	handle_child(t_command *cmd, int pipe_fd[2], int input_fd, int has_next, char **env)
{
	if (!apply_redirections(cmd))
		exit(1);

	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
		close(pipe_fd[0]);
	execute_command(cmd, env);
}

static void	handle_parent(int *input_fd, int pipe_fd[2], int has_next)
{
	if (has_next)
		close(pipe_fd[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = pipe_fd[0];
}

static void	execute_pipeline(t_list *commands, char **env)
{
	int		pipe_fd[2];
	int		input_fd;
	pid_t	pid;

	input_fd = STDIN_FILENO;
	while (commands)
	{
		t_command	*cmd = (t_command *)commands->content;
		int			has_next = (commands->next != NULL);

        if (has_next && pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        pid = fork();
        if (pid == 0)
        {
            handle_child(cmd, pipe_fd, input_fd, has_next, env);
        }
        else
        {
            handle_parent(&input_fd, pipe_fd, has_next);
            commands = commands->next;
        }
    }
    while (wait(NULL) > 0)
        ;
}

int	open_file(const char *filepath, int flags)
{
	int fd;

	if (flags == 0)
		fd = open(filepath, O_RDONLY);
	else if (flags == 2)
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = -1;
	if (fd == -1)
		perror("open failed");
	return (fd);
}

int	main(int argc, char **argv, char **env)
{
	t_minish	msh;

	(void)argc;
	(void)argv;
	while (1)
	{
		msh.input = readline("minishell> ");
		if (!msh.input)
			break ;
    	msh.tokens = extract_tokens(msh.input);
		if (!is_token_list_valid(msh.tokens))
		{
			ft_lstclear(&msh.tokens, free);
			free(msh.input);
			continue ;
		}
        msh.commands = extract_commands(msh.tokens);
		ft_lstclear(&msh.tokens, free);
		execute_pipeline(msh.commands, env);
		ft_lstclear(&msh.commands, free_command);
		add_history(msh.input);
		free(msh.input);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate-executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:17:31 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/26 16:18:47 by jarao-de         ###   ########.fr       */
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

int	execute_commands(t_minish *msh)
{
	int	num_commands;
	int	status;

	num_commands = ft_lstsize(msh->commands);
	status = 0;
	if (!init_redirections(msh->commands))
		return (1);
	if (num_commands == 1 && is_builtin(msh->commands->content))
		status = launch_builtin(msh, (t_command *)msh->commands->content);
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

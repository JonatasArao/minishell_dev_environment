/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v2-jarao-de.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:54:11 by jarao-de          #+#    #+#             */
/*   Updated: 2025/03/05 00:52:54 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_heredoc_var_end(const char *line)
{
	size_t		end;

	if (line[0] == '\0')
		return (0);
	end = 0;
	while (line[end])
	{
		if (line[0] == '$' && (ft_isspace(line[end])
				|| ft_strchr("\"';()[]{}+-*/=", line[end])
				|| (end > 0 && line[end - 1] == '?')))
			break ;
		if (line[end] == '$' && end != 0)
			return (end);
		end++;
	}
	return (end);
}

char	*get_next_heredoc_var(char const *token)
{
	char			*word;
	unsigned int	start;
	size_t			end;

	start = 0;
	end = get_heredoc_var_end(token);
	if (start == end)
		return (NULL);
	word = ft_substr(token, start, end - start);
	if (!word)
		return (NULL);
	return (word);
}

t_list	*extract_heredoc_vars(const char *token)
{
	t_list	*head;
	t_list	*current;
	char	*word;

	head = NULL;
	while (*token)
	{
		word = get_next_heredoc_var(token);
		if (!word && head)
			ft_lstclear(&head, free);
		if (!word)
			break ;
		token += ft_strlen(word);
		current = ft_lstnew((void *) word);
		if (head)
			ft_lstadd_back(&head, current);
		else
			head = current;
	}
	return (head);
}

int	expand_heredoc_var(t_list *env, int last_status, char **var)
{
	char	*new_value;
	char	*content;

	new_value = NULL;
	content = (char *)(*var);
	if (content[0] == '$' && content[1] != '\0')
	{
		new_value = get_var_value(env, last_status, content + 1);
		if (!new_value)
			new_value = ft_strdup("");
		if (!new_value)
			return (0);
	}
	else
		return (1);
	free(*var);
	*var = new_value;
	return (1);
}

char	*expand_heredoc_line(t_list *env, int last_status, char *line)
{
	t_list	*var_list;
	t_list	*current;
	char	*new_line;
	char	**current_var;

	var_list = extract_heredoc_vars(line);
	if (!var_list)
		return (NULL);
	current = var_list;
	while (current)
	{
		current_var = (char **)&current->content;
		if (!expand_heredoc_var(env, last_status, current_var))
		{
			ft_lstclear(&var_list, free);
			return (NULL);
		}
		current = current->next;
	}
	new_line = concat_vars(var_list);
	ft_lstclear(&var_list, free);
	if (!new_line)
		return (NULL);
	return (new_line);
}

int	remove_delim_quotes(char *str)
{
	char	*src;
	char	*dst;
	int		has_quote;

	if (!str)
		return (0);
	src = str;
	dst = str;
	has_quote = 0;
	while (*src)
	{
		if (*src != '\'' && *src != '\"')
		{
			*dst = *src;
			dst++;
		}
		else
			has_quote = 1;
		src++;
	}
	*dst = '\0';
	return (has_quote);
}

int	is_delimiter(char *input, char *delim)
{
	int	delim_len;

	delim_len = ft_strlen(delim);
	if (ft_strncmp(input, delim, delim_len) == 0
		&& input[delim_len] == '\0')
		return (1);
	return (0);
}

char	*process_input_line(t_msh *msh, char *input, int has_quote)
{
	char	*line;

	if (has_quote)
	{
		line = ft_strdup(input);
		if (!line)
			return (NULL);
	}
	else
	{
		line = expand_heredoc_line(msh->env_vars, msh->last_status, input);
		if (!line)
			return (NULL);
	}
	return (line);
}

int	capture_heredoc(t_msh *msh, char *delim, int heredoc_fd)
{
	char	*input;
	char	*line;
	int		has_quote;

	has_quote = remove_delim_quotes(delim);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (0);
		if (is_delimiter(input, delim))
		{
			free(input);
			break ;
		}
		line = process_input_line(msh, input, has_quote);
		free(input);
		if (!line)
			return (0);
		ft_putendl_fd(line, heredoc_fd);
		free(line);
	}
	return (1);
}

int	open_heredoc(t_msh *msh, char *delim)
{
	int		heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
	{
		perror("minishell: heredoc:");
		return (0);
	}
	if (!capture_heredoc(msh, delim, heredoc_fd[1]))
	{
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
		return (-1);
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;
	char		*input;
	int			doc_fd;

	(void) argc;
	(void) argv;
	init_minishell(&msh, envp);
	while (1)
	{
		input = readline("<< ");
		if (input == NULL)
			break ;
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		doc_fd = open_heredoc(&msh, input);
		char buffer[1024];
		ssize_t bytes_read;

		while ((bytes_read = read(doc_fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			printf("%s", buffer);
		}
		close(doc_fd);
		free(input);
	}
	destroy_minishell(&msh);
	rl_clear_history();
	return (0);
}
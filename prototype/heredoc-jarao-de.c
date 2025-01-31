/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc-jarao-de.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:36:19 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 16:43:47 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*append_heredoc_line(char *doc, const char *line)
{
	char	*new_doc;
	size_t	doc_len;
	size_t	line_len;

	doc_len = ft_strlen(doc);
	line_len = ft_strlen(line);
	new_doc = (char *)malloc((doc_len + line_len + 2) * sizeof(char));
	if (!new_doc)
		return (NULL);
	ft_strlcpy(new_doc, doc, doc_len + 1);
	ft_strlcat(new_doc, line, doc_len + line_len + 1);
	new_doc[doc_len + line_len] = '\n';
	new_doc[doc_len + line_len + 1] = '\0';
	free(doc);
	return (new_doc);
}

char	*capture_heredoc(const char *prompt, const char *delim)
{
	char	*line;
	char	*doc;

	doc = ft_strdup("");
	if (!doc)
		return (NULL);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		doc = append_heredoc_line(doc, line);
		free(line);
		if (!doc)
			break ;
	}
	return (doc);
}

int	main(void)
{
	char	*document;
	char	*input;

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
		document = capture_heredoc("> ", input);
		printf("%s", document);
		free(input);
	}
	rl_clear_history();
	return (0);
}

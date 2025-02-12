/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token-jarao-de.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:55:13 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 12:54:41 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char	*get_var_value(const char *key)
{
	size_t		key_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (ft_strncmp("USER", key, key_len) == 0
		&& "USER"[key_len] == '\0')
		return (ft_strdup("Gugomes"));
	else if (ft_strncmp("SCHOOL", key, key_len) == 0
		&& "SCHOOL"[key_len] == '\0')
		return (ft_strdup("42"));
	else if (ft_strncmp("CITY", key, key_len) == 0
		&& "CITY"[key_len] == '\0')
		return (ft_strdup("São Paulo"));
	else if (ft_strncmp("?", key, key_len) == 0
		&& "?"[key_len] == '\0')
		return (ft_strdup("0"));
	return (ft_strdup(""));
}

size_t	get_variable_end(const char *s, unsigned int start)
{
	static char	quote_char;
	size_t		end;

	if (s[start] == '\0' || start >= ft_strlen(s))
		return (start);
	end = start;
	if (!quote_char && ft_strchr("\"'", s[end]))
		quote_char = s[end];
	if (ft_strchr("\"'$", s[end]))
		end++;
	while (s[end] && (!ft_strchr("\"'$", s[end]) || quote_char))
	{
		if (s[end] == quote_char || (s[start] == '$'
				&& (ft_isspace(s[end]) || ft_strchr("\"'", s[end]))))
			break ;
		if (quote_char != '\'' && s[end] == '$')
			return (end);
		end++;
	}
	if (s[end] == quote_char)
	{
		quote_char = 0;
		end++;
	}
	return (end);
}

char	*get_next_variable(char const *s)
{
	char			*word;
	unsigned int	start;
	size_t			end;

	start = 0;
	end = get_variable_end(s, start);
	if (start == end)
		return (NULL);
	word = ft_substr(s, start, end - start);
	if (!word)
		return (NULL);
	return (word);
}

t_list	*extract_vars(const char *s)
{
	t_list	*head;
	t_list	*current;
	char	*word;

	head = NULL;
	while (*s)
	{
		word = get_next_variable(s);
		if (!word && head)
			ft_lstclear(&head, free);
		if (!word)
			break ;
		s += ft_strlen(word);
		current = ft_lstnew((void *) word);
		if (head)
			ft_lstadd_back(&head, current);
		else
			head = current;
	}
	return (head);
}

char	*concat_vars(t_list *vars)
{
	char	*result;
	size_t	total_length;
	t_list	*temp;

	total_length = 0;
	temp = vars;
	while (temp)
	{
		total_length += strlen((char *)temp->content);
		temp = temp->next;
	}
	result = (char *)malloc(total_length + 1);
	if (!result)
	{
		ft_lstclear(&vars, free);
		return (NULL);
	}
	result[0] = '\0';
	temp = vars;
	while (temp)
	{
		ft_strlcat(result, (char *)temp->content, total_length + 1);
		temp = temp->next;
	}
	return (result);
}

int	expand_var(t_list *node)
{
	char	*new_value;
	char	*content;
	char	*quote;
	char	*double_quote;

	new_value = NULL;
	content = (char *)node->content;
	if (content[0] == '$')
		new_value = get_var_value(content + 1);
	else
	{
		quote = ft_strrchr(content, '\'');
		double_quote = ft_strrchr(content, '"');
		if (quote && (!double_quote || quote > double_quote))
			new_value = ft_strtrim(content, "'");
		else if (double_quote && (!quote || double_quote > quote))
			new_value = ft_strtrim(content, "\"");
	}
	if (!new_value)
		return (0);
	free(node->content);
	node->content = new_value;
	return (1);
}

void	expand_vars(t_list *variables)
{
	t_list	*temp;

	temp = variables;
	while (temp)
	{
		expand_var(temp);
		temp = temp->next;
	}
}

int	main(void)
{
	t_list	*variables;
	char	*result;
	char	*str;

	str = "He\"ll\"o\" $USER'Aluno' \", Welcome to '$SCHOOL' in $CITY \".\" $?";
	variables = extract_vars(str);
	t_list *temp = variables;
	while (temp)
	{
		printf("Variable: {%s}\n", (char *)temp->content);
		temp = temp->next;
	}
	expand_vars(variables);
	result = concat_vars(variables);
	if (result)
	{
		printf("%s\n", result);
		free(result);
	}
	ft_lstclear(&variables, free);
	return (0);
}

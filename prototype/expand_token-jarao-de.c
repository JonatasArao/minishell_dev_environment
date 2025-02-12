/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token-jarao-de.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:55:13 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 10:07:59 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char	*get_env_var(const char *key)
{
	size_t		key_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (ft_strncmp("USER", key, key_len) == 0
		&& "USER"[key_len] == '\0')
		return (ft_strdup("Gugomes"));
	else if (ft_strncmp("SCHOOL", key, key_len) == 0
		&& "USER"[key_len] == '\0')
		return (ft_strdup("42"));
	else if (ft_strncmp("CITY", key, key_len) == 0
		&& "USER"[key_len] == '\0')
		return (ft_strdup("São Paulo"));
	return (ft_strdup(""));
}

size_t	get_variable_end(const char *s, unsigned int start)
{
	size_t	end;
	char	quote_char;

	if (s[start] == '\0' || start >= ft_strlen(s))
		return (start);
	end = start;
	quote_char = 0;
	if (s[end] == '\'')
		quote_char = s[end];
	if (ft_strchr("'$", s[end]))
		end++;
	while (s[end] && (!ft_strchr("\"'$", s[end]) || quote_char))
	{
		if (s[end] == quote_char || (s[start] == '$' && ft_isspace(s[end])))
			break ;
		end++;
	}
	if (s[start] == '\'')
		end++;
	return (end);
}

char	*get_next_variable(char const *s)
{
	char			*word;
	unsigned int	start;
	size_t			end;

	start = 0;
	while (s[start] && ft_strchr("\"", s[start]))
		start++;
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
		while (*s && ft_strchr("\"", *s))
			s++;
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

void	expand_vars(t_list *variables)
{
	t_list	*temp;
	char	*new_value;
	char	*content;

	temp = variables;
	while (temp)
	{
		new_value = NULL;
		content = (char *)temp->content;
		if (content[0] == '$')
			new_value = get_env_var(content + 1);
		if (new_value)
		{
			free(temp->content);
			temp->content = new_value;
		}
		temp = temp->next;
	}
}

int	main(void)
{
	t_list	*variables;
	char	*result;
	char	*str;

	str = "He\"ll\"o\" $USER 'SER' \", Welcome to' $SCHOOL' in $CITY \".\"";
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

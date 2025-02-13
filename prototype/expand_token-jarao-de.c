/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token-jarao-de.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:55:13 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/13 15:59:53 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

size_t	get_var_end(const char *token)
{
	static char	quote_char;
	size_t		end;

	if (token[0] == '\0')
		return (0);
	end = 0;
	if (!quote_char && ft_strchr("\"'", token[end]))
		quote_char = token[end++];
	while (token[end] && (!ft_strchr("\"'", token[end]) || quote_char))
	{
		if (token[end] == quote_char || (token[0] == '$'
				&& (ft_isspace(token[end]) || ft_strchr("\"'", token[end]))))
			break ;
		if (quote_char != '\'' && token[end] == '$' && end != 0)
			return (end);
		end++;
	}
	if (token[0] != '$' && token[end] == quote_char)
	{
		quote_char = 0;
		end++;
	}
	return (end);
}

char	*get_next_var(char const *token)
{
	char			*word;
	unsigned int	start;
	size_t			end;

	start = 0;
	end = get_var_end(token);
	if (start == end)
		return (NULL);
	word = ft_substr(token, start, end - start);
	if (!word)
		return (NULL);
	return (word);
}

t_list	*extract_vars(const char *token)
{
	t_list	*head;
	t_list	*current;
	char	*word;

	head = NULL;
	while (*token)
	{
		word = get_next_var(token);
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

char	*get_var_value(const char *key)
{
	char	*value;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_strdup("0"));
	value = getenv(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	expand_var(char	**var)
{
	char	*new_value;
	char	*content;
	char	*quote;
	char	*double_quote;

	new_value = NULL;
	content = (char *)(*var);
	if (content[0] == '$')
		new_value = get_var_value(content + 1);
	else
	{
		quote = ft_strrchr(content, '\'');
		double_quote = ft_strrchr(content, '"');
		if (double_quote && (!quote || double_quote > quote
				|| (ft_strncmp(content, "\"'", 2) == 0 && content[3] == '\0')))
			new_value = ft_strtrim(content, "\"");
		else if (quote && (!double_quote || quote > double_quote))
			new_value = ft_strtrim(content, "'");
	}
	if (!new_value)
		return (0);
	free(*var);
	*var = new_value;
	return (1);
}

char	*expand_token(char *s)
{
	t_list	*var_list;
	t_list	*current;
	char	*new_tok;

	var_list = extract_vars(s);
	current = var_list;
	while (current)
	{
		expand_var((char **)&current->content);
		current = current->next;
	}
	new_tok = concat_vars(var_list);
	ft_lstclear(&var_list, free);
	return (new_tok);
}

int	main(void)
{
	t_list	*var_list;
	t_list	*temp;
	char	*str;
	char	*new_str;

	str = "He\"ll\"o\" $USER'Vulgo'\"\"'$HOME'\", Welcome to '\"$PATH\"' in $LANG \".\" $?";
	var_list = extract_vars(str);
	temp = var_list;
	while (temp)
	{
		printf("Variable: {%s}\n", (char *)temp->content);
		temp = temp->next;
	}
	new_str = expand_token(str);
	if (new_str)
	{
		printf("%s\n", new_str);
		free(new_str);
	}
	ft_lstclear(&var_list, free);
	return (0);
}

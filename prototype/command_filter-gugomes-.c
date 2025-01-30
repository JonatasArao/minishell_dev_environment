/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_filter-gugomes-.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:00:12 by gugomes-          #+#    #+#             */
/*   Updated: 2025/01/30 12:53:19 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

typedef struct s_token
{
	char            *value;
	struct s_token  *next;
} t_token;

t_token *create_token(char *value)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void add_token(t_token **tokens, char *value)
{
	t_token *new_token;
	t_token *temp;

	new_token = create_token(value);
	if (!new_token)
		return ;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		temp = *tokens;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
}

void free_tokens(t_token *tokens)
{
	t_token *temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}
void handle_quotes(char **start, t_token **tokens)
{
	char *end = *start + 1;
	while (*end && *end != '"')
		end++;
	if (*end == '"')
		end++;
	char *token_value = ft_substr(*start, 0, end - *start);
	add_token(tokens, token_value);
	*start = end;
}

void handle_metachar(char **start, t_token **tokens)
{
	char *token_value;

	if (!ft_strncmp("<<", *start, 2) || !ft_strncmp(">>", *start, 2))
	{
		token_value = ft_substr(*start, 0, 2);
		*start += 2;
	}
	else
	{
		token_value = ft_substr(*start, 0, 1);
		*start += 1;
	}
	add_token(tokens, token_value);
}

void handle_regular_chars(char **start, t_token **tokens)
{
	char *end = *start;
	while (*end && !isspace(*end) && !ft_strchr(">|<", *end))
		end++;
	char *token_value = ft_substr(*start, 0, end - *start);
	add_token(tokens, token_value);
	*start = end;
}

void tokenize(char *input, t_token **tokens)
{
	char *start = input;
	while (*start)
	{
		while (*start && isspace(*start))
			start++;
		if (*start == '\0')
			break;
		if (*start == '"')
			handle_quotes(&start, tokens);
		else if (ft_strchr(">|<", *start))
			handle_metachar(&start, tokens);
		else
			handle_regular_chars(&start, tokens);
	}
}

int main(void)
{
	char    *input;
	t_token *tokens;
	t_token *temp;

	while (1)
	{
		input = readline("Digite algo: ");
		if (input == NULL)
			break ;
		if (strcmp(input, "sair") == 0)
		{
			free(input);
			break ;
		}
		tokens = NULL;
		tokenize(input, &tokens);
		temp = tokens;
		while (temp != NULL)
		{
			printf("Token: %s\n", temp->value);
			temp = temp->next;
		}
		free_tokens(tokens);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
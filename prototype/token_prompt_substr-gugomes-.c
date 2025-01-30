/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prompt_substr-gugomes-.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:50:08 by gugomes-          #+#    #+#             */
/*   Updated: 2025/01/23 15:52:16 by gugomes-         ###   ########.fr       */
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

void tokenize(char *input, t_token **tokens)
{
    char    *start;
    char    *end;
    char    *token_value;
    int     in_quotes;

    start = input;
    in_quotes = 0;
    while (*start)
    {
        while (*start && isspace(*start))
            start++;
        if (*start == '\0')
            break;
        if (*start == '"')
        {
            end = start + 1;
            while (*end && *end != '"')
                end++;
            if (*end == '"')
                end++;
            token_value = ft_substr(start, 0, end - start);
            add_token(tokens, token_value);
            start = end;
        }
        else
        {
            end = start;
            while (*end && !isspace(*end))
                end++;
            token_value = ft_substr(start, 0, end - start);
            add_token(tokens, token_value);
            start = end;
        }
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
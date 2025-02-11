/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_search-gugomes-.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:47:45 by gugomes-          #+#    #+#             */
/*   Updated: 2025/02/11 16:17:29 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_shell_state
{
	t_env_var	*env_vars;
	int			last_exit_status;
}	t_shell_state;

char	*expand_variable(t_shell_state *state, const char *token)
{
	t_env_var	*current;
	char		*var_name;

	var_name = strdup(token + 1); // Skip the '$' character
	current = state->env_vars;
	while (current)
	{
		if (strcmp(current->name, var_name) == 0)
		{
			free(var_name);
			return (strdup(current->value));
		}
		current = current->next;
	}
	free(var_name);
	return (strdup("")); // Return an empty string if variable not found
}

char	*expand_token(t_shell_state *state, const char *token)
{
	char	*expanded_token;

	if (token[0] == '$')
		expanded_token = expand_variable(state, token);
	else
		expanded_token = strdup(token);
	return (expanded_token);
}

void	concatenate_and_print(t_shell_state *state, char **tokens, int token_count)
{
	char	*result;
	char	*expanded_token;
	size_t	total_length;
	int		i;

	total_length = 0;
	for (i = 0; i < token_count; i++)
	{
		expanded_token = expand_token(state, tokens[i]);
		total_length += strlen(expanded_token);
		free(expanded_token);
	}

	result = (char *)malloc(total_length + 1);
	if (!result)
		return;

	result[0] = '\0';
	for (i = 0; i < token_count; i++)
	{
		expanded_token = expand_token(state, tokens[i]);
		strcat(result, expanded_token);
		free(expanded_token);
	}

	printf("%s\n", result);
	free(result);
}

char	**split_tokens(const char *input, int *token_count)
{
	char	**tokens;
	char	*token;
	char	*input_copy;
	int		count;
	int		in_quotes;
	char	quote_char;

	input_copy = strdup(input);
	if (!input_copy)
		return (NULL);

	tokens = (char **)malloc(sizeof(char *) * (strlen(input) + 1));
	if (!tokens)
	{
		free(input_copy);
		return (NULL);
	}

	count = 0;
	in_quotes = 0;
	quote_char = '\0';
	token = strtok(input_copy, " ");
	while (token)
	{
		if (token[0] == '"' || token[0] == '\'')
		{
			in_quotes = 1;
			quote_char = token[0];
			token++;
		}

		if (in_quotes)
		{
			char *end_quote = strchr(token, quote_char);
			if (end_quote)
			{
				*end_quote = '\0';
				in_quotes = 0;
			}
		}

		tokens[count++] = strdup(token);
		token = strtok(NULL, " ");
	}
	tokens[count] = NULL;
	*token_count = count;
	free(input_copy);
	return (tokens);
}

int main()
{
	t_shell_state state;
	t_env_var var1 = {"var", "jarao-d", NULL};
	state.env_vars = &var1;
	char *input = "Hello \"my friend $var\"!";
	int token_count;
	char **tokens;

	tokens = split_tokens(input, &token_count);
	concatenate_and_print(&state, tokens, token_count);

	for (int i = 0; i < token_count; i++)
		free(tokens[i]);
	free(tokens);

	return 0;
}

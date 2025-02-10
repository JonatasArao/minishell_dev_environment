/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions-gugomes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:07:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 20:37:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

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
	char	*var_name;
	char	*value;
	char	*result;

	var_name = strdup(token + 1);
	if (strcmp(var_name, "?") == 0)
	{
		free(var_name);
		return (ft_itoa(state->last_exit_status));
	}
	value = getenv(var_name);
	if (value != NULL)
		result = strdup(value);
	else
		result = strdup("");
	free(var_name);
	return (result);
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

static size_t	copy_until_quote(const char *token, char *result, \
	size_t i, char quote)
{
	size_t	j;

	j = 0;
	while (token[i] && token[i] != quote)
		result[j++] = token[i++];
	return (j);
}

char	*handle_quotes(const char *token)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!is_valid_quotes(token))
		return (NULL);
    len = strlen(token);
    result = malloc(len + 1);
	if	(!result)
		return (NULL);
	i =0;
    j = 0;
	while (i < len)
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			char quote = token[i++];
            j += copy_until_quote(token, result + j, i, quote);
			while (token[i] && token[i] != quote)
                i++;
			if (token[i])
                i++;
		}
		else
			result[j++] = token[i++];
	}
	result[j] = '\0';
	return (result);
}
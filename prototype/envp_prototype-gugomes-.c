/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_prototype-gugomes-.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:42:11 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 21:00:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_shell_state
{
	t_env_var	*env_vars;
}	t_shell_state;


t_env_var *create_env_var(const char *name, const char *value)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->name = strdup(name);
	new_var->value = strdup(value);
	new_var->next = NULL;
	return (new_var);
}

int	add_env_var(t_shell_state *state, const char *name, const char *value)
{
	t_env_var *new_var;

	new_var = create_env_var(name, value);
	if (!new_var)
		return (-1);
	new_var->next = state->env_vars;
	state->env_vars = new_var;
	return (0);
}

int	remove_env_var(t_shell_state *state, const char *name)
{
	t_env_var *current;
	t_env_var *prev;

	current = state->env_vars;
	prev = NULL;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				state->env_vars = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
        prev = current;
        current = current->next;
	}
	return (-1);
}

// Função para buscar uma variável de ambiente
char	*get_env_var(t_shell_state *state, const char *name)
{
	t_env_var	*current;

	current = state->env_vars;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

// Função para imprimir todas as variáveis de ambiente (para depuração)
void	print_env_vars(t_shell_state *state)
{
	t_env_var	*current;

	current = state->env_vars;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	main(void)
{
	t_shell_state	state;

	state.env_vars = NULL;
	add_env_var(&state, "USER", "marvin");
	add_env_var(&state, "HOME", "/home/marvin");
	add_env_var(&state, "SHELL", "/bin/bash");

	printf("Variáveis de ambiente:\n");
	print_env_vars(&state);

	printf("\nRemovendo variável HOME...\n");
	remove_env_var(&state, "HOME");

	printf("Variáveis de ambiente após remoção:\n");
	print_env_vars(&state);

	return (0);
}
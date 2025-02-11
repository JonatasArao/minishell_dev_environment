/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_linked_list-jarao-de.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:58:35 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 16:21:04 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

void	free_env_var(void *env_var_ptr)
{
	t_env_var	*env_var;

	env_var = (t_env_var *) env_var_ptr;
	if (env_var)
	{
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
	}
}

int	lstadd_env_var(t_list **head, const char *key, const char *value)
{
	t_env_var	*new_env;
	t_list		*new_node;

	if (!(*key) || !value)
		return (0);
	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		return (0);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (!new_env->key || !new_env->value)
	{
		free_env_var(new_env);
		return (0);
	}
	new_node = ft_lstnew(new_env);
	if (!new_node)
	{
		free_env_var(new_env);
		return (0);
	}
	ft_lstadd_front(head, new_node);
	return (1);
}

t_env_var	*get_env_var(t_list *env, const char *key)
{
	t_env_var	*current;
	size_t		key_len;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	while (env)
	{
		current = (t_env_var *) env->content;
		if (current-> key && ft_strncmp(current->key, key, key_len) == 0
			&& current->key[key_len] == '\0')
			return (current);
		env = env->next;
	}
	return (NULL);
}

int	lstset_env_var(t_list *env, const char *key, const char *value)
{
	t_env_var	*env_var;

	env_var = get_env_var(env, key);
	if (!env_var)
		return (lstadd_env_var(&env, key, value));
	free(env_var->value);
	env_var->value = ft_strdup(value);
	if (!env_var->value)
		return (0);
	return (1);
}

t_list	*extract_env_vars(char **envp)
{
	t_list	*env;
	char	*saveptr;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp != NULL)
	{
		key = ft_strtok_r(*envp, "=", &saveptr);
		value = ft_strtok_r(NULL, "=", &saveptr);
		if (!value)
			value = "";
		if (!lstadd_env_var(&env, key, value))
		{
			ft_lstclear(&env, free_env_var);
			return (NULL);
		}
		envp++;
	}
	return (env);
}

char	*create_env_string(const char *key, const char *value)
{
	char	*env_string;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	env_string = (char *) malloc(key_len + value_len + 2);
	if (!env_string)
		return (NULL);
	ft_strlcpy(env_string, key, key_len + 1);
	ft_strlcat(env_string, "=", key_len + 2);
	ft_strlcat(env_string, value, key_len + value_len + 2);
	return (env_string);
}

char	**get_envp(t_list *env)
{
	t_list		*current;
	t_env_var	*env_var;
	int			len;
	char		**envp;
	int			i;

	len = ft_lstsize(env);
	envp = (char **) malloc((len + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		env_var = (t_env_var *) current->content;
		envp[i] = create_env_string(env_var->key, env_var->value);
		if (!envp[i])
			return (ft_free_matrix((void **) envp, i));
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	**new_envp;
	int		i;

	(void) argc;
	(void) argv;
	env = extract_env_vars(envp);
	lstadd_env_var(&env, "SCHOOL", "42 School");
	printf("The user of %s from %s and their home is %s\n",
		get_env_var(env, "USER")->value, get_env_var(env, "SCHOOL")->value,
		get_env_var(env, "HOME")->value);
	lstset_env_var(env, "PATH", "Brasil");
	new_envp = get_envp(env);
	i = 0;
	while (new_envp[i] != NULL)
	{
		printf("%s\n", new_envp[i]);
		i++;
	}
	ft_free_matrix((void **) new_envp, i);
}

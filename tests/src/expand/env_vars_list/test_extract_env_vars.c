/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_env_vars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:14:32 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 16:39:58 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_extract_env_vars_simple)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key1 = "USER";
	char *expected_value1 = "testuser";
	char *expected_key2 = "HOME";
	char *expected_value2 = "/home/testuser";
	char *expected_key3 = "PATH";
	char *expected_value3 = "/usr/bin:/bin";

	envp = malloc(4 * sizeof(char *));
	envp[0] = strdup("USER=testuser");
	envp[1] = strdup("HOME=/home/testuser");
	envp[2] = strdup("PATH=/usr/bin:/bin");
	envp[3] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 3);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key3);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value3);
	node = node->next;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key2);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value2);
	node = node->next;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key1);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value1);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 4);
}

MU_TEST(test_extract_env_vars_empty_value)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "EMPTY";
	char *expected_value = "";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("EMPTY=");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_no_value)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "NOVALUE";
	char *expected_value = "";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("NOVALUE");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_multiple_equals)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "MULTIPLE";
	char *expected_value = "equals=signs=here";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("MULTIPLE=equals=signs=here");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_special_characters)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "SPECIAL";
	char *expected_value = "!@#$%^&*()_+";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("SPECIAL=!@#$%^&*()_+");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_numeric_key)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "123KEY";
	char *expected_value = "numeric";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("123KEY=numeric");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_empty_key)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("=emptykey");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars == NULL);

	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_duplicate_keys)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "DUPLICATE";
	char *expected_value1 = "first";
	char *expected_value2 = "second";

	envp = malloc(3 * sizeof(char *));
	envp[0] = strdup("DUPLICATE=first");
	envp[1] = strdup("DUPLICATE=second");
	envp[2] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 2);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value2);
	node = node->next;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value1);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 3);
}

MU_TEST(test_extract_env_vars_mixed_case)
{
	// ARRANGE
	char **envp;
	t_list *env_vars;
	t_list *node;
	char *expected_key = "MixedCase";
	char *expected_value = "value";

	envp = malloc(2 * sizeof(char *));
	envp[0] = strdup("MixedCase=value");
	envp[1] = NULL;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars != NULL);
	mu_check(ft_lstsize(env_vars) == 1);

	node = env_vars;
	mu_assert_string_eq(((t_env_var *)node->content)->key, expected_key);
	mu_assert_string_eq(((t_env_var *)node->content)->value, expected_value);

	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_extract_env_vars_null_input)
{
	// ARRANGE
	char **envp = NULL;
	t_list *env_vars;

	// ACT
	env_vars = extract_env_vars(envp);

	// ASSERT
	mu_check(env_vars == NULL);
}

MU_TEST_SUITE(extract_env_vars_test_suite)
{
	MU_RUN_TEST(test_extract_env_vars_simple);
	MU_RUN_TEST(test_extract_env_vars_empty_value);
	MU_RUN_TEST(test_extract_env_vars_no_value);
	MU_RUN_TEST(test_extract_env_vars_multiple_equals);
	MU_RUN_TEST(test_extract_env_vars_special_characters);
	MU_RUN_TEST(test_extract_env_vars_null_input);
	MU_RUN_TEST(test_extract_env_vars_numeric_key);
	MU_RUN_TEST(test_extract_env_vars_empty_key);
	MU_RUN_TEST(test_extract_env_vars_duplicate_keys);
	MU_RUN_TEST(test_extract_env_vars_mixed_case);
}

int test_extract_env_vars(void)
{
	MU_RUN_SUITE(extract_env_vars_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

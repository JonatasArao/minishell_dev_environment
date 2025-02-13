/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 07:36:50 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/13 07:56:59 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_envp_simple)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"PATH=/usr/bin:/bin",
		"HOME=/home/testuser",
		"USER=testuser",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "USER", "testuser");
	lstadd_env_var(&env_vars, "HOME", "/home/testuser");
	lstadd_env_var(&env_vars, "PATH", "/usr/bin:/bin");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert_string_eq(envp[1], expected_envp[1]);
	mu_assert_string_eq(envp[2], expected_envp[2]);
	mu_assert(envp[3] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 3);
}

MU_TEST(test_get_envp_empty_value)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"EMPTY=",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "EMPTY", "");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_no_value)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"NOVALUE=",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "NOVALUE", "");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_multiple_equals)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"MULTIPLE=equals=signs=here",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "MULTIPLE", "equals=signs=here");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_special_characters)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"SPECIAL=!@#$%^&*()_+",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "SPECIAL", "!@#$%^&*()_+");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_numeric_key)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"123KEY=numeric",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "123KEY", "numeric");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_empty_key)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp = NULL;

	// ACT
	lstadd_env_var(&env_vars, "", "emptykey");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp == NULL);

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
}

MU_TEST(test_get_envp_duplicate_keys)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"DUPLICATE=second",
		"DUPLICATE=first",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "DUPLICATE", "first");
	lstadd_env_var(&env_vars, "DUPLICATE", "second");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert_string_eq(envp[1], expected_envp[1]);
	mu_assert(envp[2] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 2);
}

MU_TEST(test_get_envp_mixed_case)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp;
	char *expected_envp[] = {
		"MixedCase=value",
		NULL
	};

	// ACT
	lstadd_env_var(&env_vars, "MixedCase", "value");
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp != NULL);
	mu_assert_string_eq(envp[0], expected_envp[0]);
	mu_assert(envp[1] == NULL, "The envp array should end with a NULL pointer.");

	// CLEANUP
	ft_lstclear(&env_vars, free_env_var);
	ft_free_matrix((void **)envp, 1);
}

MU_TEST(test_get_envp_null_input)
{
	// ARRANGE
	t_list *env_vars = NULL;
	char **envp = NULL;

	// ACT
	envp = get_envp(env_vars);

	// ASSERT
	mu_check(envp == NULL);
}

MU_TEST_SUITE(get_envp_test_suite)
{
	MU_RUN_TEST(test_get_envp_simple);
	MU_RUN_TEST(test_get_envp_empty_value);
	MU_RUN_TEST(test_get_envp_no_value);
	MU_RUN_TEST(test_get_envp_multiple_equals);
	MU_RUN_TEST(test_get_envp_special_characters);
	MU_RUN_TEST(test_get_envp_null_input);
	MU_RUN_TEST(test_get_envp_numeric_key);
	MU_RUN_TEST(test_get_envp_empty_key);
	MU_RUN_TEST(test_get_envp_duplicate_keys);
	MU_RUN_TEST(test_get_envp_mixed_case);
}

int test_get_envp(void)
{
	MU_RUN_SUITE(get_envp_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

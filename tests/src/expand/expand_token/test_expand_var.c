/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:25:47 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/25 04:57:47 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_expand_var_simple)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("simple_test");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple_test", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_with_dollar_variable)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// Setup environment variable
	lstadd_env_var(&env_list, "USER", "testuser");

	// ACT
	var = ft_strdup("$USER");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("testuser", var);

	// CLEANUP
	free(var);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_var_with_exit_status)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	lstadd_env_var(&env_list, "USER", "testuser");
	var = ft_strdup("$?");

	expected_result = 1;
	actual_result = expand_var(env_list, 42, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("42", var);

	// CLEANUP
	free(var);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_var_with_single_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("'ls'");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("ls", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_with_single_quotes_and_var)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// Setup environment variable
	lstadd_env_var(&env_list, "USER", "testuser");

	// ACT
	var = ft_strdup("'$USER'");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("$USER", var);

	// CLEANUP
	free(var);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_var_with_double_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("\"ls\"");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("ls", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_with_double_quotes_on_start)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("\"ls");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("ls", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_with_double_quotes_on_end)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("ls\"");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("ls", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_unclosed_single_and_double_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("test'\"");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("test'", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_unclosed_double_and_single_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("test'\"");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("test'", var);

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_var_with_multiple_vars)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// Setup environment variables
	lstadd_env_var(&env_list, "USER", "testuser");
	lstadd_env_var(&env_list, "HOME", "/home/testuser");
	lstadd_env_var(&env_list, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin");

	// ACT
	var = ft_strdup("$USER");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("testuser", var);

	// CLEANUP
	free(var);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_var_only_dollar)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *var;
	int expected_result;
	int actual_result;

	// ACT
	var = ft_strdup("$");

	expected_result = 1;
	actual_result = expand_var(env_list, 0, &var);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("$", var);

	// CLEANUP
	free(var);
}

MU_TEST_SUITE(expand_var_test_suite)
{
	MU_RUN_TEST(test_expand_var_simple);
	MU_RUN_TEST(test_expand_var_with_dollar_variable);
	MU_RUN_TEST(test_expand_var_with_exit_status);
	MU_RUN_TEST(test_expand_var_with_single_quotes);
	MU_RUN_TEST(test_expand_var_with_single_quotes_and_var);
	MU_RUN_TEST(test_expand_var_with_double_quotes);
	MU_RUN_TEST(test_expand_var_with_double_quotes_on_start);
	MU_RUN_TEST(test_expand_var_with_double_quotes_on_end);
	MU_RUN_TEST(test_expand_var_unclosed_single_and_double_quotes);
	MU_RUN_TEST(test_expand_var_unclosed_double_and_single_quotes);
	MU_RUN_TEST(test_expand_var_with_multiple_vars);
	MU_RUN_TEST(test_expand_var_only_dollar);
}

int test_expand_var(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(expand_var_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}
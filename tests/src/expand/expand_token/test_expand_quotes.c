/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:25:47 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/19 14:59:51 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_expand_quotes_simple)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("simple_test");

	expected_result = "simple_test";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert(var == actual_result, "The variable and actual result should be the same pointer");

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_quotes_with_dollar_variable)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("$USER");
	expected_result = "$USER";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert(var == actual_result, "The variable and actual result should be the same pointer");

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_quotes_with_exit_status)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("$?");
	expected_result = "$?";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert(var == actual_result, "The variable and actual result should be the same pointer");

	// CLEANUP
	free(var);
}

MU_TEST(test_expand_quotes_with_single_quotes)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("'ls'");

	expected_result = "ls";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_with_single_quotes_and_var)
{
	// ARRANG
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("'$USER'");

	expected_result = "$USER";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_with_double_quotes)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("\"ls\"");

	expected_result = "ls";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_with_double_quotes_on_start)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("\"ls");

	expected_result = "ls";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_with_double_quotes_on_end)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("ls\"");

	expected_result = "ls";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_unclosed_single_and_double_quotes)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("test'\"");

	expected_result = "test'";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST(test_expand_quotes_unclosed_double_and_single_quotes)
{
	// ARRANGE
	char *var;
	char *expected_result;
	char *actual_result;

	// ACT
	var = ft_strdup("test'\"");

	expected_result = "test'";
	actual_result = expand_quotes(var);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(var);
	free(actual_result);
}

MU_TEST_SUITE(expand_quotes_test_suite)
{
	MU_RUN_TEST(test_expand_quotes_simple);
	MU_RUN_TEST(test_expand_quotes_with_dollar_variable);
	MU_RUN_TEST(test_expand_quotes_with_exit_status);
	MU_RUN_TEST(test_expand_quotes_with_single_quotes);
	MU_RUN_TEST(test_expand_quotes_with_single_quotes_and_var);
	MU_RUN_TEST(test_expand_quotes_with_double_quotes);
	MU_RUN_TEST(test_expand_quotes_with_double_quotes_on_start);
	MU_RUN_TEST(test_expand_quotes_with_double_quotes_on_end);
	MU_RUN_TEST(test_expand_quotes_unclosed_single_and_double_quotes);
	MU_RUN_TEST(test_expand_quotes_unclosed_double_and_single_quotes);
}

int test_expand_quotes(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(expand_quotes_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

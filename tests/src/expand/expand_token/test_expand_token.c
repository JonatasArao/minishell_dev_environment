/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:28:00 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/22 02:29:58 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_expand_token_single)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = "ls";
	actual_result = expand_token(env_list, last_status, "ls");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_expand_token_with_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = "quoted";
	actual_result = expand_token(env_list, last_status, "\"quoted\"");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_expand_token_with_single_quotes)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = "single";
	actual_result = expand_token(env_list, last_status, "'single'");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_expand_token_with_dollar)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "variable", "OK");

	// ACT
	expected_result = "OK";
	actual_result = expand_token(env_list, last_status, "$variable");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_with_dollar_and_space)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "var", "soc");

	// ACT
	expected_result = "soc iable";
	actual_result = expand_token(env_list, last_status, "$var iable");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_with_dollar_and_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "var", "soc");

	// ACT
	expected_result = "sociable";
	actual_result = expand_token(env_list, last_status, "$var\"iable\"");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_with_single_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "var", "soc");

	// ACT
	expected_result = "soc iable";
	actual_result = expand_token(env_list, last_status, "$var' iable'");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_within_single_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = "$var";
	actual_result = expand_token(env_list, last_status, "'$var'");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_expand_token_within_double_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "var", "test");

	// ACT
	expected_result = "test";
	actual_result = expand_token(env_list, last_status, "\"$var\"");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_single_quote_within_double_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// Setup environment variables
	lstadd_env_var(&env_list, "var", "test");

	// ACT
	expected_result = "'test'";
	actual_result = expand_token(env_list, last_status, "\"'$var'\"");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_double_quote_within_single_quote)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = "\"$var\"";
	actual_result = expand_token(env_list, last_status, "'\"$var\"'");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_expand_token_complex_string)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 42;

	// Setup environment variables
	lstadd_env_var(&env_list, "USER", "Barry");
	lstadd_env_var(&env_list, "NICK", "Flash");
	lstadd_env_var(&env_list, "SCHOOL", "42");
	lstadd_env_var(&env_list, "CITY", "Central City");

	// ACT
	expected_result = "Hello Barry'alias'Flash, Welcome to $SCHOOL in Central City . 42";
	actual_result = expand_token(env_list, last_status, "He\"ll\"o\" $USER'alias'\"\"$NICK\", Welcome to '$SCHOOL' in $CITY \".\" $?");

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_expand_token_empty)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	int last_status = 0;

	// ACT
	expected_result = NULL;
	actual_result = expand_token(env_list, last_status, "");

	// ASSERT
	mu_assert(expected_result == actual_result, "Expected NULL but got non-NULL");

	// CLEANUP
	free(actual_result);
}

MU_TEST_SUITE(expand_token_test_suite)
{
	MU_RUN_TEST(test_expand_token_single);
	MU_RUN_TEST(test_expand_token_with_quotes);
	MU_RUN_TEST(test_expand_token_with_single_quotes);
	MU_RUN_TEST(test_expand_token_with_dollar);
	MU_RUN_TEST(test_expand_token_with_dollar_and_space);
	MU_RUN_TEST(test_expand_token_with_dollar_and_quote);
	MU_RUN_TEST(test_expand_token_with_single_quote);
	MU_RUN_TEST(test_expand_token_within_single_quote);
	MU_RUN_TEST(test_expand_token_within_double_quote);
	MU_RUN_TEST(test_expand_token_single_quote_within_double_quote);
	MU_RUN_TEST(test_expand_token_double_quote_within_single_quote);
	MU_RUN_TEST(test_expand_token_complex_string);
	MU_RUN_TEST(test_expand_token_empty);
}

int test_expand_token(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(expand_token_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}
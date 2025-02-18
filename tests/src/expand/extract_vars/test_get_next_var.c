/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:08:46 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/18 22:16:55 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_next_var_word)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word";
	expected_result = "word";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_with_quotes)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "\"quoted\"";
	expected_result = "\"quoted\"";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_with_single_quotes)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "'single'";
	expected_result = "'single'";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_with_dollar)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "$variable";
	expected_result = "$variable";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_with_dollar_and_space)
{
	// ARRANGE
	char *expected_results[] = { "$var", " iable" };
	char *actual_results[2];
	char *input_string;
	size_t i;

	// ACT
	input_string = "$var iable";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 2)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 2)
		free(actual_results[i++]);
}
MU_TEST(test_get_next_var_end_with_dollar_and_quote)
{
	// ARRANGE
	char *expected_results[] = { "$var", "\"iable\"" };
	char *actual_results[2];
	char *input_string;
	size_t i;

	// ACT
	input_string = "$var\"iable\"";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 2)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 2)
		free(actual_results[i++]);
}

MU_TEST(test_get_next_var_end_with_single_quote)
{
	// ARRANGE
	char *expected_results[] = { "$var", "' iable'" };
	char *actual_results[2];
	char *input_string;
	size_t i;

	// ACT
	input_string = "$var' iable'";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 2)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 2)
		free(actual_results[i++]);
}

MU_TEST(test_get_next_var_end_within_single_quote)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "'$var'";
	expected_result = "'$var'";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_within_double_quote)
{
	// ARRANGE
	char *expected_results[] = { "\"", "$var", "\"" };
	char *actual_results[3];
	char *input_string;
	size_t i;

	// ACT
	input_string = "\"$var\"";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 3)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 3)
		free(actual_results[i++]);
}

MU_TEST(test_get_next_var_single_quote_within_double_quote)
{
	// ARRANGE
	char *expected_results[] = { "\"'", "$var", "'\"" };
	char *actual_results[3];
	char *input_string;
	size_t i;

	// ACT
	input_string = "\"'$var'\"";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 3)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 3)
		free(actual_results[i++]);
}

MU_TEST(test_get_next_var_double_quote_within_single_quote)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "'\"$var\"'";
	expected_result = "'\"$var\"'";
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_get_next_var_end_complex_string)
{
	// ARRANGE
	char *expected_results[] = {
		"He",
		"\"ll\"",
		"o",
		"\" ",
		"$USER",
		"'alias'\"",
		"\"",
		"$NICK",
		"\"",
		", Welcome to ",
		"'$SCHOOL'",
		" in ",
		"$CITY",
		" ",
		"\".\"",
		" ",
		"$?"
	};
	char *actual_results[17];
	char *input_string;
	size_t i;

	// ACT
	input_string = "He\"ll\"o\" $USER'alias'\"\"$NICK\", Welcome to '$SCHOOL' in $CITY \".\" $?";
	i = 0;
	while (*input_string)
	{
		actual_results[i] = get_next_var(input_string);
		input_string += strlen(actual_results[i]);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 17)
		mu_assert_string_eq(expected_results[i], actual_results[i++]);

	// CLEANUP
	i = 0;
	while (i < 17)
		free(actual_results[i++]);
}

MU_TEST(test_get_next_var_empty)
{
	// ARRANGE
	char *expected_result;
	char *actual_result;
	char *input_string;

	// ACT
	input_string = "";
	expected_result = NULL;
	actual_result = get_next_var(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}
MU_TEST_SUITE(get_next_var_test_suite)
{
	MU_RUN_TEST(test_get_next_var_word);
	MU_RUN_TEST(test_get_next_var_end_with_quotes);
	MU_RUN_TEST(test_get_next_var_end_with_single_quotes);
	MU_RUN_TEST(test_get_next_var_end_with_dollar);
	MU_RUN_TEST(test_get_next_var_end_with_dollar_and_space);
	MU_RUN_TEST(test_get_next_var_end_with_dollar_and_quote);
	MU_RUN_TEST(test_get_next_var_end_with_single_quote);
	MU_RUN_TEST(test_get_next_var_end_within_single_quote);
	MU_RUN_TEST(test_get_next_var_end_within_double_quote);
	MU_RUN_TEST(test_get_next_var_single_quote_within_double_quote);
	MU_RUN_TEST(test_get_next_var_double_quote_within_single_quote);
	MU_RUN_TEST(test_get_next_var_end_complex_string);
	MU_RUN_TEST(test_get_next_var_empty);
}

int	test_get_next_var(void)
{
	MU_RUN_SUITE(get_next_var_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_valid_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:53:45 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/05 18:07:11 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_is_valid_quotes_no_quotes_input)
{
	// ARRANGE
	const char	*input;
	int			actual_result;

	// ACT
	input = "echo Hello";
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert(actual_result != 0, "expected nonzero value");

}

MU_TEST(test_is_valid_quotes_unclosed_single_quote_input)
{
	// ARRANGE
	const char	*input;
	int			expected_result;
	int			actual_result;

	// ACT
	input = "'echo Hello";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_closed_single_quote_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo Hello'";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_unclosed_double_quote_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "\"echo Hello";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_closed_double_quote_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "\"echo Hello\"";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_mismatched_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo Hello\"";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_empty_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_only_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "''\"\"''";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_nested_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'\"echo Hello\"'";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_multiple_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo' 'Hello'";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_special_characters_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'!@#$%^&*()'";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_escape_sequence_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo \\'Hello\\''";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_long_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'This is a long input with multiple quotes and special characters!@#$%^&*()'";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_closed_and_unclosed_single_quote_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo' 'Hello";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_closed_and_unclosed_souble_quote_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "\"echo\" \"Hello";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_unclosed_double_quote_input_with_single_quote)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "\"echo Hello'";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_unclosed_single_quote_input_with_double_quote)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo Hello\"";
	expected_result = 0;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_multiple_unclosed_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo Hello\" '";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_valid_quotes_multiple_closed_quotes_input)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "'echo' \"Hello\"";
	expected_result = 1;
	actual_result = is_valid_quotes(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST_SUITE(is_valid_quotes_test_suite)
{
	MU_RUN_TEST(test_is_valid_quotes_no_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_unclosed_single_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_closed_single_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_unclosed_double_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_closed_double_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_mismatched_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_empty_input);
	MU_RUN_TEST(test_is_valid_quotes_only_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_nested_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_multiple_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_special_characters_input);
	MU_RUN_TEST(test_is_valid_quotes_escape_sequence_input);
	MU_RUN_TEST(test_is_valid_quotes_long_input);
	MU_RUN_TEST(test_is_valid_quotes_closed_and_unclosed_single_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_closed_and_unclosed_souble_quote_input);
	MU_RUN_TEST(test_is_valid_quotes_unclosed_double_quote_input_with_single_quote);
	MU_RUN_TEST(test_is_valid_quotes_unclosed_single_quote_input_with_double_quote);
	MU_RUN_TEST(test_is_valid_quotes_multiple_unclosed_quotes_input);
	MU_RUN_TEST(test_is_valid_quotes_multiple_closed_quotes_input);
}

int test_is_valid_quotes(void)
{
	MU_RUN_SUITE(is_valid_quotes_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

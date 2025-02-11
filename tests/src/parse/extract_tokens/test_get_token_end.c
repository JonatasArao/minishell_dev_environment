/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_token_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:01 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 10:07:31 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_token_end_double_greater)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = ">> file";
	expected_result = 2;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_single_greater)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "> file";
	expected_result = 1;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_word)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word";
	expected_result = 4;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_quoted_word)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "\"quoted word\"";
	expected_result = 13;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_single_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "'single quote'";
	expected_result = 14;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_mixed_quotes)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "\"mixed 'quotes'\"";
	expected_result = 16;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_pipe)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "| command";
	expected_result = 1;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_dollar)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$variable";
	expected_result = 9;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_whitespace)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "   ";
	expected_result = 0;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_mixed_characters)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1|word2";
	expected_result = 5;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_multiple_spaces)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word   word";
	expected_result = 4;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_special_characters)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "@#$%^&*()";
	expected_result = 9;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_empty_string)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "";
	expected_result = 0;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_middle)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1 word2";
	expected_result = 11;
	actual_result = get_token_end(input, 6);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_special_character)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1|word2";
	expected_result = 11;
	actual_result = get_token_end(input, 6);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_whitespace)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1   word2";
	expected_result = 6;
	actual_result = get_token_end(input, 6);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1 \"quoted word\"";
	expected_result = 19;
	actual_result = get_token_end(input, 6);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_dollar)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1 $variable";
	expected_result = 15;
	actual_result = get_token_end(input, 6);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_end)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1";
	expected_result = 5;
	actual_result = get_token_end(input, 5);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_beyond_end)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word1";
	expected_result = 10;
	actual_result = get_token_end(input, 10);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_empty_string)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "";
	expected_result = 0;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_single_character)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "a";
	expected_result = 1;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_get_token_end_start_at_single_whitespace)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = " ";
	expected_result = 0;
	actual_result = get_token_end(input, 0);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST_SUITE(get_token_end_test_suite)
{
	MU_RUN_TEST(test_get_token_end_double_greater);
	MU_RUN_TEST(test_get_token_end_single_greater);
	MU_RUN_TEST(test_get_token_end_word);
	MU_RUN_TEST(test_get_token_end_quoted_word);
	MU_RUN_TEST(test_get_token_end_single_quote);
	MU_RUN_TEST(test_get_token_end_mixed_quotes);
	MU_RUN_TEST(test_get_token_end_pipe);
	MU_RUN_TEST(test_get_token_end_dollar);
	MU_RUN_TEST(test_get_token_end_whitespace);
	MU_RUN_TEST(test_get_token_end_mixed_characters);
	MU_RUN_TEST(test_get_token_end_multiple_spaces);
	MU_RUN_TEST(test_get_token_end_special_characters);
	MU_RUN_TEST(test_get_token_end_empty_string);
	MU_RUN_TEST(test_get_token_end_start_at_middle);
	MU_RUN_TEST(test_get_token_end_start_at_special_character);
	MU_RUN_TEST(test_get_token_end_start_at_whitespace);
	MU_RUN_TEST(test_get_token_end_start_at_quote);
	MU_RUN_TEST(test_get_token_end_start_at_dollar);
	MU_RUN_TEST(test_get_token_end_start_at_end);
	MU_RUN_TEST(test_get_token_end_start_beyond_end);
	MU_RUN_TEST(test_get_token_end_start_at_empty_string);
	MU_RUN_TEST(test_get_token_end_start_at_single_character);
	MU_RUN_TEST(test_get_token_end_start_at_single_whitespace);
}

int	test_get_token_end(void)
{
	MU_RUN_SUITE(get_token_end_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

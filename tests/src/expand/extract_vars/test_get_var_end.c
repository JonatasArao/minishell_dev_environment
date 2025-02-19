/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_var_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:10:11 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/19 14:24:31 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_var_end_word)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "word";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_quotes)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "\"quoted\"";
	expected_result = 8;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_single_quotes)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "'single'";
	expected_result = 8;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_dollar)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$variable";
	expected_result = 9;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_dollar_and_space)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_dollar_and_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var\"iable\"";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_single_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var' iable'";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_semicolon)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var;iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_parentheses)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var(iable)";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_square_brackets)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var[iable]";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_curly_braces)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var{iable}";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_plus)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var+iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_minus)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var-iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_asterisk)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var*iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_slash)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var/iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_with_equal)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "$var=iable";
	expected_result = 4;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_within_single_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "'$var'";
	expected_result = 6;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_within_double_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "\"$var\"";
	expected_result = 1;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_single_quote_within_double_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "\"'$var'\"";
	expected_result = 2;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_double_quote_within_single_quote)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "'\"$var\"'";
	expected_result = 8;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST(test_get_var_end_complex_string)
{
	// ARRANGE
	const char *input;
	size_t actual_values[16];
	size_t processed;
	size_t i;
	int expected_values[] = {
		2, 4, 1, 2, 5, 8, 1, 5, 1, 13, 9, 4, 5, 1, 3, 1, 2
	};

	// ACT
	input = "He\"ll\"o\" $USER'Vulgo'\"\"$NICK\", Welcome to '$SCHOOL' in $CITY \".\" $?";
	processed = 0;
	i = 0;
	while (processed < strlen(input))
	{
		actual_values[i] = get_var_end(input + processed);
		processed += actual_values[i];
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 16) {
		mu_assert_int_eq(expected_values[i], actual_values[i]);
		i++;
	}
}

MU_TEST(test_get_var_end_empty)
{
	// ARRANGE
	const char *input;
	size_t expected_result;
	size_t actual_result;

	// ACT
	input = "";
	expected_result = 0;
	actual_result = get_var_end(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	while (actual_result < strlen(input))
		actual_result += get_var_end(input + actual_result);
}

MU_TEST_SUITE(get_var_end_test_suite)
{
	MU_RUN_TEST(test_get_var_end_word);
	MU_RUN_TEST(test_get_var_end_with_quotes);
	MU_RUN_TEST(test_get_var_end_with_single_quotes);
	MU_RUN_TEST(test_get_var_end_with_dollar);
	MU_RUN_TEST(test_get_var_end_with_dollar_and_space);
	MU_RUN_TEST(test_get_var_end_with_dollar_and_quote);
	MU_RUN_TEST(test_get_var_end_with_single_quote);
	MU_RUN_TEST(test_get_var_end_with_semicolon);
	MU_RUN_TEST(test_get_var_end_with_parentheses);
	MU_RUN_TEST(test_get_var_end_with_square_brackets);
	MU_RUN_TEST(test_get_var_end_with_curly_braces);
	MU_RUN_TEST(test_get_var_end_with_plus);
	MU_RUN_TEST(test_get_var_end_with_minus);
	MU_RUN_TEST(test_get_var_end_with_asterisk);
	MU_RUN_TEST(test_get_var_end_with_slash);
	MU_RUN_TEST(test_get_var_end_with_equal);
	MU_RUN_TEST(test_get_var_end_within_single_quote);
	MU_RUN_TEST(test_get_var_end_within_double_quote);
	MU_RUN_TEST(test_get_var_end_single_quote_within_double_quote);
	MU_RUN_TEST(test_get_var_end_double_quote_within_single_quote);
	MU_RUN_TEST(test_get_var_end_complex_string);
	MU_RUN_TEST(test_get_var_end_empty);
}

int	test_get_var_end(void)
{
	MU_RUN_SUITE(get_var_end_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

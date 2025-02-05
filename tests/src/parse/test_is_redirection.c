/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:17:36 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/05 15:41:19 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_is_redirection_arg_token)
{
	// ARRANGE
	const char	*input;
	int			expected_result;
	int			actual_result;

	// ACT
	input = "word";
	expected_result = 0;
	actual_result = is_redirection(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_redirection_double_greater)
{
	// ARRANGE
	const char	*input;
	int			actual_result;

	// ACT
	input = ">>";
	actual_result = is_redirection(input);

	// ASSERT
	mu_assert(actual_result != 0, "expected nonzero value");
}
MU_TEST(test_is_redirection_double_less)
{
	// ARRANGE
	const char *input;
	int actual_result;

	// ACT
	input = "<<";
	actual_result = is_redirection(input);

	// ASSERT
	mu_assert(actual_result != 0, "expected nonzero value");
}

MU_TEST(test_is_redirection_single_less)
{
	// ARRANGE
	const char *input;
	int actual_result;

	// ACT
	input = "<";
	actual_result = is_redirection(input);

	// ASSERT
	mu_assert(actual_result != 0, "expected nonzero value");
}

MU_TEST(test_is_redirection_single_greater)
{
	// ARRANGE
	const char *input;
	int actual_result;

	// ACT
	input = ">";
	actual_result = is_redirection(input);

	// ASSERT
	mu_assert(actual_result != 0, "expected nonzero value");
}

MU_TEST(test_is_redirection_three_less)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<<<";
	actual_result = is_redirection(input);
	expected_result = 0;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_redirection_empty_string)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "";
	actual_result = is_redirection(input);
	expected_result = 0;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_redirection_invalid_characters)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "!@#$";
	actual_result = is_redirection(input);
	expected_result = 0;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_redirection_mixed_characters)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<>";
	actual_result = is_redirection(input);
	expected_result = 0;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST_SUITE(is_redirection_test_suite)
{
	MU_RUN_TEST(test_is_redirection_arg_token);
	MU_RUN_TEST(test_is_redirection_double_greater);
	MU_RUN_TEST(test_is_redirection_double_less);
	MU_RUN_TEST(test_is_redirection_single_less);
	MU_RUN_TEST(test_is_redirection_single_greater);
	MU_RUN_TEST(test_is_redirection_three_less);
	MU_RUN_TEST(test_is_redirection_empty_string);
	MU_RUN_TEST(test_is_redirection_invalid_characters);
	MU_RUN_TEST(test_is_redirection_mixed_characters);
}

int test_is_redirection(void)
{
	MU_RUN_SUITE(is_redirection_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

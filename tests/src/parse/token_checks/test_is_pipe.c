/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:17:36 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:32 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_is_pipe_pipe)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "|";
	expected_result = 1;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_arg_token)
{
	// ARRANGE
	const char	*input;
	int			expected_result;
	int			actual_result;

	// ACT
	input = "word";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_double_greater)
{
	// ARRANGE
	const char	*input;
	int			expected_result;
	int			actual_result;

	// ACT
	input = ">>";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_double_less)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<<";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_single_less)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_single_greater)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = ">";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_three_less)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<<<";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_empty_string)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_invalid_characters)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "!@#$";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_pipe_mixed_characters)
{
	// ARRANGE
	const char *input;
	int expected_result;
	int actual_result;

	// ACT
	input = "<>";
	expected_result = 0;
	actual_result = is_pipe(input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST_SUITE(is_pipe_test_suite)
{
	MU_RUN_TEST(test_is_pipe_pipe);
	MU_RUN_TEST(test_is_pipe_arg_token);
	MU_RUN_TEST(test_is_pipe_double_greater);
	MU_RUN_TEST(test_is_pipe_double_less);
	MU_RUN_TEST(test_is_pipe_single_less);
	MU_RUN_TEST(test_is_pipe_single_greater);
	MU_RUN_TEST(test_is_pipe_three_less);
	MU_RUN_TEST(test_is_pipe_empty_string);
	MU_RUN_TEST(test_is_pipe_invalid_characters);
	MU_RUN_TEST(test_is_pipe_mixed_characters);
}

int test_is_pipe(void)
{
	MU_RUN_SUITE(is_pipe_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

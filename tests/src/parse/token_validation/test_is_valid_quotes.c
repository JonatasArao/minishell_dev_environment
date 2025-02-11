/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_valid_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:53:45 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 11:22:29 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_is_valid_quotes_result capture_is_valid_quotes_output(const char *s, int fd)
{
	t_is_valid_quotes_result result;
	int pipefd[2];
	ssize_t count;
	char *buffer;
	size_t size = 1024; // Initial buffer size

	// Create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		result.return_value = 0;
		result.output = NULL;
		return (result);
	}

	// Save the original file descriptor of fd
	int fd_backup = dup(fd);

	// Save the original file descriptors of stdout and stderr
	int stdout_backup = dup(1);
	int stderr_backup = dup(2);

	// Redirect fd to the pipe
	dup2(pipefd[1], fd);
	close(pipefd[1]);

	// Close the opposite file descriptor to avoid mixed output
	if (fd == 1)
	{
		close(2); // Close stderr if fd is stdout
	}
	else if (fd == 2)
	{
		close(1); // Close stdout if fd is stderr
	}
	else
	{
		close(1);
		close(2);
	}

	// Call the function whose output we want to capture
	result.return_value = is_valid_quotes(s);

	// Restore fd
	fflush(stdout);
	dup2(fd_backup, fd);
	close(fd_backup);

	// Restore stdout and stderr
	dup2(stdout_backup, 1);
	dup2(stderr_backup, 2);
	close(stdout_backup);
	close(stderr_backup);

	// Dynamically allocate the buffer
	buffer = (char*)malloc(size);
	if (buffer == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// Read the content from the pipe
	count = read(pipefd[0], buffer, size - 1);
	if (count == -1) {
		perror("read");
		free(buffer);
		result.return_value = 0;
		result.output = NULL;
		exit(EXIT_FAILURE);
	}
	buffer[count] = '\0';

	// Close the read end of the pipe
	close(pipefd[0]);

	result.output = buffer;

	return (result);
}

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
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "'echo Hello";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
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
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "\"echo Hello";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `\"'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
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
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "'echo Hello\"";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
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
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "'echo' 'Hello";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_is_valid_quotes_closed_and_unclosed_souble_quote_input)
{
	// ARRANGE
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "\"echo\" \"Hello";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `\"'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_is_valid_quotes_unclosed_double_quote_input_with_single_quote)
{
	// ARRANGE
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "\"echo Hello'";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `\"'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_is_valid_quotes_unclosed_single_quote_input_with_double_quote)
{
	// ARRANGE
	t_is_valid_quotes_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	const char *input;

	// ACT
	input = "'echo Hello\"";
	result = capture_is_valid_quotes_output(input, 2);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
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

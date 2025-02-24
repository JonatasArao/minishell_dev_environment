/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_msh_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:00:38 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/24 20:42:04 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_msh_echo_result capture_msh_echo_output(t_command *cmd, int fd)
{
	t_msh_echo_result result;
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
	result.return_value = msh_echo(cmd);
	ft_putchar_fd('\0', fd);

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

MU_TEST(test_msh_echo_no_arguments)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_single_argument)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "hello");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "hello\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_multiple_arguments)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "hello");
	lstadd_str(&cmd->arguments, "world");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "hello world\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_with_newline_option)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "-n");
	lstadd_str(&cmd->arguments, "hello");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "hello";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_with_special_characters)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "hello");
	lstadd_str(&cmd->arguments, "world!");
	lstadd_str(&cmd->arguments, "@#$%^&*()");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "hello world! @#$%^&*()\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_with_empty_string)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST(test_msh_echo_with_multiple_newline_options)
{
	// ARRANGE
	t_msh_echo_result result;
	t_command	*cmd;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	cmd = alloc_command();
	lstadd_str(&cmd->arguments, "echo");
	lstadd_str(&cmd->arguments, "-n");
	lstadd_str(&cmd->arguments, "-n");
	lstadd_str(&cmd->arguments, "hello");
	result = capture_msh_echo_output(cmd, 1);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "hello";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	free_command(cmd);
}

MU_TEST_SUITE(msh_echo_test_suite)
{
	MU_RUN_TEST(test_msh_echo_no_arguments);
	MU_RUN_TEST(test_msh_echo_single_argument);
	MU_RUN_TEST(test_msh_echo_multiple_arguments);
	MU_RUN_TEST(test_msh_echo_with_newline_option);
	MU_RUN_TEST(test_msh_echo_with_special_characters);
	MU_RUN_TEST(test_msh_echo_with_empty_string);
	MU_RUN_TEST(test_msh_echo_with_multiple_newline_options);
}

int test_msh_echo(void)
{
	MU_RUN_SUITE(msh_echo_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
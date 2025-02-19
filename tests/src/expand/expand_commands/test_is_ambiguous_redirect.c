/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_ambiguous_redirect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:35:20 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/19 17:57:02 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_is_ambiguous_redirect_result capture_is_ambiguous_redirect_output(char *old_target, char *new_target, int fd)
{
	t_is_ambiguous_redirect_result result;
	int pipefd[2];
	ssize_t count;
	char *buffer;
	size_t size = 1024; // Initial buffer size

	// Create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		result.return_value = -1;
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
	result.return_value = is_ambiguous_redirect(old_target, new_target);

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

MU_TEST(test_is_ambiguous_redirect_valid)
{
	// ARRANGE
	char	*old_target;
	char	*new_target;
	int		expected_result;
	int		actual_result;

	// ACT
	old_target = "file.txt";
	new_target = "file.txt";
	expected_result = 0;
	actual_result = is_ambiguous_redirect(old_target, new_target);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_ambiguous_redirect_empty_new_target)
{
	// ARRANGE
	t_is_ambiguous_redirect_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	char *old_target;
	char *new_target;

	// ACT
	old_target = "$FILE";
	new_target = "";
	result = capture_is_ambiguous_redirect_output(old_target, new_target, 2);
	expected_result = 1;
	actual_result = result.return_value;
	actual_output = "minishell: $FILE: ambiguous redirect\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_is_ambiguous_redirect_new_target_with_space)
{
	// ARRANGE
	t_is_ambiguous_redirect_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	char *old_target;
	char *new_target;

	// ACT
	old_target = "$REDIRFILE";
	new_target = "redirect file.txt";
	result = capture_is_ambiguous_redirect_output(old_target, new_target, 2);
	expected_result = 1;
	actual_result = result.return_value;
	actual_output = "minishell: $REDIRFILE: ambiguous redirect\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST_SUITE(is_ambiguous_redirect_test_suite)
{
	MU_RUN_TEST(test_is_ambiguous_redirect_valid);
	MU_RUN_TEST(test_is_ambiguous_redirect_empty_new_target);
	MU_RUN_TEST(test_is_ambiguous_redirect_new_target_with_space);
}

int test_is_ambiguous_redirect(void)
{
	MU_RUN_SUITE(is_ambiguous_redirect_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

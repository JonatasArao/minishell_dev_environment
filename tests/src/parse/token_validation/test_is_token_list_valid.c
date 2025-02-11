/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_token_list_valid.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:02:08 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 08:50:07 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_is_token_list_valid_result capture_is_token_list_valid_output(t_list *tokens, int fd)
{
	t_is_token_list_valid_result result;
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
	result.return_value = is_token_list_valid(tokens);

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

void do_nothing(void *content)
{
	(void)content;
}

MU_TEST(test_is_token_list_valid_with_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_syntax)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_trailing_pipe)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_multiple_pipes)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("wc"));
	ft_lstadd_back(&tokens, ft_lstnew("-l"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_multiple_redirections)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file1.txt"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file2.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `>'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_empty_list)
{
	// ARRANGE
	t_list	*tokens = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
}

MU_TEST(test_is_token_list_valid_with_single_command)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("ls");
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe_and_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("output.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_pipe_and_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("output.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_only_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew(">");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_only_pipe)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("|");
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_double_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_double_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `>>'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_pipe_and_double_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("output.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_pipe_and_double_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("output.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_only_double_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew(">>");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_only_invalid_double_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew(">>");
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `>>'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_double_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_input_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `<'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_invalid_double_input_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `<<'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_pipe_and_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe_and_double_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_pipe_and_input_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_invalid_pipe_and_double_input_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_starting_pipe)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("|");
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `|'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_starting_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew(">");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_starting_double_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew(">>");
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe_followed_by_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("ls");
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe_followed_by_double_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("ls");
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	expected_result = 1;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_pipe_followed_by_invalid_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("ls");
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(& tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `>'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST(test_is_token_list_valid_with_pipe_followed_by_invalid_double_redirection)
{
	// ARRANGE
	t_is_token_list_valid_result result;
	t_list	*tokens;
	int		expected_result;
	int		actual_result;
	char	*expected_output;
	char	*actual_output;

	// ACT
	tokens = ft_lstnew("ls");
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file"));
	result = capture_is_token_list_valid_output(tokens, 1);
	expected_result = 0;
	actual_result = result.return_value;
	actual_output = "minishell: syntax error near token `>>'\n";
	expected_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
	free(expected_output);
}

MU_TEST_SUITE(is_token_list_valid_test_suite)
{
	MU_RUN_TEST(test_is_token_list_valid_with_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_syntax);
	MU_RUN_TEST(test_is_token_list_valid_with_trailing_pipe);
	MU_RUN_TEST(test_is_token_list_valid_with_multiple_pipes);
	MU_RUN_TEST(test_is_token_list_valid_with_multiple_redirections);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_empty_list);
	MU_RUN_TEST(test_is_token_list_valid_with_single_command);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_and_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_pipe_and_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_only_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_only_pipe);
	MU_RUN_TEST(test_is_token_list_valid_with_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_and_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_pipe_and_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_only_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_only_invalid_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_double_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_double_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_and_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_and_double_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_pipe_and_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_invalid_pipe_and_double_input_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_starting_pipe);
	MU_RUN_TEST(test_is_token_list_valid_with_starting_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_starting_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_followed_by_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_followed_by_double_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_followed_by_invalid_redirection);
	MU_RUN_TEST(test_is_token_list_valid_with_pipe_followed_by_invalid_double_redirection);
}

int test_is_token_list_valid(void)
{
	MU_RUN_SUITE(is_token_list_valid_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

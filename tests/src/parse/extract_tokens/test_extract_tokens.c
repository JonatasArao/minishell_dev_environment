/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:32:11 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 11:35:43 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_extract_tokens_result capture_extract_tokens_output(const char *s, int fd)
{
	t_extract_tokens_result result;
	int pipefd[2];
	ssize_t count;
	char *buffer;
	size_t size = 1024; // Initial buffer size

	// Create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		result.return_value = NULL;
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
	result.return_value = extract_tokens(s);

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
		result.return_value = NULL;
		result.output = NULL;
		exit(EXIT_FAILURE);
	}
	buffer[count] = '\0';

	// Close the read end of the pipe
	close(pipefd[0]);

	result.output = buffer;

	return (result);
}

MU_TEST(test_extract_tokens_word)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word";
	expected_result = ft_lstnew(strdup("word"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_multiple_words)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word1 word2";
	expected_result = ft_lstnew(strdup("word1"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("word2")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_leading_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "   word";
	expected_result = ft_lstnew(strdup("word"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_empty_string)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "";
	expected_result = NULL;
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_check(expected_result == actual_result);
}

MU_TEST(test_extract_tokens_only_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "     ";
	expected_result = NULL;
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_check(expected_result == actual_result);
}

MU_TEST(test_extract_tokens_with_trailing_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word   ";
	expected_result = ft_lstnew(strdup("word"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_special_characters)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word!@#";
	expected_result = ft_lstnew(strdup("word!@#"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_newline)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word\nnext";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("next")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_tabs)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\tword";
	expected_result = ft_lstnew(strdup("word"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_mixed_whitespace)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = " \t\n word";
	expected_result = ft_lstnew(strdup("word"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_single_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'single quoted'";
	expected_result = ft_lstnew(strdup("'single quoted'"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_double_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"double quoted\"";
	expected_result = ft_lstnew(strdup("\"double quoted\""));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_redirection)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word > file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word | next";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("|")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("next")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_double_redirection)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word >> file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">>")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_input_redirection)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word < file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("<")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe_and_redirection)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word | next > file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("|")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("next")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->next->content,
		(char *) actual_result->next->next->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->next->next->content,
		(char *) actual_result->next->next->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_redirection_no_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word>file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe_no_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word|next";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("|")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("next")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_double_redirection_no_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word>>file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">>")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_input_redirection_no_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word<file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("<")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe_and_redirection_no_spaces)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word|next>file";
	expected_result = ft_lstnew(strdup("word"));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("|")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("next")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup(">")));
	ft_lstadd_back(&expected_result, ft_lstnew(strdup("file")));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);
	mu_assert_string_eq((char *) expected_result->next->content,
		(char *) actual_result->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->content,
		(char *) actual_result->next->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->next->content,
		(char *) actual_result->next->next->next->content);
	mu_assert_string_eq((char *) expected_result->next->next->next->next->content,
		(char *) actual_result->next->next->next->next->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe_inside_single_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'word|next'";
	expected_result = ft_lstnew(strdup("'word|next'"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_pipe_inside_double_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"word|next\"";
	expected_result = ft_lstnew(strdup("\"word|next\""));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_redirection_inside_single_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'word>file'";
	expected_result = ft_lstnew(strdup("'word>file'"));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_with_redirection_inside_double_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"word>file\"";
	expected_result = ft_lstnew(strdup("\"word>file\""));
	actual_result = extract_tokens(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_tokens_unclosed_single_quotes)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed single quotes";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_double_quotes)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "\"unclosed double quotes";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `\"'\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with spaces";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_special_characters)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with special characters!@#";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_newline)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with newline\nnext";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_tabs)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with tabs\tword";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_mixed_whitespace)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with mixed whitespace \t\n word";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_redirection)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with redirection > file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_pipe)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with pipe | next";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_double_redirection)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with double redirection >> file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_input_redirection)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with input redirection < file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_pipe_and_redirection)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with pipe and redirection | next > file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_redirection_no_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with redirection no spaces>file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_pipe_no_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with pipe no spaces|next";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_double_redirection_no_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with double redirection no spaces>>file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_input_redirection_no_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with input redirection no spaces<file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST(test_extract_tokens_unclosed_quotes_with_pipe_and_redirection_no_spaces)
{
	// ARRANGE
	t_extract_tokens_result result;
	t_list *expected_result;
	t_list *actual_result;
	char *expected_output;
	char *actual_output;
	char *input_string;

	// ACT
	input_string = "'unclosed quotes with pipe and redirection no spaces|next>file";
	result = capture_extract_tokens_output(input_string, 1);
	expected_result = NULL;
	actual_result = result.return_value;
	actual_output = "minishell: unexpected EOF for `''\n";
	expected_output = result.output;

	// ASSERT
	mu_check(expected_result == actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(expected_output);
}

MU_TEST_SUITE(extract_tokens_test_suite)
{
	MU_RUN_TEST(test_extract_tokens_word);
	MU_RUN_TEST(test_extract_tokens_multiple_words);
	MU_RUN_TEST(test_extract_tokens_with_leading_spaces);
	MU_RUN_TEST(test_extract_tokens_empty_string);
	MU_RUN_TEST(test_extract_tokens_only_spaces);
	MU_RUN_TEST(test_extract_tokens_with_trailing_spaces);
	MU_RUN_TEST(test_extract_tokens_with_special_characters);
	MU_RUN_TEST(test_extract_tokens_with_newline);
	MU_RUN_TEST(test_extract_tokens_with_tabs);
	MU_RUN_TEST(test_extract_tokens_with_mixed_whitespace);
	MU_RUN_TEST(test_extract_tokens_with_single_quotes);
	MU_RUN_TEST(test_extract_tokens_with_double_quotes);
	MU_RUN_TEST(test_extract_tokens_with_redirection);
	MU_RUN_TEST(test_extract_tokens_with_pipe);
	MU_RUN_TEST(test_extract_tokens_with_double_redirection);
	MU_RUN_TEST(test_extract_tokens_with_input_redirection);
	MU_RUN_TEST(test_extract_tokens_with_pipe_and_redirection);
	MU_RUN_TEST(test_extract_tokens_with_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_with_pipe_no_spaces);
	MU_RUN_TEST(test_extract_tokens_with_double_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_with_input_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_with_pipe_and_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_with_pipe_inside_single_quotes);
	MU_RUN_TEST(test_extract_tokens_with_pipe_inside_double_quotes);
	MU_RUN_TEST(test_extract_tokens_with_redirection_inside_single_quotes);
	MU_RUN_TEST(test_extract_tokens_with_redirection_inside_double_quotes);
	MU_RUN_TEST(test_extract_tokens_unclosed_single_quotes);
	MU_RUN_TEST(test_extract_tokens_unclosed_double_quotes);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_spaces);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_special_characters);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_newline);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_tabs);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_mixed_whitespace);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_redirection);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_pipe);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_double_redirection);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_input_redirection);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_pipe_and_redirection);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_pipe_no_spaces);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_double_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_input_redirection_no_spaces);
	MU_RUN_TEST(test_extract_tokens_unclosed_quotes_with_pipe_and_redirection_no_spaces);
}

int	test_extract_tokens(void)
{
	MU_RUN_SUITE(extract_tokens_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

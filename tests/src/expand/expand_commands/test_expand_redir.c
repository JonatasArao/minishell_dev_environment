/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:35:20 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/20 12:02:17 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_expand_redir_result capture_expand_redir_output(t_list *env, int last_status, t_list *redir, int fd)
{
	t_expand_redir_result result;
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
	result.return_value = expand_redir(env, last_status, redir);

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

MU_TEST(test_expand_redir_type_overwrite_target_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">", "simple");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_overwrite_target_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">", "'single_quote'");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_overwrite_target_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">", "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_overwrite_target_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_redir(&redir, ">", "$HOME");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("/home/user", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_overwrite_target_variable_with_space_char)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_env_var(&env, "TARGET", "file name.txt");
	lstadd_redir(&redir, ">", "$TARGET");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $TARGET: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_overwrite_target_non_existing_variable)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_redir(&redir, ">", "$VAR");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $VAR: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_append_target_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">>", "simple");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_append_target_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">>", "'single_quote'");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_append_target_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, ">>", "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_append_target_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_redir(&redir, ">>", "$HOME");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("/home/user", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_append_target_variable_with_space_char)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_env_var(&env, "TARGET", "file name.txt");
	lstadd_redir(&redir, ">>", "$TARGET");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $TARGET: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_append_target_non_existing_variable)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_redir(&redir, ">>", "$VAR");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $VAR: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_simple_input_target_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<", "simple");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_simple_input_target_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<", "'single_quote'");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_simple_input_target_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<", "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_simple_input_target_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_redir(&redir, "<", "$HOME");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("/home/user", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_simple_input_target_variable_with_space_char)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_env_var(&env, "TARGET", "file name.txt");
	lstadd_redir(&redir, "<", "$TARGET");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $TARGET: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_simple_input_target_non_existing_variable)
{
	// ARRANGE
	t_expand_redir_result result;
	int expected_result;
	int actual_result;
	char *expected_output;
	char *actual_output;
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;

	// ACT
	lstadd_redir(&redir, "<", "$VAR");
	result = capture_expand_redir_output(env, last_status, redir, 2);
	expected_result = 0;
	actual_result = result.return_value;
	expected_output = "minishell: $VAR: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	free(actual_output);
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_heredoc_target_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<<", "simple");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_heredoc_target_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<<", "'single_quote'");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("'single_quote'", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_heredoc_target_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<<", "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("\"double_quote\"", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
}

MU_TEST(test_expand_redir_type_heredoc_target_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_redir(&redir, "<<", "$HOME");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("$HOME", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_heredoc_target_variable_with_space_char)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "TARGET", "file name.txt");
	lstadd_redir(&redir, "<<", "$TARGET");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("$TARGET", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_type_heredoc_target_non_existing_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*redir = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_redir(&redir, "<<", "$VAR");
	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("$VAR", ((t_redirection *)redir->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_input_type_all_cases)
{
	// ARRANGE
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;
	int expected_result;
	int actual_result;

	// ACT
	lstadd_env_var(&env, "VAR1", "file.txt");
	lstadd_env_var(&env, "VAR2", "EOF");

	lstadd_redir(&redir, "<", "simple");
	lstadd_redir(&redir, "<", "'single_quote'");
	lstadd_redir(&redir, "<", "\"double_quote\"");
	lstadd_redir(&redir, "<", "$VAR1");
	lstadd_redir(&redir, "<<", "simple");
	lstadd_redir(&redir, "<<", "'single_quote'");
	lstadd_redir(&redir, "<<", "\"double_quote\"");
	lstadd_redir(&redir, "<<", "$VAR2");

	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);
	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->next->content)->target);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->next->next->content)->target);
	mu_assert_string_eq("file.txt", ((t_redirection *)redir->next->next->next->content)->target);
	mu_assert_string_eq("simple", ((t_redirection *)redir->next->next->next->next->content)->target);
	mu_assert_string_eq("'single_quote'", ((t_redirection *)redir->next->next->next->next->next->content)->target);
	mu_assert_string_eq("\"double_quote\"", ((t_redirection *)redir->next->next->next->next->next->next->content)->target);
	mu_assert_string_eq("$VAR2", ((t_redirection *)redir->next->next->next->next->next->next->next->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_redir_output_type_all_cases)
{
	// ARRANGE
	t_list *env = NULL;
	int last_status = 0;
	t_list *redir = NULL;
	int expected_result;
	int actual_result;

	// ACT
	lstadd_env_var(&env, "VAR1", "file.txt");
	lstadd_env_var(&env, "VAR2", "file_2.txt");

	lstadd_redir(&redir, ">", "simple");
	lstadd_redir(&redir, ">", "'single_quote'");
	lstadd_redir(&redir, ">", "\"double_quote\"");
	lstadd_redir(&redir, ">", "$VAR1");
	lstadd_redir(&redir, ">>", "simple");
	lstadd_redir(&redir, ">>", "'single_quote'");
	lstadd_redir(&redir, ">>", "\"double_quote\"");
	lstadd_redir(&redir, ">>", "$VAR2");

	expected_result = 1;
	actual_result = expand_redir(env, last_status, redir);
	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", ((t_redirection *)redir->content)->target);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->next->content)->target);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->next->next->content)->target);
	mu_assert_string_eq("file.txt", ((t_redirection *)redir->next->next->next->content)->target);
	mu_assert_string_eq("simple", ((t_redirection *)redir->next->next->next->next->content)->target);
	mu_assert_string_eq("single_quote", ((t_redirection *)redir->next->next->next->next->next->content)->target);
	mu_assert_string_eq("double_quote", ((t_redirection *)redir->next->next->next->next->next->next->content)->target);
	mu_assert_string_eq("file_2.txt", ((t_redirection *)redir->next->next->next->next->next->next->next->content)->target);

	// CLEANUP
	ft_lstclear(&redir, free_redirection);
	ft_lstclear(&env, free_env_var);
}

MU_TEST_SUITE(expand_redir_test_suite)
{
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_simple);
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_single_quote);
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_double_quote);
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_valid_variable);
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_variable_with_space_char);
	MU_RUN_TEST(test_expand_redir_type_overwrite_target_non_existing_variable);
	MU_RUN_TEST(test_expand_redir_type_append_target_simple);
	MU_RUN_TEST(test_expand_redir_type_append_target_single_quote);
	MU_RUN_TEST(test_expand_redir_type_append_target_double_quote);
	MU_RUN_TEST(test_expand_redir_type_append_target_valid_variable);
	MU_RUN_TEST(test_expand_redir_type_append_target_variable_with_space_char);
	MU_RUN_TEST(test_expand_redir_type_append_target_non_existing_variable);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_simple);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_single_quote);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_double_quote);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_valid_variable);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_variable_with_space_char);
	MU_RUN_TEST(test_expand_redir_type_simple_input_target_non_existing_variable);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_simple);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_single_quote);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_double_quote);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_valid_variable);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_variable_with_space_char);
	MU_RUN_TEST(test_expand_redir_type_heredoc_target_non_existing_variable);
	MU_RUN_TEST(test_expand_redir_input_type_all_cases);
	MU_RUN_TEST(test_expand_redir_output_type_all_cases);
}

int test_expand_redir(void)
{
	MU_RUN_SUITE(expand_redir_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:25:06 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/20 13:08:41 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

static t_expand_commands_result capture_expand_commands_output(t_list *env, int last_status, t_list *cmds, int fd)
{
	t_expand_commands_result result;
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
	result.return_value = expand_commands(env, last_status, cmds);

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

MU_TEST(test_expand_commands_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	tokens = extract_tokens("simple > simple >> simple < simple << simple");
	cmds = extract_commands(tokens);;
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("simple", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("simple", ((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq("simple", ((t_redirection *)((t_command *)actual_result->content)->input_redir->next->content)->target);
	mu_assert_string_eq("simple", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("simple", ((t_redirection *)((t_command *)actual_result->content)->output_redir->next->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
}

MU_TEST(test_expand_commands_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	tokens = extract_tokens("'single' > 'single' >> 'single' < 'single' << 'single'");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("single", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("single", ((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq("'single'", ((t_redirection *)((t_command *)actual_result->content)->input_redir->next->content)->target);
	mu_assert_string_eq("single", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("single", ((t_redirection *)((t_command *)actual_result->content)->output_redir->next->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
}

MU_TEST(test_expand_commands_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	tokens = extract_tokens("\"double\" > \"double\" >> \"double\" < \"double\" << \"double\"");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("double", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("double", ((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq("\"double\"", ((t_redirection *)((t_command *)actual_result->content)->input_redir->next->content)->target);
	mu_assert_string_eq("double", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("double", ((t_redirection *)((t_command *)actual_result->content)->output_redir->next->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
}

MU_TEST(test_expand_commands_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	lstadd_env_var(&env, "VAR", "value");
	tokens = extract_tokens("$VAR > $VAR >> $VAR < $VAR << $VAR");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("value", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("value", ((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq("$VAR", ((t_redirection *)((t_command *)actual_result->content)->input_redir->next->content)->target);
	mu_assert_string_eq("value", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("value", ((t_redirection *)((t_command *)actual_result->content)->output_redir->next->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
	ft_lstclear(&env, free);
}

MU_TEST(test_expand_commands_multiple_commands)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	tokens = extract_tokens("cmd1 arg1 > out1 | cmd2 arg2 < in2");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("cmd1", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("arg1", (char *)((t_command *)actual_result->content)->arguments->next->content);
	mu_assert_string_eq("out1", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("cmd2", (char *)((t_command *)actual_result->next->content)->arguments->content);
	mu_assert_string_eq("arg2", (char *)((t_command *)actual_result->next->content)->arguments->next->content);
	mu_assert_string_eq("in2", ((t_redirection *)((t_command *)actual_result->next->content)->input_redir->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
}

MU_TEST(test_expand_commands_multiple_commands_with_variables_and_quotes)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	lstadd_env_var(&env, "VAR1", "value1");
	lstadd_env_var(&env, "VAR2", "value2");
	tokens = extract_tokens("cmd1 $VAR1 > 'out1' | cmd2 $VAR2 < \"in2\"");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("cmd1", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("value1", (char *)((t_command *)actual_result->content)->arguments->next->content);
	mu_assert_string_eq("out1", ((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);
	mu_assert_string_eq("cmd2", (char *)((t_command *)actual_result->next->content)->arguments->content);
	mu_assert_string_eq("value2", (char *)((t_command *)actual_result->next->content)->arguments->next->content);
	mu_assert_string_eq("in2", ((t_redirection *)((t_command *)actual_result->next->content)->input_redir->content)->target);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
	ft_lstclear(&env, free);
}

MU_TEST(test_expand_commands_non_existing_variable_on_arguments)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*actual_result;

	// ACT
	tokens = extract_tokens("cmd $VAR");
	cmds = extract_commands(tokens);
	actual_result = expand_commands(env, last_status, cmds);

	// ASSERT
	mu_assert_string_eq("cmd", (char *)((t_command *)actual_result->content)->arguments->content);
	mu_assert_string_eq("", (char *)((t_command *)actual_result->content)->arguments->next->content);

	// CLEANUP
	ft_lstclear(&cmds, free_command);
	ft_lstclear(&tokens, free);
}

MU_TEST(test_expand_commands_non_existing_variable_on_redirections)
{
	// ARRANGE
	t_expand_commands_result result;
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*cmds = NULL;
	t_list	*tokens = NULL;
	t_list	*expected_result;
	t_list	*actual_result;
	char *expected_output;
	char *actual_output;

	// ACT
	tokens = extract_tokens("$VAR < $VAR << $VAR > $VAR >> $VAR");
	cmds = extract_commands(tokens);
	result = capture_expand_commands_output(env, last_status, cmds, 2);
	expected_result = NULL;
	actual_result = result.return_value;
	expected_output = "minishell: $VAR: ambiguous redirect\n";
	actual_output = result.output;

	// ASSERT
	mu_assert(expected_result == actual_result, "Expected NULL but got non-NULL");
	mu_assert_string_eq(expected_output, actual_output);

	// CLEANUP
	ft_lstclear(&tokens, free);
}

MU_TEST_SUITE(expand_commands_test_suite)
{
	MU_RUN_TEST(test_expand_commands_simple);
	MU_RUN_TEST(test_expand_commands_single_quote);
	MU_RUN_TEST(test_expand_commands_double_quote);
	MU_RUN_TEST(test_expand_commands_valid_variable);
	MU_RUN_TEST(test_expand_commands_multiple_commands);
	MU_RUN_TEST(test_expand_commands_multiple_commands_with_variables_and_quotes);
	MU_RUN_TEST(test_expand_commands_non_existing_variable_on_arguments);
	MU_RUN_TEST(test_expand_commands_non_existing_variable_on_redirections);
}

int test_expand_commands(void)
{
	MU_RUN_SUITE(expand_commands_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

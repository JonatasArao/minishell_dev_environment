/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:49:23 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 11:54:07 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_extract_commands_argument)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	first_command = alloc_command();
	lstadd_str(&first_command->arguments, "ls");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->content,
							((t_command *)expected_result->content)->arguments->content);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_multiple_arguments)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("-la")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("/home")));
	first_command = alloc_command();
	lstadd_str(&first_command->arguments, "ls");
	lstadd_str(&first_command->arguments, "-la");
	lstadd_str(&first_command->arguments, "/home");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->content,
							((t_command *)expected_result->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->next->content,
							((t_command *)expected_result->content)->arguments->next->content);
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->next->next->content,
							((t_command *)expected_result->content)->arguments->next->next->content);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_parse_tokens_input_redirection_less_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->input_redir, "<", "file.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_parse_tokens_input_redirection_double_less_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->input_redir, "<<", "file.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_parse_tokens_output_redirection_greater_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->output_redir, ">", "file.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->output_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->output_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_parse_tokens_output_redirection_double_greater_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->output_redir, ">>", "file.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->output_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->output_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->output_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_with_pipe)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;
	t_command	*second_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("minishell")));
	first_command = alloc_command();
	lstadd_str(&first_command->arguments, "ls");
	second_command = alloc_command();
	lstadd_str(&second_command->arguments, "grep");
	lstadd_str(&second_command->arguments, "minishell");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	ft_lstadd_back(&expected_result, ft_lstnew(second_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->content,
							((t_command *)expected_result->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->content)->arguments->content,
							((t_command *)expected_result->next->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->content)->arguments->next->content,
							((t_command *)expected_result->next->content)->arguments->next->content);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_with_pipe_and_redirection)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;
	t_command	*second_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("minishell")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("output.txt")));
	first_command = alloc_command();
	lstadd_str(&first_command->arguments, "cat");
	lstadd_str(&first_command->arguments, "file.txt");
	second_command = alloc_command();
	lstadd_str(&second_command->arguments, "grep");
	lstadd_str(&second_command->arguments, "minishell");
	lstadd_redir(&second_command->output_redir, ">", "output.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	ft_lstadd_back(&expected_result, ft_lstnew(second_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->content,
							((t_command *)expected_result->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->next->content,
							((t_command *)expected_result->content)->arguments->next->content);
	mu_assert_string_eq(((t_command *)actual_result->next->content)->arguments->content,
							((t_command *)expected_result->next->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->content)->arguments->next->content,
							((t_command *)expected_result->next->content)->arguments->next->content);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_with_multiple_pipes)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;
	t_command	*second_command;
	t_command	*third_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("file.txt")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("minishell")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("wc")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("-l")));
	first_command = alloc_command();
	lstadd_str(&first_command->arguments, "cat");
	lstadd_str(&first_command->arguments, "file.txt");
	second_command = alloc_command();
	lstadd_str(&second_command->arguments, "grep");
	lstadd_str(&second_command->arguments, "minishell");
	third_command = alloc_command();
	lstadd_str(&third_command->arguments, "wc");
	lstadd_str(&third_command->arguments, "-l");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	ft_lstadd_back(&expected_result, ft_lstnew(second_command));
	ft_lstadd_back(&expected_result, ft_lstnew(third_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_command *)actual_result->content)->arguments->content,
							((t_command *)expected_result->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->content)->arguments->content,
							((t_command *)expected_result->next->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->next->content)->arguments->content,
							((t_command *)expected_result->next->next->content)->arguments->content);
	mu_assert_string_eq(((t_command *)actual_result->next->next->content)->arguments->next->content,
							((t_command *)expected_result->next->next->content)->arguments->next->content);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_with_pipe_and_input_redirection)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;
	t_command	*second_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("input.txt")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("output.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->input_redir, "<", "input.txt");
	second_command = alloc_command();
	lstadd_redir(&second_command->output_redir, ">", "output.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	ft_lstadd_back(&expected_result, ft_lstnew(second_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST(test_extract_commands_with_double_input_redirection_and_pipe)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*first_command;
	t_command	*second_command;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("input.txt")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("output.txt")));
	first_command = alloc_command();
	lstadd_redir(&first_command->input_redir, "<<", "input.txt");
	second_command = alloc_command();
	lstadd_redir(&second_command->output_redir, ">>", "output.txt");
	expected_result = NULL;
	ft_lstadd_back(&expected_result, ft_lstnew(first_command));
	ft_lstadd_back(&expected_result, ft_lstnew(second_command));
	actual_result = extract_commands(token_list);

	// ASSERT
	mu_check(ft_lstsize(actual_result) == ft_lstsize(expected_result));
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->content)->input_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->content)->input_redir->content)->target);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->type,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->type);
	mu_assert_string_eq(((t_redirection *)((t_command *)expected_result->next->content)->output_redir->content)->target,
							((t_redirection *)((t_command *)actual_result->next->content)->output_redir->content)->target);

	// CLEANUP
	ft_lstclear(&token_list, free);
	ft_lstclear(&expected_result, free_command);
	ft_lstclear(&actual_result, free_command);
}

MU_TEST_SUITE(extract_commands_test_suite)
{
	MU_RUN_TEST(test_extract_commands_argument);
	MU_RUN_TEST(test_extract_commands_multiple_arguments);
	MU_RUN_TEST(test_parse_tokens_input_redirection_less_than);
	MU_RUN_TEST(test_parse_tokens_input_redirection_double_less_than);
	MU_RUN_TEST(test_parse_tokens_output_redirection_greater_than);
	MU_RUN_TEST(test_parse_tokens_output_redirection_double_greater_than);
	MU_RUN_TEST(test_extract_commands_with_pipe);
	MU_RUN_TEST(test_extract_commands_with_pipe_and_redirection);
	MU_RUN_TEST(test_extract_commands_with_multiple_pipes);
	MU_RUN_TEST(test_extract_commands_with_pipe_and_input_redirection);
	MU_RUN_TEST(test_extract_commands_with_double_input_redirection_and_pipe);
}

int test_extract_commands(void)
{
	MU_RUN_SUITE(extract_commands_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

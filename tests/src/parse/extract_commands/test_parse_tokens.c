/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:59:08 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/20 23:07:12 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_parse_tokens_argument)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	expected_cmd = alloc_command();
	lstadd_str(&expected_cmd->arguments, "ls");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq((char *) expected_cmd->arguments->content,
		(char *) actual_cmd->arguments->content);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);

}

MU_TEST(test_parse_tokens_multiple_arguments)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("-la")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("/home")));
	expected_cmd = alloc_command();
	lstadd_str(&expected_cmd->arguments, "ls");
	lstadd_str(&expected_cmd->arguments, "-la");
	lstadd_str(&expected_cmd->arguments, "/home");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq((char *) expected_cmd->arguments->content,
		(char *) actual_cmd->arguments->content);
	mu_assert_string_eq((char *) expected_cmd->arguments->next->content,
		(char *) actual_cmd->arguments->next->content);
	mu_assert_string_eq((char *) expected_cmd->arguments->next->next->content,
		(char *) actual_cmd->arguments->next->next->content);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_no_arguments)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	expected_cmd = alloc_command();
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_check(expected_cmd->arguments == NULL);
	mu_check(actual_cmd->arguments == NULL);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_input_redirection_less_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("input.txt")));
	expected_cmd = alloc_command();
	lstadd_redir(&expected_cmd->redirections, "<", "input.txt");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->type,
		((t_redirection *)actual_cmd->redirections->content)->type);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->target,
		((t_redirection *)actual_cmd->redirections->content)->target);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_input_redirection_double_less_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("input.txt")));
	expected_cmd = alloc_command();
	lstadd_redir(&expected_cmd->redirections, "<<", "input.txt");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->type,
		((t_redirection *)actual_cmd->redirections->content)->type);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->target,
		((t_redirection *)actual_cmd->redirections->content)->target);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_output_redirection_greater_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("output.txt")));
	expected_cmd = alloc_command();
	lstadd_redir(&expected_cmd->redirections, ">", "output.txt");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->type,
		((t_redirection *)actual_cmd->redirections->content)->type);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->target,
		((t_redirection *)actual_cmd->redirections->content)->target);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_output_redirection_double_greater_than)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("append.txt")));
	expected_cmd = alloc_command();
	lstadd_redir(&expected_cmd->redirections, ">>", "append.txt");
	actual_cmd = alloc_command();
	expected_result = NULL;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->type,
		((t_redirection *)actual_cmd->redirections->content)->type);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->target,
		((t_redirection *)actual_cmd->redirections->content)->target);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_pipe)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("ls")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("minishell")));
	expected_cmd = alloc_command();
	lstadd_str(&expected_cmd->arguments, "ls");
	lstadd_str(&expected_cmd->arguments, "|");
	lstadd_str(&expected_cmd->arguments, "grep");
	lstadd_str(&expected_cmd->arguments, "minishell");
	actual_cmd = alloc_command();
	expected_result = token_list->next->next;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq((char *) expected_cmd->arguments->content,
		(char *) actual_cmd->arguments->content);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST(test_parse_tokens_pipe_and_redirection)
{
	// ARRANGE
	t_list		*token_list;
	t_list		*expected_result;
	t_list		*actual_result;
	t_command	*expected_cmd;
	t_command	*actual_cmd;

	// ACT
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("input.txt")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&token_list, ft_lstnew(ft_strdup("pattern")));
	expected_cmd = alloc_command();
	lstadd_str(&expected_cmd->arguments, "cat");
	lstadd_redir(&expected_cmd->redirections, "<", "input.txt");
	lstadd_str(&expected_cmd->arguments, "|");
	lstadd_str(&expected_cmd->arguments, "grep");
	lstadd_str(&expected_cmd->arguments, "pattern");
	actual_cmd = alloc_command();
	expected_result = token_list->next->next->next->next;
	actual_result = parse_tokens(token_list, actual_cmd);

	// ASSERT
	mu_assert_string_eq((char *) expected_cmd->arguments->content,
		(char *) actual_cmd->arguments->content);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->type,
		((t_redirection *)actual_cmd->redirections->content)->type);
	mu_assert_string_eq(((t_redirection *)expected_cmd->redirections->content)->target,
		((t_redirection *)actual_cmd->redirections->content)->target);
	mu_assert(actual_result == expected_result, "Wrong token node");

	// CLEANUP
	ft_lstclear(&token_list, free);
	free_command(expected_cmd);
	free_command(actual_cmd);
}

MU_TEST_SUITE(parse_tokens_test_suite)
{
	MU_RUN_TEST(test_parse_tokens_argument);
	MU_RUN_TEST(test_parse_tokens_multiple_arguments);
	MU_RUN_TEST(test_parse_tokens_no_arguments);
	MU_RUN_TEST(test_parse_tokens_input_redirection_less_than);
	MU_RUN_TEST(test_parse_tokens_input_redirection_double_less_than);
	MU_RUN_TEST(test_parse_tokens_output_redirection_greater_than);
	MU_RUN_TEST(test_parse_tokens_output_redirection_double_greater_than);
	MU_RUN_TEST(test_parse_tokens_pipe);
	MU_RUN_TEST(test_parse_tokens_pipe_and_redirection);
}

int test_parse_tokens(void)
{
	MU_RUN_SUITE(parse_tokens_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

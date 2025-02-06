/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_token_list_valid.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:02:08 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/06 17:34:28 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_trailing_pipe)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

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
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("|");
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("echo");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

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
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew(">>");
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_double_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("cat");
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("file.txt"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
}

MU_TEST(test_is_token_list_valid_with_invalid_pipe_and_double_input_redirection)
{
	// ARRANGE
	t_list	*tokens;
	int		expected_result;
	int		actual_result;

	// ACT
	tokens = ft_lstnew("grep");
	ft_lstadd_back(&tokens, ft_lstnew("Hello"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	expected_result = 0;
	actual_result = is_token_list_valid(tokens);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);

	// CLEANUP
	ft_lstclear(&tokens, do_nothing);
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
}

int test_is_token_list_valid(void)
{
	MU_RUN_SUITE(is_token_list_valid_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

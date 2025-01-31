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
}

int	test_extract_tokens(void)
{
	MU_RUN_SUITE(extract_tokens_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

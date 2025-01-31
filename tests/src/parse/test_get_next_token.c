/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:01 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 10:47:11 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
# include "minunit.h"

MU_TEST(test_get_next_token_word)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}
MU_TEST(test_get_next_token_multiple_words)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*input_string;

	// ACT
	input_string = "word1 word2";
	expected_result = strdup("word1");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("word2");
	actual_result2 = get_next_token(&input_string[6]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
}

MU_TEST(test_get_next_token_with_leading_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "   word";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_empty_string)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "";
	expected_result = NULL;
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
}

MU_TEST(test_get_next_token_only_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "     ";
	expected_result = NULL;
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
}

MU_TEST(test_get_next_token_with_trailing_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word   ";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_special_characters)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word!@#";
	expected_result = strdup("word!@#");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_newline)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word\nnext";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_tabs)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\tword";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_mixed_whitespace)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = " \t\n word";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_single_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'single quoted'";
	expected_result = strdup("'single quoted'");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_double_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"double quoted\"";
	expected_result = strdup("\"double quoted\"");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_redirection)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word > file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup(">");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[6]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_pipe)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word | next";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("|");
	actual_result2 = get_next_token(&input_string[5]);
	expected_result3 = strdup("next");
	actual_result3 = get_next_token(&input_string[7]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_double_redirection)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word >> file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup(">>");
	actual_result2 = get_next_token(&input_string[5]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[8]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_input_redirection)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word < file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("<");
	actual_result2 = get_next_token(&input_string[5]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[7]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_pipe_and_redirection)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*expected_result4;
	char	*actual_result4;
	char	*expected_result5;
	char	*actual_result5;
	char	*input_string;

	// ACT
	input_string = "word | next > file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("|");
	actual_result2 = get_next_token(&input_string[5]);
	expected_result3 = strdup("next");
	actual_result3 = get_next_token(&input_string[7]);
	expected_result4 = strdup(">");
	actual_result4 = get_next_token(&input_string[12]);
	expected_result5 = strdup("file");
	actual_result5 = get_next_token(&input_string[14]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);
	mu_assert_string_eq(expected_result4, actual_result4);
	mu_assert_string_eq(expected_result5, actual_result5);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
	free(expected_result4);
	free(actual_result4);
	free(expected_result5);
	free(actual_result5);
}

MU_TEST(test_get_next_token_with_redirection_no_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word>file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup(">");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[5]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_pipe_no_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word|next";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("|");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("next");
	actual_result3 = get_next_token(&input_string[5]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_double_redirection_no_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word>>file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup(">>");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[6]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_input_redirection_no_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*input_string;

	// ACT
	input_string = "word<file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("<");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("file");
	actual_result3 = get_next_token(&input_string[5]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
}

MU_TEST(test_get_next_token_with_pipe_and_redirection_no_spaces)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*expected_result2;
	char	*actual_result2;
	char	*expected_result3;
	char	*actual_result3;
	char	*expected_result4;
	char	*actual_result4;
	char	*expected_result5;
	char	*actual_result5;
	char	*input_string;

	// ACT
	input_string = "word|next>file";
	expected_result = strdup("word");
	actual_result = get_next_token(input_string);
	expected_result2 = strdup("|");
	actual_result2 = get_next_token(&input_string[4]);
	expected_result3 = strdup("next");
	actual_result3 = get_next_token(&input_string[5]);
	expected_result4 = strdup(">");
	actual_result4 = get_next_token(&input_string[9]);
	expected_result5 = strdup("file");
	actual_result5 = get_next_token(&input_string[10]);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);
	mu_assert_string_eq(expected_result2, actual_result2);
	mu_assert_string_eq(expected_result3, actual_result3);
	mu_assert_string_eq(expected_result4, actual_result4);
	mu_assert_string_eq(expected_result5, actual_result5);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	free(expected_result2);
	free(actual_result2);
	free(expected_result3);
	free(actual_result3);
	free(expected_result4);
	free(actual_result4);
	free(expected_result5);
	free(actual_result5);
}

MU_TEST(test_get_next_token_with_pipe_inside_single_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'word|next'";
	expected_result = strdup("'word|next'");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_pipe_inside_double_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"word|next\"";
	expected_result = strdup("\"word|next\"");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_redirection_inside_single_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'word>file'";
	expected_result = strdup("'word>file'");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST(test_get_next_token_with_redirection_inside_double_quotes)
{
	// ARRANGE
	char	*expected_result;
	char	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"word>file\"";
	expected_result = strdup("\"word>file\"");
	actual_result = get_next_token(input_string);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
}

MU_TEST_SUITE(get_next_token_test_suite)
{
	MU_RUN_TEST(test_get_next_token_word);
	MU_RUN_TEST(test_get_next_token_multiple_words);
	MU_RUN_TEST(test_get_next_token_with_leading_spaces);
	MU_RUN_TEST(test_get_next_token_empty_string);
	MU_RUN_TEST(test_get_next_token_only_spaces);
	MU_RUN_TEST(test_get_next_token_with_trailing_spaces);
	MU_RUN_TEST(test_get_next_token_with_special_characters);
	MU_RUN_TEST(test_get_next_token_with_newline);
	MU_RUN_TEST(test_get_next_token_with_tabs);
	MU_RUN_TEST(test_get_next_token_with_mixed_whitespace);
	MU_RUN_TEST(test_get_next_token_with_single_quotes);
	MU_RUN_TEST(test_get_next_token_with_double_quotes);
	MU_RUN_TEST(test_get_next_token_with_redirection);
	MU_RUN_TEST(test_get_next_token_with_pipe);
	MU_RUN_TEST(test_get_next_token_with_double_redirection);
	MU_RUN_TEST(test_get_next_token_with_input_redirection);
	MU_RUN_TEST(test_get_next_token_with_pipe_and_redirection);
	MU_RUN_TEST(test_get_next_token_with_redirection_no_spaces);
	MU_RUN_TEST(test_get_next_token_with_pipe_no_spaces);
	MU_RUN_TEST(test_get_next_token_with_double_redirection_no_spaces);
	MU_RUN_TEST(test_get_next_token_with_input_redirection_no_spaces);
	MU_RUN_TEST(test_get_next_token_with_pipe_and_redirection_no_spaces);
	MU_RUN_TEST(test_get_next_token_with_pipe_inside_single_quotes);
	MU_RUN_TEST(test_get_next_token_with_pipe_inside_double_quotes);
	MU_RUN_TEST(test_get_next_token_with_redirection_inside_single_quotes);
	MU_RUN_TEST(test_get_next_token_with_redirection_inside_double_quotes);
}

int	test_get_next_token(void)
{
	MU_RUN_SUITE(get_next_token_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

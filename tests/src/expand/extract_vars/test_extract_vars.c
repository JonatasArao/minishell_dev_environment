/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:20:17 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/13 15:41:21 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_extract_vars_word)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "word";
	expected_result = ft_lstnew(ft_strdup("word"));
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"quoted\"";
	expected_result = ft_lstnew(ft_strdup("\"quoted\""));
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_single_quotes)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'single'";
	expected_result = ft_lstnew(ft_strdup("'single'"));
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_dollar)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "$variable";
	expected_result = ft_lstnew(ft_strdup("$variable"));
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_dollar_and_space)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "$var iable";
	expected_result = ft_lstnew(ft_strdup("$var"));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup(" iable")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_dollar_and_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "$var\"iable\"";
	expected_result = ft_lstnew(ft_strdup("$var"));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\"iable\"")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_with_single_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "$var' iable'";
	expected_result = ft_lstnew(ft_strdup("$var"));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("' iable'")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_within_single_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'$var'";
	expected_result = ft_lstnew(ft_strdup("'$var'"));
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_assert_string_eq((char *) expected_result->content,
		(char *) actual_result->content);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_within_double_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"$var\"";
	expected_result = ft_lstnew(ft_strdup("\""));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$var")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\"")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_single_quote_within_double_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "\"'$var'\"";
	expected_result = ft_lstnew(ft_strdup("\"'"));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$var")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("'\"")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_double_quote_within_single_quote)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "'\"$var\"'";
	expected_result = ft_lstnew(ft_strdup("'\"$var\"'"));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_complex_string)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "He\"ll\"o\" $USER'alias'\"\"$NICK\", Welcome to '$SCHOOL' in $CITY \".\" $?";
	expected_result = ft_lstnew(ft_strdup("He"));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\"ll\"")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("o")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\" ")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$USER")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("'alias'\"")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\"")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$NICK")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\"")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup(", Welcome to ")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("'$SCHOOL'")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup(" in ")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$CITY")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup(" ")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("\".\"")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup(" ")));
	ft_lstadd_back(&expected_result, ft_lstnew(ft_strdup("$?")));
	actual_result = extract_vars(input_string);

	// ASSERT
	t_list *expected_ptr = expected_result;
	t_list *actual_ptr = actual_result;
	while (expected_ptr && actual_ptr)
	{
		mu_assert_string_eq((char *) expected_ptr->content,
			(char *) actual_ptr->content);
		expected_ptr = expected_ptr->next;
		actual_ptr = actual_ptr->next;
	}

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST(test_extract_vars_empty)
{
	// ARRANGE
	t_list	*expected_result;
	t_list	*actual_result;
	char	*input_string;

	// ACT
	input_string = "";
	expected_result = NULL;
	actual_result = extract_vars(input_string);

	// ASSERT
	mu_check(expected_result == actual_result);

	// CLEANUP
	ft_lstclear(&expected_result, free);
	ft_lstclear(&actual_result, free);
}

MU_TEST_SUITE(extract_vars_test_suite)
{
	MU_RUN_TEST(test_extract_vars_word);
	MU_RUN_TEST(test_extract_vars_with_quotes);
	MU_RUN_TEST(test_extract_vars_with_single_quotes);
	MU_RUN_TEST(test_extract_vars_with_dollar);
	MU_RUN_TEST(test_extract_vars_with_dollar_and_space);
	MU_RUN_TEST(test_extract_vars_with_dollar_and_quote);
	MU_RUN_TEST(test_extract_vars_with_single_quote);
	MU_RUN_TEST(test_extract_vars_within_single_quote);
	MU_RUN_TEST(test_extract_vars_within_double_quote);
	MU_RUN_TEST(test_extract_vars_single_quote_within_double_quote);
	MU_RUN_TEST(test_extract_vars_double_quote_within_single_quote);
	MU_RUN_TEST(test_extract_vars_complex_string);
	MU_RUN_TEST(test_extract_vars_empty);
}

int	test_extract_vars(void)
{
	MU_RUN_SUITE(extract_vars_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

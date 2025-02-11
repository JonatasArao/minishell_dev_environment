/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstadd_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:06:23 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 09:22:16 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_lstadd_str_word)
{
	// ARRANGE
	char *input;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	input = "word";
	expected_result = 1;
	actual_result = lstadd_str(&head, input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(head->content, input);
	ft_lstclear(&head, free);
}

MU_TEST(test_lstadd_str_empty)
{
	// ARRANGE
	char *input;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	input = "";
	expected_result = 1;
	actual_result = lstadd_str(&head, input);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(head->content, input);
	ft_lstclear(&head, free);
}

MU_TEST(test_lstadd_str_multiple)
{
	// ARRANGE
	char *input1;
	char *input2;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	input1 = "first";
	input2 = "second";
	expected_result = 1;
	actual_result = lstadd_str(&head, input1);
	mu_assert_int_eq(expected_result, actual_result);
	actual_result = lstadd_str(&head, input2);
	mu_assert_int_eq(expected_result, actual_result);

	// ASSERT
	mu_assert_string_eq(head->content, input1);
	mu_assert_string_eq(head->next->content, input2);
	ft_lstclear(&head, free);
}

MU_TEST_SUITE(lstadd_str_test_suite)
{
	MU_RUN_TEST(test_lstadd_str_word);
	MU_RUN_TEST(test_lstadd_str_empty);
	MU_RUN_TEST(test_lstadd_str_multiple);
}

int test_lstadd_str(void)
{
	MU_RUN_SUITE(lstadd_str_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstadd_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:06:23 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/11 09:27:24 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_lstadd_redir_valid)
{
	// ARRANGE
	char *type;
	char *target;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	type = ">";
	target = "file.txt";
	expected_result = 1;
	actual_result = lstadd_redir(&head, type, target);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_redirection *)head->content)->type, type);
	mu_assert_string_eq(((t_redirection *)head->content)->target, target);
	ft_lstclear(&head, free_redirection);
}

MU_TEST(test_lstadd_redir_no_type)
{
	// ARRANGE
	char *type;
	char *target;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	type = "";
	target = "file.txt";
	expected_result = 0;
	actual_result = lstadd_redir(&head, type, target);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(head == NULL, "Head should be NULL");
}

MU_TEST(test_lstadd_redir_no_target)
{
	// ARRANGE
	char *type;
	char *target;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	type = ">";
	target = "";
	expected_result = 0;
	actual_result = lstadd_redir(&head, type, target);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(head == NULL, "Head should be NULL");
}

MU_TEST(test_lstadd_redir_multiple)
{
	// ARRANGE
	char *type1;
	char *target1;
	char *type2;
	char *target2;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	type1 = ">";
	target1 = "file1.txt";
	type2 = "<";
	target2 = "file2.txt";
	expected_result = 1;
	actual_result = lstadd_redir(&head, type1, target1);
	mu_assert_int_eq(expected_result, actual_result);
	actual_result = lstadd_redir(&head, type2, target2);
	mu_assert_int_eq(expected_result, actual_result);

	// ASSERT
	mu_assert_string_eq(((t_redirection *)head->content)->type, type1);
	mu_assert_string_eq(((t_redirection *)head->content)->target, target1);
	mu_assert_string_eq(((t_redirection *)head->next->content)->type, type2);
	mu_assert_string_eq(((t_redirection *)head->next->content)->target, target2);
	ft_lstclear(&head, free_redirection);
}

MU_TEST_SUITE(lstadd_redir_test_suite)
{
	MU_RUN_TEST(test_lstadd_redir_valid);
	MU_RUN_TEST(test_lstadd_redir_no_type);
	MU_RUN_TEST(test_lstadd_redir_no_target);
	MU_RUN_TEST(test_lstadd_redir_multiple);
}

int test_lstadd_redir(void)
{
	MU_RUN_SUITE(lstadd_redir_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

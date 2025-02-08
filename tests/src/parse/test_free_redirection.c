/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:30:21 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/08 22:39:34 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_free_redirection_single)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_redirection *redir;
	char message[80];

	// ACT
	redir = malloc(sizeof(t_redirection));
	redir->target = strdup("file.txt");
	redir->type = strdup("<");
	mk_free_reset_counter();
	free_redirection(redir);
	expected_result = 3;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_redirection_linked_list)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_redirection *redir1;
	t_redirection *redir2;
	t_redirection *redir3;
	t_list *list;
	char message[80];

	// ACT
	redir1 = malloc(sizeof(t_redirection));
	redir1->target = strdup("file1.txt");
	redir1->type = strdup(">");
	redir2 = malloc(sizeof(t_redirection));
	redir2->target = strdup("file2.txt");
	redir2->type = strdup("<");
	redir3 = malloc(sizeof(t_redirection));
	redir3->target = strdup("file3.txt");
	redir3->type = strdup(">>");

	list = ft_lstnew(redir1);
	ft_lstadd_back(&list, ft_lstnew(redir2));
	ft_lstadd_back(&list, ft_lstnew(redir3));

	mk_free_reset_counter();
	ft_lstclear(&list, free_redirection);
	expected_result = 12;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_redirection_missing_target)
{
	int expected;
	int result;
	t_redirection *redir;

	redir = malloc(sizeof(*redir));
	redir->target = NULL;
	redir->type = strdup(">");
	mk_free_reset_counter();
	free_redirection(redir);
	expected = 2; 
	result = mk_free_get_control_status().counter;
	mu_assert(expected == result, "Incorrect free count with missing target.");
}

MU_TEST(test_free_redirection_missing_type)
{
	int expected;
	int result;
	t_redirection *redir;

	redir = malloc(sizeof(*redir));
	redir->target = strdup("file.txt");
	redir->type = NULL;
	mk_free_reset_counter();
	free_redirection(redir);
	expected = 2; 
	result = mk_free_get_control_status().counter;
	mu_assert(expected == result, "Incorrect free count with missing type.");
}

MU_TEST(test_free_redirection_only_malloc)
{
	int expected;
	int result;
	t_redirection *redir;

	redir = malloc(sizeof(*redir));
	redir->target = NULL;
	redir->type = NULL;
	mk_free_reset_counter();
	free_redirection(redir);
	expected = 1; 
	result = mk_free_get_control_status().counter;
	mu_assert(expected == result, "Incorrect free count with only malloc.");
}

MU_TEST(test_free_redirection_null)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	char message[80];

	// ACT
	mk_free_reset_counter();
	free_redirection(NULL);
	expected_result = 0;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST_SUITE(free_redirection_test_suite)
{
	MU_RUN_TEST(test_free_redirection_single);
	MU_RUN_TEST(test_free_redirection_linked_list);
	MU_RUN_TEST(test_free_redirection_missing_target);
	MU_RUN_TEST(test_free_redirection_missing_type);
	MU_RUN_TEST(test_free_redirection_only_malloc);
	MU_RUN_TEST(test_free_redirection_null);
}

int test_free_redirection(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(free_redirection_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}
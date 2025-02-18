/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_concat_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:51:52 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/18 21:28:21 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_concat_vars_single_var)
{
	// ARRANGE
	t_list *var_list = NULL;
	char *expected_result;
	char *actual_result;

	// ACT
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup("ls")));

	expected_result = "ls";
	actual_result = concat_vars(var_list);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&var_list, free);
}

MU_TEST(test_concat_vars_multiple_vars)
{
	// ARRANGE
	t_list *var_list = NULL;
	char *expected_result;
	char *actual_result;

	// ACT
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup("echo")));
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup(" ")));
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup(" ")));
	ft_lstadd_back(&var_list, ft_lstnew(ft_strdup("world")));

	expected_result = "echo hello world";
	actual_result = concat_vars(var_list);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
	ft_lstclear(&var_list, free);
}

MU_TEST(test_concat_vars_empty_list)
{
	// ARRANGE
	t_list *var_list = NULL;
	char *expected_result;
	char *actual_result;

	// ACT
	expected_result = "";
	actual_result = concat_vars(var_list);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST_SUITE(concat_vars_test_suite)
{
	MU_RUN_TEST(test_concat_vars_single_var);
	MU_RUN_TEST(test_concat_vars_multiple_vars);
	MU_RUN_TEST(test_concat_vars_empty_list);
}

int test_concat_vars(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(concat_vars_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}
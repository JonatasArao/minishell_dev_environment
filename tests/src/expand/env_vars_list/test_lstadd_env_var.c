/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstadd_env_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:37:42 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 15:37:32 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_lstadd_env_var_valid)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "PATH";
	value = "/usr/bin";
	expected_result = 1;
	actual_result = lstadd_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstadd_env_var_no_key)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "";
	value = "/usr/bin";
	expected_result = 0;
	actual_result = lstadd_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(head == NULL, "Head should be NULL");
}

MU_TEST(test_lstadd_env_var_no_value)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "PATH";
	value = "";
	expected_result = 1;
	actual_result = lstadd_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstadd_env_var_multiple)
{
	// ARRANGE
	char *key1;
	char *value1;
	char *key2;
	char *value2;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key1 = "PATH";
	value1 = "/usr/bin";
	key2 = "HOME";
	value2 = "/home/user";
	expected_result = 1;
	actual_result = lstadd_env_var(&head, key1, value1);
	mu_assert_int_eq(expected_result, actual_result);
	actual_result = lstadd_env_var(&head, key2, value2);
	mu_assert_int_eq(expected_result, actual_result);

	// ASSERT
	mu_assert_string_eq(((t_env_var *)head->content)->key, key2);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value2);
	mu_assert_string_eq(((t_env_var *)head->next->content)->key, key1);
	mu_assert_string_eq(((t_env_var *)head->next->content)->value, value1);
	ft_lstclear(&head, free_env_var);
}

MU_TEST_SUITE(lstadd_env_var_test_suite)
{
	MU_RUN_TEST(test_lstadd_env_var_valid);
	MU_RUN_TEST(test_lstadd_env_var_no_key);
	MU_RUN_TEST(test_lstadd_env_var_no_value);
	MU_RUN_TEST(test_lstadd_env_var_multiple);
}

int test_lstadd_env_var(void)
{
	MU_RUN_SUITE(lstadd_env_var_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

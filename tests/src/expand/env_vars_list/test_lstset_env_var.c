/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstset_env_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:54:09 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/26 07:52:11 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_lstset_env_var_valid)
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
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_update)
{
	// ARRANGE
	char *key;
	char *value1;
	char *value2;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "PATH";
	value1 = "/usr/bin";
	value2 = "/bin";
	lstadd_env_var(&head, key, value1);
	expected_result = 1;
	actual_result = lstset_env_var(&head, key, value2);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value2);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_no_key)
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
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(head == NULL, "Head should be NULL");
}

MU_TEST(test_lstset_env_var_no_value)
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
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_create_multiple)
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
	actual_result = lstset_env_var(&head, key1, value1);
	mu_assert_int_eq(expected_result, actual_result);
	actual_result = lstset_env_var(&head, key2, value2);
	mu_assert_int_eq(expected_result, actual_result);

	// ASSERT
	mu_assert_string_eq(((t_env_var *)head->content)->key, key2);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value2);
	mu_assert_string_eq(((t_env_var *)head->next->content)->key, key1);
	mu_assert_string_eq(((t_env_var *)head->next->content)->value, value1);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_update_multiple)
{
	// ARRANGE
	char *key1;
	char *value1;
	char *value2;
	char *key2;
	char *value3;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key1 = "PATH";
	value1 = "/usr/bin";
	value2 = "/bin";
	key2 = "HOME";
	value3 = "/home/user";
	lstadd_env_var(&head, key1, value1);
	lstadd_env_var(&head, key2, value3);
	expected_result = 1;
	actual_result = lstset_env_var(&head, key1, value2);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key2);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value3);
	mu_assert_string_eq(((t_env_var *)head->next->content)->key, key1);
	mu_assert_string_eq(((t_env_var *)head->next->content)->value, value2);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_update_nonexistent)
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
	lstadd_env_var(&head, key1, value1);
	expected_result = 1;
	actual_result = lstset_env_var(&head, key2, value2);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key2);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value2);
	mu_assert_string_eq(((t_env_var *)head->next->content)->key, key1);
	mu_assert_string_eq(((t_env_var *)head->next->content)->value, value1);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_null_key)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = NULL;
	value = "/usr/bin";
	expected_result = 0;
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(head == NULL, "Head should be NULL");
}

MU_TEST(test_lstset_env_var_null_value)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "PATH";
	value = NULL;
	expected_result = 1;
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert(((t_env_var *)head->content)->value == NULL, "Value should be NULL");
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_empty_list)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "NEW_VAR";
	value = "new_value";
	expected_result = 1;
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST(test_lstset_env_var_special_characters)
{
	// ARRANGE
	char *key;
	char *value;
	int expected_result;
	int actual_result;
	t_list *head = NULL;

	// ACT
	key = "SPECIAL_VAR";
	value = "!@#$%^&*()_+";
	expected_result = 1;
	actual_result = lstset_env_var(&head, key, value);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq(((t_env_var *)head->content)->key, key);
	mu_assert_string_eq(((t_env_var *)head->content)->value, value);
	ft_lstclear(&head, free_env_var);
}

MU_TEST_SUITE(lstset_env_var_test_suite)
{
	MU_RUN_TEST(test_lstset_env_var_valid);
	MU_RUN_TEST(test_lstset_env_var_update);
	MU_RUN_TEST(test_lstset_env_var_no_key);
	MU_RUN_TEST(test_lstset_env_var_no_value);
	MU_RUN_TEST(test_lstset_env_var_create_multiple);
	MU_RUN_TEST(test_lstset_env_var_update_multiple);
	MU_RUN_TEST(test_lstset_env_var_update_nonexistent);
	MU_RUN_TEST(test_lstset_env_var_null_key);
	MU_RUN_TEST(test_lstset_env_var_null_value);
	MU_RUN_TEST(test_lstset_env_var_empty_list);
	MU_RUN_TEST(test_lstset_env_var_special_characters);
}

int test_lstset_env_var(void)
{
	MU_RUN_SUITE(lstset_env_var_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

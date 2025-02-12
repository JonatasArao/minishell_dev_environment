/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:11:58 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 15:31:46 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_free_env_var_single)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_env_var *env_var;
	char message[80];

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	mk_free_reset_counter();
	free_env_var(env_var);
	expected_result = 3; // 1 for env_var, 1 for key, 1 for value
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_env_var_linked_list)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_env_var *env_var1;
	t_env_var *env_var2;
	t_env_var *env_var3;
	t_list *list;
	char message[80];

	// ACT
	env_var1 = malloc(sizeof(t_env_var));
	env_var1->key = strdup("USER");
	env_var1->value = strdup("student");
	env_var2 = malloc(sizeof(t_env_var));
	env_var2->key = strdup("OS");
	env_var2->value = strdup("Linux");
	env_var3 = malloc(sizeof(t_env_var));
	env_var3->key = strdup("Version");
	env_var3->value = strdup("Ubuntu");

	list = ft_lstnew(env_var1);
	ft_lstadd_back(&list, ft_lstnew(env_var2));
	ft_lstadd_back(&list, ft_lstnew(env_var3));

	mk_free_reset_counter();
	ft_lstclear(&list, free_env_var);
	expected_result = 12;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_env_var_missing_key)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_env_var *env_var;
	char message[80];

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = NULL;
	env_var->value = strdup("student");
	mk_free_reset_counter();
	free_env_var(env_var);
	expected_result = 2; // 1 for env_var, 1 for value
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_env_var_missing_value)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_env_var *env_var;
	char message[80];

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = NULL;
	mk_free_reset_counter();
	free_env_var(env_var);
	expected_result = 2; // 1 for env_var, 1 for key
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_env_var_only_malloc)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_env_var *env_var;
	char message[80];

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = NULL;
	env_var->value = NULL;
	mk_free_reset_counter();
	free_env_var(env_var);
	expected_result = 1; // 1 for env_var
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_env_var_null)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	char message[80];

	// ACT
	mk_free_reset_counter();
	free_env_var(NULL);
	expected_result = 0;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST_SUITE(free_env_var_test_suite)
{
	MU_RUN_TEST(test_free_env_var_single);
	MU_RUN_TEST(test_free_env_var_linked_list);
	MU_RUN_TEST(test_free_env_var_missing_key);
	MU_RUN_TEST(test_free_env_var_missing_value);
	MU_RUN_TEST(test_free_env_var_only_malloc);
	MU_RUN_TEST(test_free_env_var_null);
}

int test_free_env_var(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(free_env_var_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstrm_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:55:34 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/25 13:05:42 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_lstrm_env_var_single)
{
	// ARRANGE
	t_list *env = NULL;
	int expected_result;
	int actual_result;
	int expected_free;
	int actual_free;
	char free_message[80];

	// ACT
	lstadd_env_var(&env, "USER", "student");
	mk_free_reset_counter();
	expected_result = 1;
	actual_result = lstrm_env_var(&env, "USER");
	expected_free = 4;
	actual_free = mk_free_get_control_status().counter;
	snprintf(free_message, sizeof(free_message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_free, actual_free);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(expected_free == actual_free, free_message);
	mu_assert(get_env_var(env, "USER") == NULL, "Environment variable 'USER' shouldn't exist after removal.");
}

MU_TEST(test_lstrm_env_var_multiple)
{
	// ARRANGE
	t_list *env = NULL;
	int expected_result;
	int actual_result;
	int expected_free;
	int actual_free;
	char free_message[80];

	// ACT
	lstadd_env_var(&env, "USER", "student");
	lstadd_env_var(&env, "PATH", "/usr/bin");
	lstadd_env_var(&env, "HOME", "/home/student");
	mk_free_reset_counter();
	expected_result = 1;
	actual_result = lstrm_env_var(&env, "PATH");
	expected_free = 4;
	actual_free = mk_free_get_control_status().counter;
	snprintf(free_message, sizeof(free_message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_free, actual_free);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(get_env_var(env, "PATH") == NULL, "Environment variable 'PATH' shouldn't exist after removal.");
	mu_assert(get_env_var(env, "USER") != NULL, "Environment variable 'USER' should still exist.");
	mu_assert(get_env_var(env, "HOME") != NULL, "Environment variable 'HOME' should still exist.");

	// CLEANUP
	ft_lstclear(&env, free_env_var);

	// ASSERT - VERIFY FREE FUNCTION CALL COUNT
	mu_assert(expected_free == actual_free, free_message);
}

MU_TEST(test_lstrm_env_var_nonexistent)
{
	// ARRANGE
	t_list *env = NULL;
	int expected_result;
	int actual_result;
	int expected_free;
	int actual_free;
	char free_message[80];

	// ACT
	lstadd_env_var(&env, "USER", "student");
	mk_free_reset_counter();
	expected_result = 0;
	actual_result = lstrm_env_var(&env, "NONEXISTENT");
	expected_free = 0;
	actual_free = mk_free_get_control_status().counter;
	snprintf(free_message, sizeof(free_message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_free, actual_free);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(expected_free == actual_free, free_message);
	mu_assert(get_env_var(env, "USER") != NULL, "Environment variable 'USER' should still exist.");

	// CLEANUP
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_lstrm_env_var_empty_list)
{
	// ARRANGE
	t_list *env = NULL;
	int expected_result;
	int actual_result;
	int expected_free;
	int actual_free;
	char free_message[80];

	// ACT
	mk_free_reset_counter();
	expected_result = 0;
	actual_result = lstrm_env_var(&env, "USER");
	expected_free = 0;
	actual_free = mk_free_get_control_status().counter;
	snprintf(free_message, sizeof(free_message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_free, actual_free);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(expected_free == actual_free, free_message);
}

MU_TEST(test_lstrm_env_var_null_key)
{
	// ARRANGE
	t_list *env = NULL;
	int expected_result;
	int actual_result;
	int expected_free;
	int actual_free;
	char free_message[80];

	// ACT
	lstadd_env_var(&env, "USER", "student");
	mk_free_reset_counter();
	expected_result = 0;
	actual_result = lstrm_env_var(&env, NULL);
	expected_free = 0;
	actual_free = mk_free_get_control_status().counter;
	snprintf(free_message, sizeof(free_message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_free, actual_free);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(expected_free == actual_free, free_message);
	mu_assert(get_env_var(env, "USER") != NULL, "Environment variable 'USER' should still exist.");

	// CLEANUP
	ft_lstclear(&env, free_env_var);
}

MU_TEST_SUITE(lstrm_env_var_test_suite)
{
	MU_RUN_TEST(test_lstrm_env_var_single);
	MU_RUN_TEST(test_lstrm_env_var_multiple);
	MU_RUN_TEST(test_lstrm_env_var_nonexistent);
	MU_RUN_TEST(test_lstrm_env_var_empty_list);
	MU_RUN_TEST(test_lstrm_env_var_null_key);
}

int test_lstrm_env_var(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(lstrm_env_var_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

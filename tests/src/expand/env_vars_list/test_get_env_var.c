/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:53:39 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 15:38:51 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_env_var_existing_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "USER";

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = env_var;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert_string_eq(expected_result->key, actual_result->key);
	mu_assert_string_eq(expected_result->value, actual_result->value);

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_non_existing_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "HOME";

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for non-existing key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_multiple_keys)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var1;
	t_env_var *env_var2;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "PATH";

	// ACT
	env_var1 = malloc(sizeof(t_env_var));
	env_var1->key = strdup("USER");
	env_var1->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var1));

	env_var2 = malloc(sizeof(t_env_var));
	env_var2->key = strdup("PATH");
	env_var2->value = strdup("/usr/bin");
	ft_lstadd_back(&env_list, ft_lstnew(env_var2));

	t_env_var *env_var3 = malloc(sizeof(t_env_var));
	env_var3->key = strdup("HOME");
	env_var3->value = strdup("/home/student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var3));

	t_env_var *env_var4 = malloc(sizeof(t_env_var));
	env_var4->key = strdup("SHELL");
	env_var4->value = strdup("/bin/bash");
	ft_lstadd_back(&env_list, ft_lstnew(env_var4));

	expected_result = env_var2;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert_string_eq(expected_result->key, actual_result->key);
	mu_assert_string_eq(expected_result->value, actual_result->value);

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_case_sensitive)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "user";

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for case-sensitive key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_special_characters)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "USER@42";

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER@42");
	env_var->value = strdup("special");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = env_var;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert_string_eq(expected_result->key, actual_result->key);
	mu_assert_string_eq(expected_result->value, actual_result->value);

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_empty_env_list)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "USER";

	// ACT
	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for empty env list");
}

MU_TEST(test_get_env_var_null_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = NULL;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for NULL key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_env_var_null_env)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "USER";

	// ACT
	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for NULL env list");
}

MU_TEST(test_get_env_var_empty_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	t_env_var *expected_result;
	t_env_var *actual_result;
	char *key = "";

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_env_var(env_list, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for empty key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST_SUITE(get_env_var_test_suite)
{
	MU_RUN_TEST(test_get_env_var_existing_key);
	MU_RUN_TEST(test_get_env_var_non_existing_key);
	MU_RUN_TEST(test_get_env_var_multiple_keys);
	MU_RUN_TEST(test_get_env_var_case_sensitive);
	MU_RUN_TEST(test_get_env_var_special_characters);
	MU_RUN_TEST(test_get_env_var_empty_env_list);
	MU_RUN_TEST(test_get_env_var_null_key);
	MU_RUN_TEST(test_get_env_var_null_env);
	MU_RUN_TEST(test_get_env_var_empty_key);
}

int test_get_env_var(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(get_env_var_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

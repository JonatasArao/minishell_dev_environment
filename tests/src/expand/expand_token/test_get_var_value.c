/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_var_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:12:09 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/13 17:23:25 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_get_var_value_existing_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "USER";
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = strdup("student");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_special_case_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "?";
	int last_status = 42;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = strdup("42");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_non_existing_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "HOME";
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = strdup("");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_multiple_keys)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var1;
	t_env_var *env_var2;
	char *expected_result;
	char *actual_result;
	char *key = "PATH";
	int last_status = 0;

	// ACT
	env_var1 = malloc(sizeof(t_env_var));
	env_var1->key = strdup("USER");
	env_var1->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var1));

	env_var2 = malloc(sizeof(t_env_var));
	env_var2->key = strdup("PATH");
	env_var2->value = strdup("/usr/bin");
	ft_lstadd_back(&env_list, ft_lstnew(env_var2));

	expected_result = strdup("/usr/bin");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_case_sensitive)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "user";
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = strdup("");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_special_characters)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "USER@42";
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER@42");
	env_var->value = strdup("special");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = strdup("special");
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(expected_result);
	free(actual_result);
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_null_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = NULL;
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for NULL key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST(test_get_var_value_null_env)
{
	// ARRANGE
	t_list *env_list = NULL;
	char *expected_result;
	char *actual_result;
	char *key = "USER";
	int last_status = 0;

	// ACT
	expected_result = NULL;
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for NULL env list");
}

MU_TEST(test_get_var_value_empty_key)
{
	// ARRANGE
	t_list *env_list = NULL;
	t_env_var *env_var;
	char *expected_result;
	char *actual_result;
	char *key = "";
	int last_status = 0;

	// ACT
	env_var = malloc(sizeof(t_env_var));
	env_var->key = strdup("USER");
	env_var->value = strdup("student");
	ft_lstadd_back(&env_list, ft_lstnew(env_var));

	expected_result = NULL;
	actual_result = get_var_value(env_list, last_status, key);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected result to be NULL for empty key");

	// CLEANUP
	ft_lstclear(&env_list, free_env_var);
}

MU_TEST_SUITE(get_var_value_test_suite)
{
	MU_RUN_TEST(test_get_var_value_existing_key);
	MU_RUN_TEST(test_get_var_value_special_case_key);
	MU_RUN_TEST(test_get_var_value_non_existing_key);
	MU_RUN_TEST(test_get_var_value_multiple_keys);
	MU_RUN_TEST(test_get_var_value_case_sensitive);
	MU_RUN_TEST(test_get_var_value_special_characters);
	MU_RUN_TEST(test_get_var_value_null_key);
	MU_RUN_TEST(test_get_var_value_null_env);
	MU_RUN_TEST(test_get_var_value_empty_key);
}

int test_get_var_value(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(get_var_value_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

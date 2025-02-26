/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:04:11 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/26 14:05:47 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_expand_arguments_simple)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_str(&args, "simple");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("simple", (char *)args->content);

	// CLEANUP
	ft_lstclear(&args, free);
}

MU_TEST(test_expand_arguments_single_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_str(&args, "'single_quote'");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("single_quote", (char *)args->content);

	// CLEANUP
	ft_lstclear(&args, free);
}

MU_TEST(test_expand_arguments_double_quote)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_str(&args, "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("double_quote", (char *)args->content);

	// CLEANUP
	ft_lstclear(&args, free);
}

MU_TEST(test_expand_arguments_valid_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_str(&args, "$HOME");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("/home/user", (char *)args->content);

	// CLEANUP
	ft_lstclear(&args, free);
	ft_lstclear(&env, free_env_var);
}

MU_TEST(test_expand_arguments_non_existing_variable)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_str(&args, "$VAR");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert(args == NULL, "Argument list should be NULL");

	// CLEANUP
	ft_lstclear(&args, free);
}

MU_TEST(test_expand_arguments_multiple_args)
{
	// ARRANGE
	t_list	*env = NULL;
	int		last_status = 0;
	t_list	*args = NULL;
	int		expected_result;
	int		actual_result;

	// ACT
	lstadd_env_var(&env, "HOME", "/home/user");
	lstadd_str(&args, "echo");
	lstadd_str(&args, "$HOME");
	lstadd_str(&args, "$VAR");
	lstadd_str(&args, "'single_quote'");
	lstadd_str(&args, "\"double_quote\"");
	expected_result = 1;
	actual_result = expand_arguments(env, last_status, &args);

	// ASSERT
	mu_assert_int_eq(expected_result, actual_result);
	mu_assert_string_eq("echo", (char *)args->content);
	mu_assert_string_eq("/home/user", (char *)args->next->content);
	mu_assert_string_eq("single_quote", (char *)args->next->next->content);
	mu_assert_string_eq("double_quote", (char *)args->next->next->next->content);

	// CLEANUP
	ft_lstclear(&args, free);
	ft_lstclear(&env, free_env_var);
}

MU_TEST_SUITE(expand_arguments_test_suite)
{
	MU_RUN_TEST(test_expand_arguments_simple);
	MU_RUN_TEST(test_expand_arguments_single_quote);
	MU_RUN_TEST(test_expand_arguments_double_quote);
	MU_RUN_TEST(test_expand_arguments_valid_variable);
	MU_RUN_TEST(test_expand_arguments_non_existing_variable);
	MU_RUN_TEST(test_expand_arguments_multiple_args);
}

int test_expand_arguments(void)
{
	MU_RUN_SUITE(expand_arguments_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

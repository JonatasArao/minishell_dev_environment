/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_env_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 07:23:47 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/18 22:20:04 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_create_env_string_valid)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "PATH";
	value = "/usr/bin";
	expected_result = "PATH=/usr/bin";
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_create_env_string_no_key)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "";
	value = "/usr/bin";
	expected_result = NULL;
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected NULL when key is empty");
}

MU_TEST(test_create_env_string_no_value)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "PATH";
	value = "";
	expected_result = "PATH=";
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_create_env_string_multiple)
{
	// ARRANGE
	char *key1;
	char *value1;
	char *key2;
	char *value2;
	char *expected_result1;
	char *expected_result2;
	char *actual_result1;
	char *actual_result2;

	// ACT
	key1 = "PATH";
	value1 = "/usr/bin";
	key2 = "HOME";
	value2 = "/home/user";
	expected_result1 = "PATH=/usr/bin";
	expected_result2 = "HOME=/home/user";
	actual_result1 = create_env_string(key1, value1);
	actual_result2 = create_env_string(key2, value2);

	// ASSERT
	mu_assert_string_eq(expected_result1, actual_result1);
	mu_assert_string_eq(expected_result2, actual_result2);

	// CLEANUP
	free(actual_result1);
	free(actual_result2);
}

MU_TEST(test_create_env_string_special_characters)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "SPECIAL";
	value = "!@#$%^&*()";
	expected_result = "SPECIAL=!@#$%^&*()";
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_create_env_string_null_key)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = NULL;
	value = "/usr/bin";
	expected_result = NULL;
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected NULL when key is NULL");
}

MU_TEST(test_create_env_string_null_value)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "PATH";
	value = NULL;
	expected_result = NULL;
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected NULL when value is NULL");
}

MU_TEST(test_create_env_string_empty_key_value)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "";
	value = "";
	expected_result = NULL;
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert(actual_result == expected_result, "Expected NULL when both key and value are empty");
}

MU_TEST(test_create_env_string_long_key_value)
{
	// ARRANGE
	char *key;
	char *value;
	char *expected_result;
	char *actual_result;

	// ACT
	key = "LONG_KEY";
	value = "ThisIsAVeryLongValueThatShouldBeHandledProperlyByTheFunction";
	expected_result = "LONG_KEY=ThisIsAVeryLongValueThatShouldBeHandledProperlyByTheFunction";
	actual_result = create_env_string(key, value);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result);

	// CLEANUP
	free(actual_result);
}

MU_TEST_SUITE(create_env_string_test_suite)
{
	MU_RUN_TEST(test_create_env_string_valid);
	MU_RUN_TEST(test_create_env_string_no_key);
	MU_RUN_TEST(test_create_env_string_no_value);
	MU_RUN_TEST(test_create_env_string_multiple);
	MU_RUN_TEST(test_create_env_string_special_characters);
	MU_RUN_TEST(test_create_env_string_null_key);
	MU_RUN_TEST(test_create_env_string_null_value);
	MU_RUN_TEST(test_create_env_string_empty_key_value);
	MU_RUN_TEST(test_create_env_string_long_key_value);
}

int test_create_env_string(void)
{
	MU_RUN_SUITE(create_env_string_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

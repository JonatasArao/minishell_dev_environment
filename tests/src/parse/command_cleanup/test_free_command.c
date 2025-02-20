/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:56:46 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/20 23:03:48 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_free_command_single)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_command *cmd;
	t_redirection *input_redir;
	t_redirection *output_redir;
	char message[80];

	// ACT
	cmd = malloc(sizeof(t_command));
	cmd->arguments = ft_lstnew(ft_strdup("ls"));
	input_redir = malloc(sizeof(t_redirection));
	input_redir->target = strdup("infile.txt");
	input_redir->type = strdup("<");
	cmd->redirections = ft_lstnew(input_redir);
	output_redir = malloc(sizeof(t_redirection));
	output_redir->target = strdup("outfile.txt");
	output_redir->type = strdup(">");
	ft_lstadd_back(&cmd->redirections, ft_lstnew(output_redir));
	mk_free_reset_counter();
	free_command(cmd);
	expected_result = 11;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_linked_list)
{
	int expected_result;
	int actual_result;
	t_command *cmd1;
	t_command *cmd2;
	t_command *cmd3;
	t_list *list;
	t_redirection *input_redir1;
	t_redirection *output_redir1;
	t_redirection *input_redir2;
	t_redirection *output_redir2;
	t_redirection *input_redir3;
	t_redirection *output_redir3;
	char message[80];

	cmd1 = malloc(sizeof(t_command));
	cmd1->arguments = ft_lstnew(ft_strdup("cmd_a"));
	input_redir1 = malloc(sizeof(t_redirection));
	input_redir1->target = strdup("infile1.txt");
	input_redir1->type = strdup("<");
	cmd1->redirections = ft_lstnew(input_redir1);
	output_redir1 = malloc(sizeof(t_redirection));
	output_redir1->target = strdup("outfile1.txt");
	output_redir1->type = strdup(">");
	ft_lstadd_back(&cmd1->redirections, ft_lstnew(output_redir1));

	cmd2 = malloc(sizeof(t_command));
	cmd2->arguments = ft_lstnew(ft_strdup("cmd_b"));
	input_redir2 = malloc(sizeof(t_redirection));
	input_redir2->target = strdup("infile2.txt");
	input_redir2->type = strdup("<");
	cmd2->redirections = ft_lstnew(input_redir2);
	output_redir2 = malloc(sizeof(t_redirection));
	output_redir2->target = strdup("outfile2.txt");
	output_redir2->type = strdup(">");
	ft_lstadd_back(&cmd2->redirections, ft_lstnew(output_redir2));

	cmd3 = malloc(sizeof(t_command));
	cmd3->arguments = ft_lstnew(ft_strdup("cmd_c"));
	input_redir3 = malloc(sizeof(t_redirection));
	input_redir3->target = strdup("infile3.txt");
	input_redir3->type = strdup("<");
	cmd3->redirections = ft_lstnew(input_redir3);
	output_redir3 = malloc(sizeof(t_redirection));
	output_redir3->target = strdup("outfile3.txt");
	output_redir3->type = strdup(">");
	ft_lstadd_back(&cmd3->redirections, ft_lstnew(output_redir3));

	list = ft_lstnew(cmd1);
	ft_lstadd_back(&list, ft_lstnew(cmd2));
	ft_lstadd_back(&list, ft_lstnew(cmd3));

	mk_free_reset_counter();
	ft_lstclear(&list, free_command);
	expected_result = 36;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected %d frees, got %d\n",
			 expected_result, actual_result);
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_missing_arguments)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_command *cmd;
	t_redirection *input_redir;
	t_redirection *output_redir;
	char message[80];

	// ACT
	cmd = malloc(sizeof(t_command));
	cmd->arguments = NULL;
	input_redir = malloc(sizeof(t_redirection));
	input_redir->target = strdup("infile.txt");
	input_redir->type = strdup("<");
	cmd->redirections = ft_lstnew(input_redir);
	output_redir = malloc(sizeof(t_redirection));
	output_redir->target = strdup("outfile.txt");
	output_redir->type = strdup(">");
	ft_lstadd_back(&cmd->redirections, ft_lstnew(output_redir));
	mk_free_reset_counter();
	free_command(cmd);
	expected_result = 9;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_missing_input_redirection)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_command *cmd;
	t_redirection *output_redir;
	char message[80];

	// ACT
	cmd = malloc(sizeof(t_command));
	cmd->arguments = ft_lstnew(ft_strdup("ls"));
	cmd->redirections = NULL;
	output_redir = malloc(sizeof(t_redirection));
	output_redir->target = strdup("outfile.txt");
	output_redir->type = strdup(">");
	cmd->redirections = ft_lstnew(output_redir);
	mk_free_reset_counter();
	free_command(cmd);
	expected_result = 7;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_missing_output_redirection)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_command *cmd;
	t_redirection *input_redir;
	char message[80];

	// ACT
	cmd = malloc(sizeof(t_command));
	cmd->arguments = ft_lstnew(ft_strdup("ls"));
	input_redir = malloc(sizeof(t_redirection));
	input_redir->target = strdup("infile.txt");
	input_redir->type = strdup("<");
	cmd->redirections = ft_lstnew(input_redir);
	mk_free_reset_counter();
	free_command(cmd);
	expected_result = 7;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_only_malloc)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	t_command *cmd;
	char message[80];

	// ACT
	cmd = malloc(sizeof(t_command));
	cmd->arguments = NULL;
	cmd->redirections = NULL;
	mk_free_reset_counter();
	free_command(cmd);
	expected_result = 1;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST(test_free_command_null)
{
	// ARRANGE
	int expected_result;
	int actual_result;
	char message[80];

	// ACT
	mk_free_reset_counter();
	free_command(NULL);
	expected_result = 0;
	actual_result = mk_free_get_control_status().counter;
	snprintf(message, sizeof(message),
			 "Expected free function to be called %d times, but it was "
			 "called %d times.\n",
			 expected_result, actual_result);

	// ASSERT
	mu_assert(expected_result == actual_result, message);
}

MU_TEST_SUITE(free_command_test_suite)
{
	MU_RUN_TEST(test_free_command_single);
	MU_RUN_TEST(test_free_command_linked_list);
	MU_RUN_TEST(test_free_command_missing_arguments);
	MU_RUN_TEST(test_free_command_missing_input_redirection);
	MU_RUN_TEST(test_free_command_missing_output_redirection);
	MU_RUN_TEST(test_free_command_only_malloc);
	MU_RUN_TEST(test_free_command_null);
}

int test_free_command(void)
{
	mk_free_activate_counter();
	MU_RUN_SUITE(free_command_test_suite);
	mk_free_reset_control();
	MU_REPORT();
	return MU_EXIT_CODE;
}

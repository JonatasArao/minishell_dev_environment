/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_alloc_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:45:57 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/28 18:36:08 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"
#include "minunit.h"

MU_TEST(test_alloc_command_init)
{
	// ARRANGE
	t_command *cmd;

	// ACT
	mk_malloc_activate_memset_mode();
	cmd = alloc_command();
	mk_malloc_deactivate_memset_mode();

	// ASSERT
	mu_check(cmd != NULL);
	mu_check(cmd->arguments == NULL);
	mu_check(cmd->redirections == NULL);
	mu_check(cmd->pid == -1);
	mu_check(cmd->input_fd == -1);
	mu_check(cmd->output_fd == -1);
	mu_check(cmd->pipe_fd[0] == -1);
	mu_check(cmd->pipe_fd[1] == -1);
	// CLEANUP
	free(cmd);

	// ASSERT - VERIFY ALLOCATION SIZE
	if (memcmp((unsigned char *)cmd + sizeof(t_command), "\xFF\xFF", 2) == 0)
		mu_fail("Allocation size is larger than expected for the command structure");
	else if (memcmp((unsigned char *)cmd + sizeof(t_command), "\xFF", 1) != 0)
		mu_fail("Allocation size is shorter than expected for the command structure");
}

MU_TEST_SUITE(alloc_command_test_suite)
{
	MU_RUN_TEST(test_alloc_command_init);
}

int test_alloc_command(void)
{
	MU_RUN_SUITE(alloc_command_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

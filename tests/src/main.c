/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:10 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/12 16:12:29 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"

int	main(void)
{
	printf(COLORIZE("File: parse/extract_tokens.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: get_token_end\n", STYLE_BOLD, COLOR_CYAN));
	test_get_token_end();
	printf(COLORIZE("Testing function: get_next_token\n", STYLE_BOLD, COLOR_CYAN));
	test_get_next_token();
	printf(COLORIZE("Testing function: extract_tokens\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_tokens();

	printf(COLORIZE("File: parse/token_checks.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: is_input_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_input_redirection();
	printf(COLORIZE("Testing function: is_output_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_output_redirection();
	printf(COLORIZE("Testing function: is_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_redirection();
	printf(COLORIZE("Testing function: is_pipe\n", STYLE_BOLD, COLOR_CYAN));
	test_is_pipe();

	printf(COLORIZE("File: parse/token_validation.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: is_valid_quotes\n", STYLE_BOLD, COLOR_CYAN));
	test_is_valid_quotes();
	printf(COLORIZE("Testing function: is_token_list_valid\n", STYLE_BOLD, COLOR_CYAN));
	test_is_token_list_valid();

	printf(COLORIZE("File: parse/command_cleanup.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: free_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_free_redirection();
	printf(COLORIZE("Testing function: free_command\n", STYLE_BOLD, COLOR_CYAN));
	test_free_command();

	printf(COLORIZE("File: parse/command_list.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: lstadd_str\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_str();
	printf(COLORIZE("Testing function: lstadd_redir\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_redir();

	printf(COLORIZE("File: parse/extract_commands.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: alloc_command\n", STYLE_BOLD, COLOR_CYAN));
	test_alloc_command();
	printf(COLORIZE("Testing function: parse_tokens\n", STYLE_BOLD, COLOR_CYAN));
	test_parse_tokens();
	printf(COLORIZE("Testing function: extract_commands\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_commands();

	printf(COLORIZE("File: expand/env_vars_list.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: free_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_free_env_var();
	printf(COLORIZE("Testing function: lstadd_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_env_var();
	printf(COLORIZE("Testing function: get_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_get_env_var();
	printf(COLORIZE("Testing function: lstset_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_lstset_env_var();
	printf(COLORIZE("Testing function: extract_env_vars\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_env_vars();
	return (0);
}

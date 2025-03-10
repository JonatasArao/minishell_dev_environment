/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:10 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/24 20:06:48 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"

int	main(void)
{
	// Testing functions from parse/extract_tokens.c
	printf(COLORIZE("File: parse/extract_tokens.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: get_token_end\n", STYLE_BOLD, COLOR_CYAN));
	test_get_token_end();
	printf(COLORIZE("Testing function: get_next_token\n", STYLE_BOLD, COLOR_CYAN));
	test_get_next_token();
	printf(COLORIZE("Testing function: extract_tokens\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_tokens();
	// Testing functions from parse/token_checks.c
	printf(COLORIZE("File: parse/token_checks.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: heredoc\n", STYLE_BOLD, COLOR_CYAN));
	test_is_heredoc();
	printf(COLORIZE("Testing function: is_input_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_input_redirection();
	printf(COLORIZE("Testing function: is_output_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_output_redirection();
	printf(COLORIZE("Testing function: is_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_redirection();
	printf(COLORIZE("Testing function: is_pipe\n", STYLE_BOLD, COLOR_CYAN));
	test_is_pipe();
	// Testing functions from parse/token_validation.c
	printf(COLORIZE("File: parse/token_validation.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: is_valid_quotes\n", STYLE_BOLD, COLOR_CYAN));
	test_is_valid_quotes();
	printf(COLORIZE("Testing function: is_token_list_valid\n", STYLE_BOLD, COLOR_CYAN));
	test_is_token_list_valid();
	// Testing functions from parse/command_cleanup.c
	printf(COLORIZE("File: parse/command_cleanup.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: free_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_free_redirection();
	printf(COLORIZE("Testing function: free_command\n", STYLE_BOLD, COLOR_CYAN));
	test_free_command();
	// Testing functions from parse/command_list.c
	printf(COLORIZE("File: parse/command_list.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: lstadd_str\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_str();
	printf(COLORIZE("Testing function: lstadd_redir\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_redir();
	// Testing functions from parse/extract_commands.c
	printf(COLORIZE("File: parse/extract_commands.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: alloc_command\n", STYLE_BOLD, COLOR_CYAN));
	test_alloc_command();
	printf(COLORIZE("Testing function: parse_tokens\n", STYLE_BOLD, COLOR_CYAN));
	test_parse_tokens();
	printf(COLORIZE("Testing function: extract_commands\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_commands();
	// Testing functions from expand/env_vars_list.c
	printf(COLORIZE("File: expand/env_vars_list.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: free_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_free_env_var();
	printf(COLORIZE("Testing function: lstadd_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_lstadd_env_var();
	printf(COLORIZE("Testing function: get_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_get_env_var();
	printf(COLORIZE("Testing function: lstset_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_lstset_env_var();
	printf(COLORIZE("Testing function: lstrm_env_var\n", STYLE_BOLD, COLOR_CYAN));
	test_lstrm_env_var();
	// Testing functions from expand/envp_manager.c
	printf(COLORIZE("File: expand/envp_manager.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: create_env_string\n", STYLE_BOLD, COLOR_CYAN));
	test_create_env_string();
	printf(COLORIZE("Testing function: get_envp\n", STYLE_BOLD, COLOR_CYAN));
	test_get_envp();
	printf(COLORIZE("Testing function: extract_env_vars\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_env_vars();
	// Testing functions from expand/extract_vars.c
	printf(COLORIZE("File: expand/extract_vars.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: get_var_end\n", STYLE_BOLD, COLOR_CYAN));
	test_get_var_end();
	printf(COLORIZE("Testing function: get_next_var\n", STYLE_BOLD, COLOR_CYAN));
	test_get_next_var();
	printf(COLORIZE("Testing function: extract_vars\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_vars();
	// Testing functions from expand/expand_token.c
	printf(COLORIZE("File: expand/expand_token.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: get_var_value\n", STYLE_BOLD, COLOR_CYAN));
	test_get_var_value();
	printf(COLORIZE("Testing function: concat_vars\n", STYLE_BOLD, COLOR_CYAN));
	test_concat_vars();
	printf(COLORIZE("Testing function: expand_quotes\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_quotes();
	printf(COLORIZE("Testing function: expand_var\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_var();
	printf(COLORIZE("Testing function: expand_token\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_token();
	// Testing functions from expand/expand_commands.c
	printf(COLORIZE("File: expand/expand_commands.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: is_ambiguous_redirect\n", STYLE_BOLD, COLOR_CYAN));
	test_is_ambiguous_redirect();
	printf(COLORIZE("Testing function: expand_redir\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_redir();
	printf(COLORIZE("Testing function: expand_arguments\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_arguments();
	printf(COLORIZE("Testing function: expand_commands\n", STYLE_BOLD, COLOR_CYAN));
	test_expand_commands();
	// Testing functions from builtins/msh_echo.c
	printf(COLORIZE("File: builtins/echo.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: msh_echo\n", STYLE_BOLD, COLOR_CYAN));
	test_msh_echo();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:10 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/08 21:57:55 by jarao-de         ###   ########.fr       */
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
	printf(COLORIZE("File: parse/token_validation.c\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: is_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_is_redirection();
	printf(COLORIZE("Testing function: is_valid_quotes\n", STYLE_BOLD, COLOR_CYAN));
	test_is_valid_quotes();
	printf(COLORIZE("Testing function: is_pipe\n", STYLE_BOLD, COLOR_CYAN));
	test_is_pipe();
	printf(COLORIZE("Testing function: is_token_list_valid\n", STYLE_BOLD, COLOR_CYAN));
	test_is_token_list_valid();
	printf(COLORIZE("Testing function: free_redirection\n", STYLE_BOLD, COLOR_CYAN));
	test_free_redirection();
	printf(COLORIZE("Testing function: free_command\n", STYLE_BOLD, COLOR_CYAN));
	test_free_command();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:10 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 11:37:13 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"

int	main(void)
{
	printf(COLORIZE("File: parse/extract_token\n", STYLE_BOLD, COLOR_MAGENTA));
	printf(COLORIZE("Testing function: get_token_end\n", STYLE_BOLD, COLOR_CYAN));
	test_get_token_end();
	printf(COLORIZE("Testing function: get_next_token\n", STYLE_BOLD, COLOR_CYAN));
	test_get_next_token();
	printf(COLORIZE("Testing function: extract_token\n", STYLE_BOLD, COLOR_CYAN));
	test_extract_token();
	return (0);
}

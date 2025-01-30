/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:26:10 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/30 10:37:27 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tests.h"

int	main(void)
{
	t_readline_control readline_control;

	(void) readline_control;
	set_readline_predefined_response("hello");
	activate_readline_failure_mode(2);
	readline_control = get_readline_control_status();
	program_main();
	readline_control = get_readline_control_status();
	return (0);
}

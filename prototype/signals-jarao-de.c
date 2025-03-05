/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-jarao-de.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:36:43 by jarao-de          #+#    #+#             */
/*   Updated: 2025/03/05 00:52:54 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct sigaction	t_sigaction;

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	int	is_user_signal;

	(void) context;
	ft_putchar_fd('\n', 1);
	is_user_signal = (info->si_code == SI_USER);
	if (sig == SIGINT && is_user_signal)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	t_sigaction	action;

	action.sa_sigaction = handle_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void) argc;
	(void) argv;
	setup_signal_handlers();
	init_minishell(&msh, envp);
	if (!msh.env_vars)
		return (1);
	while (1)
	{
		msh.input = readline("Minishell $ ");
		if (msh.input == NULL)
			break ;
		if (!ft_strall(msh.input, ft_isspace))
			add_history(msh.input);
		if (process_input(&msh))
			msh.last_status = execute_commands(&msh);
		free_minishell_loop(&msh);
	}
	printf("exit\n");
	destroy_minishell(&msh);
	return (0);
}

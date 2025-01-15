/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_prompt-jarao-de.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:13:35 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/15 16:30:51 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * Lê uma linha de entrada com o prompt "Digite algo: "
 * readline("Digite algo: ") - Esta função exibe o prompt e espera que o
 * usuário digite algo. Retorna a linha digitada ou NULL se houver um erro
 * ou EOF.
 *
 * Se a entrada for NULL, saímos do loop
 * if (input == NULL) - Verifica se a entrada é NULL, indicando que o usuário
 * pressionou Ctrl+D ou houve um erro.
 *
 * Se a entrada for "sair", saímos do loop
 * if (strcmp(input, "sair") == 0) - Compara a entrada com a string "sair".
 * Se forem iguais, saímos do loop.
 *
 * Adiciona a linha lida ao histórico
 * add_history(input) - Adiciona a linha digitada ao histórico de comandos
 * do readline.
 *
 * Informa ao readline que uma nova linha está sendo iniciada
 * rl_on_new_line() - Informa ao readline que uma nova linha está sendo
 * iniciada.
 *
 * Substitui a linha atual pela nova linha "Nova linha substituída"
 * rl_replace_line("Nova linha substituída", 0) - Substitui a linha atual
 * pela string fornecida.
 *
 * Redesenha a linha atual
 * rl_redisplay() - Redesenha a linha atual no prompt.
 *
 * Imprime a linha lida
 * printf("Você digitou: %s\n", input) - Imprime a linha digitada pelo
 * usuário.
 *
 * Libera a memória alocada para a entrada
 * free(input) - Libera a memória alocada para a linha digitada.
 *
 * Limpa o histórico de linhas lidas
 * rl_clear_history() - Limpa o histórico de comandos armazenado pelo
 * readline.
 */

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Digite algo: ");
		if (input == NULL)
			break ;
		if (strcmp(input, "sair") == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		rl_on_new_line();
		rl_replace_line("Nova linha substituída", 0);
		rl_redisplay();
		printf("\nVocê digitou: %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}

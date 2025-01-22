/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prompt-jarao-de.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:13:35 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/22 09:22:20 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
 * Tokeniza a entrada e imprime os tokens
 * tokenize(input) - Chama a função tokenize para dividir a entrada em tokens
 * e imprimir cada token.
 *
 * Adiciona a linha lida ao histórico
 * add_history(input) - Adiciona a linha digitada ao histórico de comandos
 * do readline.
 *
 * Libera a memória alocada para a entrada
 * free(input) - Libera a memória alocada para a linha digitada.
 *
 * Limpa o histórico de linhas lidas
 * rl_clear_history() - Limpa o histórico de comandos armazenado pelo
 * readline.
 */

void	tokenize(char *input)
{
	char	*input_copy;
	char	*token;

	input_copy = ft_strdup(input);
	token = ft_strtok(input_copy, " ");
	while (token != NULL)
	{
		printf("Token: %s\n", token);
		token = ft_strtok(NULL, " ");
	}
	free(input_copy);
}

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
		tokenize(input);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}

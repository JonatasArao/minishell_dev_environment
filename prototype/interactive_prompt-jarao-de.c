/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_prompt-jarao-de.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:13:35 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/15 16:30:55 by jarao-de         ###   ########.fr       */
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
 * Define a resposta apropriada com base na entrada
 * set_response(&response, input) - Define a função de resposta apropriada
 * com base na entrada do usuário. A função verifica a string de entrada e
 * compara com valores predefinidos ("ola", "sim", "nao"). Se houver uma
 * correspondência, a função de resposta correspondente é atribuída ao ponteiro
 * de função 'execute' na estrutura 'response'. Se não houver correspondência,
 * a função 'response_default' é atribuída.
 *
 * Adiciona a linha lida ao histórico
 * add_history(input) - Adiciona a linha digitada ao histórico de comandos
 * do readline.
 *
 * Executa a resposta definida
 * response.execute() - Chama a função de resposta definida anteriormente.
 *
 * Libera a memória alocada para a entrada
 * free(input) - Libera a memória alocada para a linha digitada.
 *
 * Limpa o histórico de linhas lidas
 * rl_clear_history() - Limpa o histórico de comandos armazenado pelo
 * readline.
 */

typedef struct s_response
{
	void	(*execute)(void);
}	t_response;

void	response_ola(void)
{
	printf("Olá, tudo bem?\n");
}

void	response_sim(void)
{
	printf("Que bom\n");
}

void	response_nao(void)
{
	printf("Que pena\n");
}

void	response_default(void)
{
	printf("Desculpe, não entendi.\n");
}

void	set_response(t_response *response, const char *input)
{
	if (strcmp(input, "ola") == 0)
		response->execute = response_ola;
	else if (strcmp(input, "sim") == 0)
		response->execute = response_sim;
	else if (strcmp(input, "nao") == 0)
		response->execute = response_nao;
	else
		response->execute = response_default;
}

int	main(void)
{
	char		*input;
	t_response	response;

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
		set_response(&response, input);
		add_history(input);
		response.execute();
		free(input);
	}
	rl_clear_history();
	return (0);
}

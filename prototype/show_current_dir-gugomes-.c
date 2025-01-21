/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_current_dir-gugomes-.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:10:24 by gugomes-          #+#    #+#             */
/*   Updated: 2025/01/21 17:35:46 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

/*
 * Obtém e exibe o diretório de trabalho atual
 * getcwd(cwd, sizeof(cwd)) - Esta função retorna o diretório de trabalho
 * atual do processo. O primeiro parâmetro é um buffer (cwd) onde o
 * diretório será armazenado, e o segundo é o tamanho desse buffer. Se a
 * função for bem-sucedida, ela retorna o diretório atual. Caso contrário,
 * retorna NULL e o erro pode ser verificado com a função perror.
 */

void	find_current_directory(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Directory: %s\n", cwd);
	else
		perror("Error finding directory");
}


int	main(void)
{
	find_current_directory();
	return (0);
}



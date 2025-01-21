/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_navigation-jarao-de.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:56:57 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/21 17:21:00 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

/*
 * Este arquivo contém funções para navegação de diretórios.
 * A função find_current_directory() obtém e exibe o diretório de trabalho
 * atual. A função getcwd(cwd, sizeof(cwd)) é usada para obter o diretório
 * de trabalho atual do processo. O primeiro parâmetro é um buffer (cwd)
 * onde o diretório será armazenado, e o segundo é o tamanho desse buffer.
 * Se a função for bem-sucedida, ela retorna o diretório atual. Caso
 * contrário, retorna NULL e o erro pode ser verificado com a função perror.
 * A função main() altera o diretório de trabalho para o especificado pelo
 * usuário e exibe o novo diretório de trabalho. Se a mudança de diretório
 * falhar, um erro é exibido usando perror.
 */

void	find_current_directory(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Directory: %s\n", cwd);
	else
		perror("Error finding directory");
}


int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
		return (1);
	}
	if (chdir(argv[1]) == 0)
		find_current_directory();
	else
		perror("chdir() error");
	return (0);
}

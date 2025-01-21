/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_manipulation-jarao-de.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:19:59 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/21 17:36:56 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>

/*
 * Este arquivo contém funções para manipulação de diretórios. A função
 * list_directory_contents(DIR *dir) lista o conteúdo de um diretório
 * especificado. Ela utiliza a função readdir para ler as entradas do
 * diretório e exibe informações detalhadas sobre cada entrada, como nome,
 * número do inode, deslocamento para a próxima entrada, comprimento do
 * registro e tipo de arquivo. A função main(int argc, char *argv[]) abre
 * o diretório especificado pelo usuário, chama a função
 * list_directory_contents para listar seu conteúdo e, em seguida, fecha
 * o diretório. Se o diretório não puder ser aberto, uma mensagem de erro
 * é exibida.
 */

void	list_directory_contents(DIR *dir)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		printf("Name: %s\n", entry->d_name);
		printf("Inode number: %ld\n", entry->d_ino);
		printf("Offset to the next dirent: %ld\n", entry->d_off);
		printf("Length of this record: %d\n", entry->d_reclen);
		printf("Type of file: %d\n", entry->d_type);
		printf("----------------------------------------------\n");
		entry = readdir(dir);
	}
}


int	main(int argc, char *argv[])
{
	DIR	*dir;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
		return (1);
	}
	dir = opendir(argv[1]);
	if (dir)
	{
		list_directory_contents(dir);
		closedir(dir);
	}
	else
	{
		perror("Erro ao abrir diretório");
		return (1);
	}
	return (0);
}

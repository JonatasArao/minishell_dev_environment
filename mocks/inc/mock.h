/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:12:57 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/28 14:40:54 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOCK_H
# define MOCK_H
# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <dlfcn.h>

typedef struct s_free_control{
	int counter_active;
	int counter;
} t_free_control;

typedef struct s_malloc_control {
	int memset_active;
	int failure_active;
	int failure_threshold;
	int failure_counter;
	int counter_active;
	int counter;
} t_malloc_control;

#endif

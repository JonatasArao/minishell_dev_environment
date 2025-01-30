/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:17:33 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/30 07:25:17 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock.h"

// Global variable to control the mock free function
t_free_control free_control =
{
	.counter = 0,
	.counter_active = 0
};

void	mk_free_activate_counter(void)
{
	free_control.counter_active = 1;
}

void	mk_free_deactivate_counter(void)
{
	free_control.counter_active = 0;
}

void	mk_free_reset_counter(void)
{
	free_control.counter = 0;
}

void	mk_free_reset_control(void)
{
	free_control.counter = 0;
	free_control.counter_active = 0;
}

t_free_control	mk_free_get_control_status(void)
{
	return (free_control);
}

// Mock free function
void	free(void	*ptr)
{
	void(*original_free)(void *); // Pointer to the original free function
	char *error;

	// Get the pointer to the original free function
	#ifdef __linux__
	original_free = dlsym(RTLD_NEXT, "free");
	#elif __APPLE__
	original_free = dlsym(RTLD_DEFAULT, "free");
	#endif
	if ((error = dlerror()) != NULL)
	{ // Check for errors in dlsym
		fprintf(stderr, "%s\n", error); // Print the error message
		exit(EXIT_FAILURE); // Exit the program in case of error
	}
	// If counter behavior is active, increment the counter
	if (free_control.counter_active)
		free_control.counter++;
	// Call the original free function
	original_free(ptr);
}

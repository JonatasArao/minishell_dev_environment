/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:17:33 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/21 15:13:20 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock.h"

// Global variables to control the behavior of the mock free function
int mock_free_counter_active = 0; // Flag to activate counter behavior in free
int mock_free_counter; // Counter to keep track of free calls

// Mock free function
void free(void *ptr) {
	void (*original_free)(void *); // Pointer to the original free function
	char *error;

	// Get the pointer to the original free function
	#ifdef __linux__
	original_free = dlsym(RTLD_NEXT, "free");
	#elif __APPLE__
	original_free = dlsym(RTLD_DEFAULT, "free");
	#endif
	if ((error = dlerror()) != NULL) { // Check for errors in dlsym
		fprintf(stderr, "%s\n", error); // Print the error message
		exit(EXIT_FAILURE); // Exit the program in case of error
	}

	// If counter behavior is active, increment the counter
	if (mock_free_counter_active)
		mock_free_counter++;

	// Call the original free function
	original_free(ptr);
}

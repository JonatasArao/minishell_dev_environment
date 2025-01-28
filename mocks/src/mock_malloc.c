/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:17:33 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/28 14:42:53 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock.h"

// Global variable to control the mock malloc behavior
t_malloc_control malloc_control = {
	.failure_counter = 0,
	.failure_threshold = 0,
	.failure_active = 1,
	.counter = 0,
	.counter_active = 0,
	.memset_active = 0
};

// Mock malloc function
void* malloc(size_t size) {
	void *(*original_malloc)(size_t); // Function pointer to the original malloc
	char *error;

	// Get the pointer to the original malloc function
	#ifdef __linux__
	original_malloc = dlsym(RTLD_NEXT, "malloc");
	#elif __APPLE__
	original_malloc = dlsym(RTLD_DEFAULT, "malloc");
	#endif

	if ((error = dlerror()) != NULL) { // Check for errors in dlsym
		fprintf(stderr, "%s\n", error); // Print the error message
		exit(EXIT_FAILURE); // Exit the program on error
	}

	// If failure mode is active and the call count matches, return NULL
	if (malloc_control.failure_active) {
		malloc_control.failure_counter++;
		if (malloc_control.failure_counter >= malloc_control.failure_threshold) {
			malloc_control.failure_counter = 0;
			return (NULL);
		}
	}

	// If counter behavior is active, increment the counter
	if (malloc_control.counter_active)
		malloc_control.counter++;

	// If memset mode is active, allocate memory and set it to 0xFF
	if (malloc_control.memset_active) {
		void *tmp = original_malloc(size + 1); // Allocate extra byte for memset
		if (tmp != NULL) {
			memset(tmp, 0xFF, size + 1); // Set allocated memory to 0xFF
		}
		return (tmp); // Return the allocated memory
	}

	// Otherwise, just return the result of the original malloc
	return (original_malloc(size));
}

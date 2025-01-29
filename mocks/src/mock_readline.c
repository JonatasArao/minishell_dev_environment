/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:45:19 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/29 10:18:59 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock.h"

// Global variable to control the mock readline function
t_readline_control readline_control = {
	.counter_active = 0,
	.counter = 0,
	.failure_active = 0,
	.failure_counter = 0,
	.failure_threshold = 0,
	.predefined_response = NULL
};

void activate_readline_counter(void) {
	readline_control.counter_active = 1;
}

void deactivate_readline_counter(void) {
	readline_control.counter_active = 0;
}

void activate_readline_failure_mode(int threshold) {
	readline_control.failure_active = 1;
	readline_control.failure_threshold = threshold;
	readline_control.failure_counter = 0;
}

void deactivate_readline_failure_mode(void) {
	readline_control.failure_active = 0;
	readline_control.failure_counter = 0;
}

void set_readline_predefined_response(const char *response) {
	if (readline_control.predefined_response != NULL) {
		free(readline_control.predefined_response);
	}
	readline_control.predefined_response = strdup(response);
	if (readline_control.predefined_response == NULL) {
		fprintf(stderr, "Failed to allocate memory for predefined response\n");
		exit(EXIT_FAILURE);
	}
}

void clear_readline_predefined_response(void) {
	if (readline_control.predefined_response != NULL) {
		free(readline_control.predefined_response);
		readline_control.predefined_response = NULL;
	}
}

void reset_readline_control(void) {
	readline_control.counter_active = 0;
	readline_control.counter = 0;
	readline_control.failure_active = 0;
	readline_control.failure_threshold = 0;
	clear_readline_predefined_response();
}

t_readline_control get_readline_control_status(void) {
	return (readline_control);
}

// Mock readline function
char *readline(const char *prompt) {
	char *(*original_readline)(const char *); // Pointer to the original readline function
	char *error;

	// Get the pointer to the original readline function
	#ifdef __linux__
	original_readline = dlsym(RTLD_NEXT, "readline");
	#elif __APPLE__
	original_readline = dlsym(RTLD_DEFAULT, "readline");
	#endif
	if ((error = dlerror()) != NULL) { // Check for errors in dlsym
		fprintf(stderr, "%s\n", error); // Print the error message
		exit(EXIT_FAILURE); // Exit the program in case of error
	}

	// If failure mode is active and the call count matches, return NULL
	if (readline_control.failure_active) {
		readline_control.failure_counter++;
		if (readline_control.failure_counter >= readline_control.failure_threshold)
			return NULL;
	}

	// If counter behavior is active, increment the counter
	if (readline_control.counter_active)
		readline_control.counter++;

	// If a predefined response is set, return it
	if (readline_control.predefined_response != NULL) {
		char *response = strdup(readline_control.predefined_response);
		if (response == NULL) {
			fprintf(stderr, "Failed to allocate memory for predefined response\n");
			exit(EXIT_FAILURE);
		}
		return (response);
	}

	// Call the original readline function
	return (original_readline(prompt));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:45:19 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 07:13:42 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock.h"

// Global variable to control the mock readline function
static t_readline_control readline_control =
{
	.counter_active = 0,
	.counter = 0,
	.failure_active = 0,
	.failure_counter = 0,
	.failure_threshold = 0,
	.current_response_counter = 0,
	.predefined_response = NULL
};

void	mk_readline_activate_counter(void)
{
	readline_control.counter_active = 1;
}

void	mk_readline_deactivate_counter(void)
{
	readline_control.counter_active = 0;
}

void	mk_readline_reset_counter(void)
{
	readline_control.counter = 0;
}

void	mk_readline_activate_failure_mode(int threshold)
{
	readline_control.failure_active = 1;
	readline_control.failure_threshold = threshold;
	readline_control.failure_counter = 0;
}

void	mk_readline_deactivate_failure_mode(void)
{
	readline_control.failure_active = 0;
	readline_control.failure_counter = 0;
}

void	mk_readline_set_predefined_response(const char **response)
{
	int i;
	int count;

	// Clear any existing predefined response
	mk_readline_clear_predefined_response();
	// Count the number of responses
	count = 0;
	while (response[count] != NULL)
		count++;
	// Allocate memory for the predefined responses
	readline_control.predefined_response = (char **)malloc((count + 1) * sizeof(char *));
	if (readline_control.predefined_response == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for predefined responses\n");
		exit(EXIT_FAILURE);
	}
	// Copy the responses
	i = 0;
	while (i < count)
	{
		readline_control.predefined_response[i] = strdup(response[i]);
		if (readline_control.predefined_response[i] == NULL)
		{
			fprintf(stderr, "Failed to allocate memory for predefined response\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	readline_control.predefined_response[count] = NULL; // Null-terminate the array
}

void	mk_readline_clear_predefined_response(void)
{
	int	i;

	i = 0;
	if (readline_control.predefined_response != NULL)
	{
		while (readline_control.predefined_response[i] != NULL)
		{
			if (readline_control.predefined_response[i] != NULL)
				free(readline_control.predefined_response[i]);
			i++;
		}
		free(readline_control.predefined_response);
		readline_control.predefined_response = NULL;
	}
}

void	mk_readline_reset_control(void)
{
	readline_control.counter_active = 0;
	readline_control.counter = 0;
	readline_control.failure_active = 0;
	readline_control.failure_threshold = 0;
	mk_readline_clear_predefined_response();
}

t_readline_control	mk_readline_get_control_status(void)
{
	return (readline_control);
}

// Mock readline function
char	*readline(const char *prompt)
{
	char *(*original_readline)(const char *); // Pointer to the original readline function
	char *error;
	char *response;

	// Get the pointer to the original readline function
	#ifdef __linux__
	original_readline = dlsym(RTLD_NEXT, "readline");
	#elif __APPLE__
	original_readline = dlsym(RTLD_DEFAULT, "readline");
	#endif
	if ((error = dlerror()) != NULL)
	{ // Check for errors in dlsym
		fprintf(stderr, "%s\n", error); // Print the error message
		exit(EXIT_FAILURE); // Exit the program in case of error
	}
	// If failure mode is active and the call count matches, return NULL
	if (readline_control.failure_active)
	{
		readline_control.failure_counter++;
		if (readline_control.failure_counter >= readline_control.failure_threshold)
			return NULL;
	}
	// If counter behavior is active, increment the counter
	if (readline_control.counter_active)
		readline_control.counter++;
	// If a predefined response is set, return it
	if (readline_control.predefined_response != NULL)
	{
		if (readline_control.predefined_response
			[readline_control.current_response_counter])
		{
			response = strdup(readline_control.predefined_response
				[readline_control.current_response_counter]);
			if (response == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for predefined response\n");
				exit(EXIT_FAILURE);
			}
			readline_control.current_response_counter++;
		}
		else
			response = NULL;
		return (response);
	}
	// Call the original readline function
	return (original_readline(prompt));
}

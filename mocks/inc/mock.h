/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:12:57 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 07:15:35 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOCK_H
# define MOCK_H
# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <dlfcn.h>

/**
 * @file mock.h
 * @brief Header file for mock-related structures and definitions.
 */

/**
 * @struct s_free_control
 * @brief Structure to control the free operation counters.
 *
 * This structure is used to keep track of the number of active and total
 * free operations.
 *
 * @var s_free_control::counter_active
 * Member 'counter_active' indicates the number of currently active free
 * operations.
 *
 * @var s_free_control::counter
 * Member 'counter' indicates the total number of free operations.
 */
typedef struct s_free_control{
	int	counter_active;
	int	counter;
}	t_free_control;

/**
 * @struct s_malloc_control
 * @brief Structure to control memory allocation behavior for testing purposes.
 *
 * This structure is used to simulate different memory allocation scenarios
 * such as memset activation, counter activation, and failure conditions.
 *
 * @var s_malloc_control::memset_active
 * Flag to indicate if memset should be active.
 *
 * @var s_malloc_control::counter_active
 * Flag to indicate if the counter should be active.
 *
 * @var s_malloc_control::counter
 * Counter to keep track of memory allocations.
 *
 * @var s_malloc_control::failure_active
 * Flag to indicate if memory allocation failure simulation should be active.
 *
 * @var s_malloc_control::failure_counter
 * Counter to keep track of memory allocation failures.
 *
 * @var s_malloc_control::failure_threshold
 * Threshold value to trigger memory allocation failure.
 */
typedef struct s_malloc_control {
	int	memset_active;
	int	counter_active;
	int	counter;
	int	failure_active;
	int	failure_counter;
	int	failure_threshold;
}	t_malloc_control;

/**
 * @struct s_readline_control
 * @brief Structure to control the behavior of the readline function in tests.
 *
 * This structure is used to simulate and control the behavior of the readline
 * function during testing. It allows for predefined responses and failure
 * conditions to be set.
 *
 * @var s_readline_control::counter_active
 * Indicates if the counter is active.
 *
 * @var s_readline_control::counter
 * Keeps track of the number of times the readline function has been called.
 *
 * @var s_readline_control::failure_active
 * Indicates if failure simulation is active.
 *
 * @var s_readline_control::failure_counter
 * Keeps track of the number of times the readline function has failed.
 *
 * @var s_readline_control::failure_threshold
 * The threshold at which the readline function should simulate a failure.
 *
 * @var s_readline_control::predefined_response
 * A predefined response that the readline function should return.
 */
typedef struct s_readline_control{
	int		counter_active;
	int		counter;
	int		failure_active;
	int		failure_counter;
	int		failure_threshold;
	int		current_response_counter;
	char	**predefined_response;
}	t_readline_control;

// Malloc control functions
/**
 * @brief Activates the malloc counter.
 *
 * This function enables the tracking of memory allocations by incrementing
 * a counter each time a malloc operation is performed. It is useful for
 * debugging and ensuring that memory is being allocated and freed correctly.
 */
void				mk_malloc_activate_counter(void);
/**
 * @brief Deactivates the malloc counter.
 *
 * This function is used to deactivate the malloc counter, which is likely
 * used for tracking memory allocations in the program. Once deactivated,
 * the malloc counter will no longer track memory allocations.
 */
void				mk_malloc_deactivate_counter(void);
/**
 * @brief Resets the internal counter used to track the number of malloc calls.
 *
 * This function is typically used in a testing or debugging environment to
 * reset the count of memory allocations made via malloc. It can be useful
 * for verifying that memory allocation behavior is as expected.
 */
void				mk_malloc_reset_counter(void);
/**
 * @brief Activates a mode where malloc will fail after a certain number of
 * allocations.
 *
 * This function sets a threshold for the number of successful malloc calls.
 * Once the threshold is reached, subsequent malloc calls will fail, simulating
 * a memory allocation failure.
 *
 * @param threshold The number of successful malloc calls before failure mode
 * is activated.
 */
void				mk_malloc_activate_failure_mode(size_t threshold);
/**
 * @brief Deactivates the malloc failure mode.
 *
 * This function disables the mode where malloc is forced to fail,
 * allowing memory allocations to proceed normally.
 */
void				mk_malloc_deactivate_failure_mode(void);
/**
 * @brief Activates a mode where malloc and memset operations are mocked.
 *
 * This function enables a special mode for testing purposes where the
 * behavior of memory allocation and initialization functions (malloc and
 * memset) are simulated. This can be useful for unit testing to ensure
 * that memory-related operations are handled correctly without actually
 * performing them.
 */
void				mk_malloc_activate_memset_mode(void);
/**
 * @brief Deactivates the malloc memset mode.
 *
 * This function is used to turn off the mode where malloc is
 * combined with memset. It is typically used in testing or
 * debugging scenarios to control memory allocation behavior.
 */
void				mk_malloc_deactivate_memset_mode(void);
/**
 * @brief Resets the malloc control mechanism.
 *
 * This function is used to reset any controls or counters related to
 * dynamic memory allocation. It is typically used in a testing or
 * debugging environment to ensure that the state of memory allocation
 * is clean and consistent before running a new test or operation.
 */
void				mk_malloc_reset_control(void);
/**
 * @brief Retrieves the current status of the malloc control.
 *
 * This function returns the current status of the malloc control, which
 * can be used to monitor and manage memory allocation within the program.
 *
 * @return t_malloc_control The current status of the malloc control.
 */
t_malloc_control	mk_malloc_get_control_status(void);

// Free control functions
/**
 * @brief Activates the free counter mechanism.
 *
 * This function enables the tracking of memory allocations and deallocations
 * to help identify memory leaks or improper memory management within the
 * application.
 */
void				mk_free_activate_counter(void);
/**
 * @brief Deactivates the free counter.
 *
 * This function is used to deactivate the free counter mechanism.
 * It should be called when the free counter is no longer needed.
 */
void				mk_free_deactivate_counter(void);
/**
 * @brief Resets the free counter to its initial state.
 *
 * This function is used to reset the counter that tracks the number of
 * free operations performed. It is typically used in a testing or
 * debugging context to ensure that memory management operations are
 * being tracked accurately.
 */
void				mk_free_reset_counter(void);
/**
 * @brief Resets the free control mechanism.
 *
 * This function is used to reset the control mechanism that manages
 * the freeing of resources. It should be called to ensure that the
 * control state is properly initialized or reset.
 */
void				mk_free_reset_control(void);
/**
 * @brief Retrieves the current status of the free control mechanism.
 *
 * This function returns the current status of the free control mechanism,
 * which is used to manage memory deallocation within the minishell project.
 *
 * @return t_free_control The current status of the free control mechanism.
 */
t_free_control		mk_free_get_control_status(void);

// Readline control functions
/**
 * @brief Activates the readline counter.
 *
 * This function enables the readline counter, which is used to keep track
 * of the number of lines read. It is typically used in scenarios where
 * monitoring the number of lines read from an input source is necessary.
 */
void				mk_readline_activate_counter(void);
/**
 * @brief Deactivates the readline counter.
 *
 * This function is used to disable the counter that tracks the number of
 * readline operations. It can be useful in scenarios where the readline
 * counter is no longer needed or should be reset.
 */
void				mk_readline_deactivate_counter(void);
/**
 * @brief Resets the readline counter to its initial state.
 *
 * This function is used to reset the internal counter used by the readline
 * functionality. It should be called whenever the counter needs to be
 * reinitialized.
 */
void	mk_readline_reset_counter(void);
/**
 * @brief Activates the readline failure mode.
 *
 * This function sets the readline failure mode to be activated after a
 * specified number of successful readline calls. Once the threshold is
 * reached, subsequent readline calls will simulate a failure.
 *
 * @param threshold The number of successful readline calls before failure
 * mode is activated.
 */
void				mk_readline_activate_failure_mode(int threshold);
/**
 * @brief Deactivates the readline failure mode.
 *
 * This function is used to turn off the failure mode for the readline
 * functionality, restoring normal operation.
 */
void				mk_readline_deactivate_failure_mode(void);
/**
 * @brief Sets a predefined response for the readline function.
 *
 * This function allows you to specify a predefined response that will be used
 * by the readline function. This is useful for testing purposes where you want
 * to simulate user input.
 *
 * @param response A null-terminated array of strings to be used as responses
 * by readline.
 */
void				mk_readline_set_predefined_response(const char **response);
/**
 * @brief Clears the predefined response for readline.
 *
 * This function resets any predefined response that has been set for the
 * readline function, ensuring that subsequent calls to readline do not
 * return any previously set responses.
 */
void				mk_readline_clear_predefined_response(void);
/**
 * @brief Resets the readline control settings to their default state.
 *
 * This function is used to reset any modifications made to the readline
 * control settings, ensuring that the readline environment is returned
 * to its initial configuration.
 */
void				mk_readline_reset_control(void);
/**
 * @brief Retrieves the current status of the readline control.
 *
 * This function returns the status of the readline control, which can be used
 * to determine the current state of the readline functionality.
 *
 * @return t_readline_control The current status of the readline control.
 */
t_readline_control	mk_readline_get_control_status(void);

#endif

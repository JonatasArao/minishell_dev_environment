/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tests.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:57:40 by jarao-de          #+#    #+#             */
/*   Updated: 2025/02/18 19:54:29 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TESTS_H
# define MINISHELL_TESTS_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
# include "mock.h"
# include "minishell.h"

/**
 * @file minishell_tests.h
 * @brief Header file for minishell tests.
 *
 * This file contains definitions and macros used for testing the
 * minishell project.
 */

/**
 * @def COLOR_BLACK
 * @brief ANSI escape code for black text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to black in the terminal.
 */
# define COLOR_BLACK "30m"
/**
 * @def COLOR_RED
 * @brief ANSI escape code for red text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to red in the terminal.
 */
# define COLOR_RED "31m"
/**
 * @def COLOR_GREEN
 * @brief ANSI escape code for green text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to green in the terminal.
 */
# define COLOR_GREEN "32m"
/**
 * @def COLOR_YELLOW
 * @brief ANSI escape code for yellow text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to yellow in the terminal.
 */
# define COLOR_YELLOW "33m"
/**
 * @def COLOR_BLUE
 * @brief ANSI escape code for blue text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to blue in the terminal.
 */
# define COLOR_BLUE "34m"
/**
 * @def COLOR_MAGENTA
 * @brief ANSI escape code for magenta text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to magenta in the terminal.
 */
# define COLOR_MAGENTA "35m"
/**
 * @def COLOR_CYAN
 * @brief ANSI escape code for cyan text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to cyan in the terminal.
 */
# define COLOR_CYAN "36m"
/**
 * @def COLOR_WHITE
 * @brief ANSI escape code for white text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to white in the terminal.
 */
# define COLOR_WHITE "37m"
/**
 * @def COLOR_LIGHT_BLACK
 * @brief ANSI escape code for light black text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light black in the terminal.
 */
# define COLOR_LIGHT_BLACK "90m"
/**
 * @def COLOR_LIGHT_RED
 * @brief ANSI escape code for light red text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light red in the terminal.
 */
# define COLOR_LIGHT_RED "91m"
/**
 * @def COLOR_LIGHT_GREEN
 * @brief ANSI escape code for light green text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light green in the terminal.
 */
# define COLOR_LIGHT_GREEN "92m"
/**
 * @def COLOR_LIGHT_YELLOW
 * @brief ANSI escape code for light yellow text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light yellow in the terminal.
 */
# define COLOR_LIGHT_YELLOW "93m"
/**
 * @def COLOR_LIGHT_BLUE
 * @brief ANSI escape code for light blue text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light blue in the terminal.
 */
# define COLOR_LIGHT_BLUE "94m"
/**
 * @def COLOR_LIGHT_MAGENTA
 * @brief ANSI escape code for light magenta text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light magenta in the terminal.
 */
# define COLOR_LIGHT_MAGENTA "95m"
/**
 * @def COLOR_LIGHT_CYAN
 * @brief ANSI escape code for light cyan text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light cyan in the terminal.
 */
# define COLOR_LIGHT_CYAN "96m"
/**
 * @def COLOR_LIGHT_WHITE
 * @brief ANSI escape code for light white text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to light white in the terminal.
 */
# define COLOR_LIGHT_WHITE "97m"
/**
 * @def STYLE_DEFAULT
 * @brief ANSI escape code for default text color.
 *
 * This macro defines the ANSI escape code for setting the text color
 * to default in the terminal.
 */
# define STYLE_DEFAULT "\033[0;"
/**
 * @def STYLE_BOLD
 * @brief ANSI escape code for bold text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to bold in the terminal.
 */
# define STYLE_BOLD "\033[1;"
/**
 * @def STYLE_DIM
 * @brief ANSI escape code for dim text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to dim in the terminal.
 */
# define STYLE_DIM "\033[2;"
/**
 * @def STYLE_ITALIC
 * @brief ANSI escape code for italic text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to italic in the terminal.
 */
# define STYLE_ITALIC "\033[3;"
/**
 * @def STYLE_UNDERLINE
 * @brief ANSI escape code for underline text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to underline in the terminal.
 */
# define STYLE_UNDERLINE "\033[4;"
/**
 * @def STYLE_BLINK
 * @brief ANSI escape code for blink text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to blink in the terminal.
 */
# define STYLE_BLINK "\033[5;"
/**
 * @def STYLE_REVERSE
 * @brief ANSI escape code for reverse text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to reverse in the terminal.
 */
# define STYLE_REVERSE "\033[7;"
/**
 * @def STYLE_HIDDEN
 * @brief ANSI escape code for hidden text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to hidden in the terminal.
 */
# define STYLE_HIDDEN "\033[8;"
/**
 * @def STYLE_STRIKETHROUGH
 * @brief ANSI escape code for strikethrough text style.
 *
 * This macro defines the ANSI escape code for setting the text style
 * to strikethrough in the terminal.
 */
# define STYLE_STRIKETHROUGH "\033[9;"
/**
 * @def FORMAT_RESET
 * @brief ANSI escape code to reset text formatting.
 *
 * This macro defines the ANSI escape code for resetting the text
 * formatting in the terminal.
 */
# define FORMAT_RESET "\033[0m"
/**
 * @def COLORIZE(text, style, color)
 * @brief Macro to apply ANSI color and style to text.
 *
 * This macro is used to apply a specific ANSI style and color to a
 * given text, and then reset the text formatting.
 *
 * @param text The text to be colorized.
 * @param style The ANSI style to be applied to the text (e.g., bold,
 * italic, underline).
 * @param color The ANSI color to be applied to the text.
 */
# define COLORIZE(text, style, color) style color text FORMAT_RESET

/**
 * @brief Entry point for the program's main functionality.
 *
 * This function serves as the main entry point for the program's
 * execution. It is responsible for initializing and running the core
 * logic of the program.
 *
 * @return An integer representing the exit status of the program.
 * Typically, a return value of 0 indicates successful execution,
 * while a non-zero value indicates an error or abnormal termination.
 */
int	program_main(void);

/**
 * @brief Tests the functionality of the get_token_end function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_token_end function, ensuring that it properly identifies
 * and returns the end position of a token in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_get_token_end(void);
/**
 * @brief Tests the functionality of the get_next_token function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_next_token function, ensuring that it properly identifies
 * and returns the next token in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_get_next_token(void);
/**
 * @struct s_extract_tokens_result
 * @brief Structure to hold the result of token extraction.
 *
 * This structure contains the return value and output of a token extraction operation.
 *
 * @var t_extract_tokens_result::return_value
 * Pointer to a list that holds the extracted tokens.
 *
 * @var t_extract_tokens_result::output
 * Pointer to a character array that holds the output of the token extraction.
 */
typedef struct s_extract_tokens_result
{
	t_list	*return_value;
	char	*output;
}	t_extract_tokens_result;
/**
 * @brief Tests the functionality of the extract_tokens function.
 *
 * This function is designed to test the behavior and correctness of
 * the extract_tokens function, ensuring that it properly identifies
 * and extracts tokens from a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_extract_tokens(void);
/**
 * @brief Tests the functionality of the is_input_redirection function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_input_redirection function, ensuring that it properly identifies
 * if a given token is an input redirection symbol.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_is_input_redirection(void);
/**
 * @brief Tests the functionality of the is_output_redirection function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_output_redirection function, ensuring that it properly identifies
 * if a given token is an output redirection symbol.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_is_output_redirection(void);
/**
 * @brief Tests the functionality of the is_redirection function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_redirection function, ensuring that it properly identifies
 * if a given token is a redirection symbol.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int	test_is_redirection(void);
/**
 * @brief Tests the functionality of the is_pipe function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_pipe function, ensuring that it properly identifies
 * if a given token is a pipe symbol.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_is_pipe(void);
/**
 * @struct s_is_valid_quotes_result
 * @brief Structure to hold the result of the is_valid_quotes function.
 *
 * This structure contains the return value and output of the is_valid_quotes function.
 *
 * @var t_is_valid_quotes_result::return_value
 * Integer that holds the return value of the is_valid_quotes function.
 *
 * @var t_is_valid_quotes_result::output
 * Pointer to a character array that holds the output of the is_valid_quotes function.
 */
typedef struct s_is_valid_quotes_result
{
	int		return_value;
	char	*output;
}	t_is_valid_quotes_result;
/**
 * @brief Tests the functionality of the is_valid_quotes function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_valid_quotes function, ensuring that it properly identifies
 * if a given token has valid quotes.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_is_valid_quotes(void);
/**
 * @struct s_is_token_list_valid_result
 * @brief Structure to hold the result of the is_token_list_valid function.
 *
 * This structure contains the return value and output of the is_token_list_valid function.
 *
 * @var t_is_token_list_valid_result::return_value
 * Integer that holds the return value of the is_token_list_valid function.
 *
 * @var t_is_token_list_valid_result::output
 * Pointer to a character array that holds the output of the is_token_list_valid function.
 */
typedef struct s_is_token_list_valid_result
{
	int		return_value;
	char	*output;
}	t_is_token_list_valid_result;
/**
 * @brief Tests the functionality of the is_token_list_valid function.
 *
 * This function is designed to test the behavior and correctness of
 * the is_token_list_valid function, ensuring that it properly identifies
 * if a given token list is valid.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_is_token_list_valid(void);
/**
 * @brief Tests the functionality of the free_redirection function.
 *
 * This function is designed to test the behavior and correctness of
 * the free_redirection function, ensuring that it properly frees
 * the memory allocated for a redirection structure.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_free_redirection(void);
/**
 * @brief Tests the functionality of the free_command function.
 *
 * This function is designed to test the behavior and correctness of
 * the free_command function, ensuring that it properly frees
 * the memory allocated for a command structure.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_free_command(void);
/**
 * @brief Tests the addition of a string to a list.
 *
 * This function is designed to test the functionality of adding a string
 * to a linked list. It ensures that the string is correctly added and
 * that the list maintains its integrity.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_lstadd_str(void);
/**
 * @brief Tests the addition of a redirection to a list.
 *
 * This function is designed to test the functionality of adding a redirection
 * to a linked list. It ensures that the redirection is correctly added and
 * that the list maintains its integrity.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_lstadd_redir(void);
/**
 * @brief Tests the allocation of a command.
 *
 * This function is designed to test the memory allocation process for a command
 * in the minishell project. It ensures that the command is properly allocated
 * and ready for use.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_alloc_command(void);
/**
 * @brief Tests the parsing of tokens in the minishell project.
 *
 * This function is designed to test the functionality of the token parsing
 * mechanism within the minishell project. It ensures that tokens are parsed
 * correctly and that the parsing logic adheres to the expected behavior.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_parse_tokens(void);
/**
 * @brief Tests the extraction of commands.
 *
 * This function is designed to test the functionality of extracting commands
 * from a given input. It ensures that the command extraction logic works
 * correctly and handles various edge cases.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_extract_commands(void);
/**
 * @brief Tests the freeing of environment variables.
 *
 * This function is designed to test the functionality of freeing environment
 * variables. It ensures that the memory allocated for environment variables
 * is properly freed.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_free_env_var(void);
/**
 * @brief Tests the addition of an environment variable to a list.
 *
 * This function is designed to test the functionality of adding an environment
 * variable to a linked list. It ensures that the environment variable is correctly
 * added and that the list maintains its integrity.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_lstadd_env_var(void);
/**
 * @brief Tests the functionality of the get_env_var function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_env_var function, ensuring that it properly retrieves
 * the value of a given environment variable.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_get_env_var(void);
/**
 * @brief Tests the functionality of the lstset_env_var function.
 *
 * This function is designed to test the behavior and correctness of
 * the lstset_env_var function, ensuring that it properly sets
 * the value of a given environment variable in a linked list.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_lstset_env_var(void);
/**
 * @brief Tests the extraction of environment variables.
 *
 * This function is designed to test the functionality of extracting environment
 * variables from a given input. It ensures that the environment variable extraction
 * logic works correctly and handles various edge cases.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_extract_env_vars(void);
/**
 * @brief Tests the creation of an environment string.
 *
 * This function is designed to test the functionality of creating an environment
 * string from a given key-value pair. It ensures that the environment string is
 * correctly formatted and ready for use.
 *
 * @return int Returns 0 if the test passes, otherwise returns a non-zero value.
 */
int test_create_env_string(void);
/**
 * @brief Tests the functionality of the get_envp function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_envp function, ensuring that it properly retrieves
 * the environment variables as an array of strings.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_get_envp(void);
/**
 * @brief Tests the functionality of the get_var_end function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_var_end function, ensuring that it properly identifies
 * and returns the end position of a variable in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_get_var_end(void);
/**
 * @brief Tests the functionality of the get_next_var function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_next_var function, ensuring that it properly identifies
 * and returns the next variable in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_get_next_var(void);
/**
 * @brief Tests the functionality of the extract_vars function.
 *
 * This function is designed to test the behavior and correctness of
 * the extract_vars function, ensuring that it properly identifies
 * and extracts variables from a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_extract_vars(void);
/**
 * @brief Tests the functionality of the get_var_value function.
 *
 * This function is designed to test the behavior and correctness of
 * the get_var_value function, ensuring that it properly retrieves
 * the value of a given variable from the environment.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_get_var_value(void);
/**
 * @brief Tests the functionality of the concat_vars function.
 *
 * This function is designed to test the behavior and correctness of
 * the concat_vars function, ensuring that it properly concatenates
 * variables and returns the expected result.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_concat_vars(void);
/**
 * @brief Tests the functionality of the expand_var function.
 *
 * This function is designed to test the behavior and correctness of
 * the expand_var function, ensuring that it properly expands
 * variables in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_expand_var(void);
/**
 * @brief Tests the functionality of the expand_token function.
 *
 * This function is designed to test the behavior and correctness of
 * the expand_token function, ensuring that it properly expands
 * tokens in a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */
int test_expand_token(void);

#endif

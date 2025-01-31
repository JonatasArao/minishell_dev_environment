/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tests.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:57:40 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/31 11:37:59 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TESTS_H
# define MINISHELL_TESTS_H
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
 * @brief Tests the functionality of the extract_token function.
 *
 * This function is designed to test the behavior and correctness of
 * the extract_token function, ensuring that it properly identifies
 * and extracts tokens from a given input.
 *
 * @return int Returns 0 if the test passes, or a non-zero value if
 * the test fails.
 */

int	test_extract_token(void);

#endif

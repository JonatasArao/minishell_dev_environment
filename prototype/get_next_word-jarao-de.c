/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word-jarao-de.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:55:13 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/30 10:33:48 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char	*get_next_word(char const *s)
{
	char			*word;
	char			quote_char;
	unsigned int	start;
	size_t			end;

	quote_char = 0;
	start = 0;
	while (s[start] && ft_isspace(s[start]))
		start++;
	end = start;
	while (s[end] && (!ft_isspace(s[end]) || quote_char))
	{
		if ((s[end] == '\'' || s[end] == '"') && !quote_char)
			quote_char = s[end];
		else if (s[end] == quote_char)
			quote_char = 0;
		end++;
	}
	word = ft_substr(s, start, end - start);
	if (!word)
		return (NULL);
	return (word);
}

int	main(void)
{
	const char	*str;
	char		*word;

	str = " hello 'hello world' \"hello world\" '\"hello world\"' "
		"\"'hello world'\" hello\" \"world";
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		word = get_next_word(str);
		if (!word)
			break ;
		printf("Word: %s\n", word);
		str += strlen(word);
		free(word);
	}
	return (0);
}

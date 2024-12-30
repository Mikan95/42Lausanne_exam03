/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:57:50 by ameechan          #+#    #+#             */
/*   Updated: 2024/12/29 22:58:47 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name : permutations

// Expected files : *.c *.h
// Allowed functions : puts, malloc, calloc, realloc, free, write
// ---------------------------------------------------------------

// Write a program that will print all the permutations of a string given as argument.

// The solutions must be given in alphabetical order.

// We will not try your program with strings containing duplicates (eg: 'abccd')

// For example this should work:
// $> ./permutations a | cat -e
// a$
// $> ./permutations ab | cat -e
// ab$
// ba$
// $> ./permutations abc | cat -e
// abc$
// acb$
// bac$
// bca$
// cab$
// cba$


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Bubble sort a string in alphabetical order
 * @note As the exercise specifies it will not test duplicates, we can get away with
 * using a bubble sort without worrying too much about how slow it is
 */
char	*ft_sort(char *str)
{
	int		i = 0;
	char	temp;

	while (i < (ft_strlen(str) - 1))
	{
		if (str[i] > str[i + 1])
		{
			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

/**
 * @brief Recursively generates every possible permutation of a given string that has been sorted alphabetically before being called.
 * @param s the given string to permute
 * @param current The index of the 'current' position being 'locked in'.
 * The function progresses by recursively calling itself with current + 1 to explore all possibilities for the remaining characters.
 * @param end The index of the last character in the string (length of s - 1).
 * @note At the start of the recursion, the `current` position is 0, meaning no characters have been fixed yet.
 * Each level of recursion 'locks in' one character by swapping it with others in the remaining range.
 * As `current` increments with each recursive call, the scope of reordering shrinks.
 * When `current` equals `end`, all characters have been fixed in place, forming a complete and valid permutation.
 */
void	ft_permute(char *s, int current, int end)
{
	int		i = current;
	char	tmp;

	if (current == end) //valid permutation has been generated, thus print and return
	{
		puts(s);
		return;
	}
	while (i <= end)
	{
		tmp = s[current];
		s[current] = s[i];
		s[i] = tmp;
		ft_permute(s, current + 1, end);
		s[i] = s[current];
		s[current] = tmp;
		i++;
	}
}

int	main(int ac, char **av)
{
	char	*sorted_str = NULL;

	if (ac != 2)						//return 1 if more or less than 1 argument
		return (1);
	else if (ft_strlen(av[1]) <= 1)		//print string and return 0 if given string is 1 character long or less
	{
		puts(av[1]);
		return (0);
	}
	sorted_str = ft_sort(av[1]);
	ft_permute(sorted_str, 0, (ft_strlen(sorted_str) - 1));
	return (0);
}


/*
Visualization of Recursion
For "abc", the permutations are generated like this:

(abc)	Lock 'a' at pos `0`
			Lock 'b' at pos `1`
				Lock 'c' at pos `2`
					current == end → Print "abc"

	(acb)	Backtrack: Swap 'b' and 'c':
			Lock 'c' at pos `1`
				lock 'b' at pos `2`
					current == end → Print "acb"

(bac)	Backtrack to Lock 'b' at Pos `0`:
		Lock 'a' at pos `1`
			Lock 'c' at pos `2`
				current == end → Print "bac"

	(bca)	Backtrack: Swap 'a' and 'c':
			Lock 'c' at pos `1`
				Lock 'a' at pos `2`
					current == end → Print "bca"

(cab)	Backtrack to Lock 'c' at Pos `0`:
		Lock 'a' at pos `1`
			Lock 'b' at pos `2`
				current == end → Print "cab"

	(cba)	Backtrack: Swap 'a' and 'b':
			Lock 'b' at pos `1`
				Lock 'a' at pos `2`
					current == end → Print "cba"

*/

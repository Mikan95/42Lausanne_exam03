/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:19:56 by ameechan          #+#    #+#             */
/*   Updated: 2024/11/27 20:11:42 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// CAUTION: memmem() cannot be used anymore!
//allowed functions as of Nov 21 2024:
//printf, perror, calloc, malloc, realloc, strlen, read, free

/*
The program takes one argument `ndl` and starts by reading from stdin.
Whatever it reads from stdin will now be refered to as `hs`.

The program then must find and replace every occurence of `ndl` in `hs`
and replace it with how ever many strlen(ndl) `*` (stars)

It then must write the new string to stdout and return 0.

If an error occurs it must exit and write "Error: " followed
by an adequate error message in stderr and return 1.

Allowed functions:
printf, perror, calloc, malloc, realloc, strlen, read, free

Usage example:
$:echo "hello friend, hello foe" | ./filter "hello"
***** friend, ***** foe$
$:


*/


int	handle_error(char *errmsg)
{
	perror(errmsg);
	return(1);
}

int	strings_match(const char *str1, const char *str2, size_t len)
{
	size_t	i = 0;
	while (i < len)
	{
		if (str1[i] != str2[i]) //return false as soon as two characters don't match
			return (0);
		i++;
	}
	return (1);//	both strings match, return 1
}

char	*ft_replacestr(const char *buf, const char *ndl)
{
	size_t	buf_len = strlen(buf);
	size_t	ndl_len = strlen(ndl);
	size_t	i, j, k;
	char	*result;

	if (ndl_len == 0)
		return ("\x01");

	result = calloc(buf_len + 1,  sizeof(char));
	if (!result)
		handle_error("Error: Memory Allocation Failed\n");

	i = 0;
	j = 0;
	while (i < buf_len)
	{
		if (i <= (buf_len - ndl_len) && strings_match(&buf[i], ndl, ndl_len))
		{
			//found matching string, replace ndl_len `*` (stars)
			k = 0;
			while(k < ndl_len)
			{
				result[j++] = '*';
				k++;
			}
			//skip over replaced ndl
			i += ndl_len;
		}
		else
			//otherwise simply copy over the characters
			result[j++] = buf[i++];
	}
	return (result);
}

int	main(int ac, char **av)
{
	char	*result;
	char	*buf;
	const char	*ndl;
	size_t	buffer_size, total_read;
	ssize_t	bytes_read;

	if (ac > 2)//return error if more than two args
		return (handle_error("Error: Too many arguments\n"));

	if (av[1])//point `ndl` to the substring in the user's input
		ndl = av[1];
	else
		ndl = NULL;

	buffer_size = 1;
	total_read = 0;
	buf = malloc(buffer_size); //allocate memory for buf
	if (!buf)
		handle_error("Error: Memory Allocation Failed\n");

	//read in a loop appending to buf with each iterration until 0 (end of file)
	//add total_size to buffer each loop to ensure read doesn't overwrite data in buf
	//substract total_size from buffer size to ensure you don't read out of bounds
	while ((bytes_read = read(0, buf + total_read, buffer_size - total_read)) > 0)
	{
		total_read += bytes_read;//		keep track of total_size

//											dynamically allocate more memory if
		if (total_read >= buffer_size)//	total_size gets bigger than buffer_size
		{
			buffer_size *= 2;
			buf = realloc(buf, buffer_size);
			if (!buf)
				handle_error("Error: Memory Allocation Failed\n");
		}
	}
	//return an error if read returned -1
	if (bytes_read == -1)
		handle_error("Error: failed to read input\n");

	//If the user did not input a ndl (av[1])
	//print `buf` and exit program cleanly
	if (!ndl)
	{
		printf("%s\n", buf);
		free(buf);
		return (0);
	}

	//Null terminate string read from stdin
	buf[total_read] = '\0';

	//replace every occurence of `ndl` in `buf`
	result = ft_replacestr(buf, ndl);

	//return an error if result is NULL
	if (!result)
		handle_error("Error: Failed to write output\n");

	//print the result to stdout
	// printf("END\n");
	printf("%s\n", result);
	free(buf);
	free(result);

	return (0);
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use ./program <needle> < test1.txt


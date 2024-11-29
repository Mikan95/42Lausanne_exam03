/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:19:56 by ameechan          #+#    #+#             */
/*   Updated: 2024/11/29 01:10:13 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//CAUTION: memmem() cannot be used anymore!
//allowed functions as of Nov 21 2024:
//strlen, printf, perror, read, malloc, calloc, realloc, free

/*
Write a program that takes one and only one parameter s.

The program should take the standard output and replace
every instance of s inside it with a corresponding number of "*".
It should then print it to the standard output and return 0.

If the program encounters an error when executing malloc or read,
it should output "Error: " followed by the corresponding error code,
to the standard error output and return 1.

Your program is generally equivalent to the
filter.sh shell script we have provided.

If the program is run with no parameter,
an empty parameter, or multiple parameters,
it should return 1.

Usage:
$> echo testa | ./filter est | cat -e
t***a$

$> echo 1234512345 | ./filter 234 | cat -e
1***51***5$


*/


int	handle_error()
{
	perror("Error: ");
	exit (1);
}

int	strings_match(const char *buf, const char *ndl, size_t len)
{
	size_t	i = 0;

	while (i < len)
	{
		if (buf[i] != ndl[i]) //return false as soon as two characters don't match
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
	char	*res;

	res = calloc(buf_len,  sizeof(char));
	if (!res)
		handle_error();
	i = 0;
	j = 0;
	while (i < buf_len)//while not reached the end of buf
	{
		//if there is enough space in buf to replace ndl && strings match
		if (i <= (buf_len - ndl_len) && strings_match(&buf[i], ndl, ndl_len))
		{
			//found matching string, replace ndl_len `*` (stars)
			k = 0;
			while(k < ndl_len)
			{
				res[j++] = '*';
				k++;
			}
			//skip over replaced ndl
			i += ndl_len;
		}
		else
			//otherwise simply copy over the characters
			res[j++] = buf[i++];
	}
	return (res);
}

int	main(int ac, char **av)
{
	char		*res;
	char		*buf;
	const char	*ndl;
	size_t		buffer_size;
	size_t		total_read;
	ssize_t		bytes_read;

	//return 1 if no argument or empty argument
	if (av[1] && av[1][0] != '\0')
		ndl = av[1];
	else
		return (1);

	//initialize buffer_size, total_read and bytes_read
	buffer_size = 20;
	total_read = 0;
	bytes_read = 0;
	buf = malloc(buffer_size); //allocate memory for buf
	if (!buf)
		handle_error();

	//read in a loop appending to buf with each iterration until 0 (end of file)
	//add total_size to buffer each loop to ensure read doesn't overwrite data already stored in buf
	//substract total_size from buffer size to ensure you don't read out of bounds
	while ((bytes_read = read(STDIN_FILENO, buf + total_read, buffer_size - total_read)) > 0)
	{
		total_read += bytes_read;//		keep track of total_size

//											dynamically allocate more memory to buf
		if (total_read >= buffer_size)//	if total_size goes over max capacity
		{
			buffer_size *= 2;
			buf = realloc(buf, buffer_size);
			if (!buf)
				handle_error();
		}
	}
	//return an error if read returned -1
	if (bytes_read == -1)
		handle_error();

	//Null terminate string captured from stdin
	buf[total_read] = '\0';

	//replace every occurence of `ndl` in `buf`
	res = ft_replacestr(buf, ndl);

	//return an error if res is NULL
	if (!res)
		handle_error();

	//print the res to stdout
	printf("%s", res);

	return (0);
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use ./program <needle> < test1.txt


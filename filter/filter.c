/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:19:56 by ameechan          #+#    #+#             */
/*   Updated: 2024/11/19 16:31:43 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define _GNU_SOURCE
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// /**
//  * @brief Allocates memory big enough to copy contents of `str` to `res`.
//  * @return A pointer to the newly allocated memory.
//  */
// char	*copy_str(char *str)
// {
// 	char	*res;
// 	int		i = 0;

// 	if (!str)
// 		return (NULL);
// 	res = malloc(sizeof(char) * strlen(str) + 1);
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// /**
//  * @brief Prints `str` to stdout.
//  */
// void	put_stdout(char *str)
// {
// 	int	i = 0;

// 	while (str[i])
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

// /**
//  * @brief Counts first, then replaces all occurences of `ndl` in `hs`.
//  */
// void	str_replace(char **hs, int hs_len, char *ndl, int ndl_len)
// {
// 	int		ndl_count = 0; // Number of occurences of `ndl` in `hs`
// 	char	*ptr;	// Pointer to the first occurence of `ndl` in `hs`
// 	char	*start = *hs;	// Pointer to the start of `hs`
// 	int		i = 0;

// 	ptr = *hs;	// Set the pointer to the start of `hs`
// 	if (!memmem(*hs, hs_len, ndl, ndl_len))	// return; if `ndl` is not in `hs`
// 		return ;

// 	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// 	//&&&&&&&&&&&&&  COUNT OCCURENCES OF `ndl` IN `hs`  &&&&&&&&&&&&&&&&&&//
// 	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// 	// (ptr - start) gives the len between start and ptr
// 	// thus, by subtracting this from hs_len, we get the remaining length of the string.
// 	while (memmem(ptr, hs_len - (ptr - start), ndl, ndl_len))
// 	{
// 		ptr = memmem(ptr, hs_len - (ptr - start), ndl, ndl_len);	// Find the next occurence of `ndl` in `hs` and set `ptr` to it
// 		ptr += ndl_len;	// increment ptr by the length of `ndl` so we point after the found `ndl`
// 		ndl_count++;	// increment ndl_count
// 	}

// 	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// 	//&&&&&&&&&&&&&&&&&  REPLACE EVERY `ndl` in `hs`  &&&&&&&&&&&&&&&&&&&&//
// 	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// 	ptr = *hs;	// Reset the pointer to the start of `hs`
// 	while (ndl_count > 0 && (ptr = memmem(ptr, hs_len - (ptr - start), ndl, ndl_len)))	// while ndl_count > 0 and `ndl` is found in `hs`
// 	{
// 		ptr = memmem(ptr, strlen(ptr), ndl, ndl_len);	// Find the next occurence of `ndl` in `hs` and set `ptr` to it
// 		i = 0;
// 		while (i < ndl_len)	// Replace ndl_len characters with '*' in `hs`
// 		{
// 			ptr[i] = '*';
// 			i++;
// 		}
// 		ndl_count--;	// decrement ndl_count
// 	}
// }

// /**
//  * @brief `read()` sometimes fails to read big chunks of data in one go,
//  * so we read in a loop until, memorising the total bytes read and appending all
//  * non-read data to the buffer, until we read all the data from stdin. If `read()` returns 0
//  *  */
// int	main(int ac, char **av)
// {
// 	char	*buf = calloc(10000, sizeof(char));	// Allocate 10k bytes buffer to read from stdin
// 	char	*hs;	// Heap string
// 	char	*ndl;	// Needle
// 	int bytes_read;	// Bytes read from stdin
// 	int total_bytes_read = 0;	// Total bytes read from stdin

// 	(void)ac;
// 	while ((bytes_read = read(0, buf + total_bytes_read, 10000 - total_bytes_read)) > 0)
// 	{
// 		total_bytes_read += bytes_read;
// 	}

// 	if (bytes_read < 0)	// security check in case read() fails
// 	{
// 		fprintf(stderr, "Error: Can't read file\n");
// 		free(buf);
// 		return (1);
// 	}
// 	buf[total_bytes_read] = '\0'; // Null-terminate the buffer
// 	if (!(*buf))
// 		return (0);

// 	hs = copy_str(buf);	// Copy the buffer to the heap string
// 	free(buf);	// Free the buffer
// 	if (!hs)	// security check in case memory allocation fails
// 	{
// 		fprintf(stderr, "Error: Memory allocation\n");
// 		return (1);
// 	}

// 	ndl = copy_str(av[1]);	// Copy the needle from argv
// 	if (*ndl)	// only run this if the needle is not empty
// 		str_replace(&hs, strlen(hs), ndl, strlen(ndl));	// Replace all occurences of needle in the heap string
// 	put_stdout(hs);	// Print the heap string to stdout
// 	return (0);
// }

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// CAUTION: memmem() cannot be used anymore!
//allowed functions as of Nov 21 2024: 
//printf, perror, calloc, malloc, realloc, strlen, read, free 

/**
 * @brief Allocates and copies the contents of `str`.
 */
char *copy_str(char *str)
{
    if (!str)
        return NULL;
    char *res = malloc(strlen(str) + 1);
    if (!res)
        return NULL;
    for (int i = 0; str[i]; i++)
        res[i] = str[i];
    res[strlen(str)] = '\0';
    return res;
}

/**
 * @brief Prints `str` followed by a newline to stdout.
 */
void put_stdout(char *str)
{
    for (int i = 0; str[i]; i++)
        write(1, &str[i], 1);
    write(1, "\n", 1);
}

/**
 * @brief Replaces all occurrences of `ndl` in `hs` with '*'.
 */
void str_replace(char **hs, int hs_len, char *ndl, int ndl_len)
{
    char *ptr = *hs;

    while ((ptr = memmem(ptr, hs_len - (ptr - *hs), ndl, ndl_len)))
    {
        for (int i = 0; i < ndl_len; i++)
            ptr[i] = '*';
        ptr += ndl_len;
    }
}

/**
 * @brief Reads input from stdin into a dynamically allocated buffer.
 */
char *read_input(void)
{
    char *buf = calloc(10000, sizeof(char));
    if (!buf)
        return NULL;
    int bytes_read, total_bytes = 0;

    while ((bytes_read = read(0, buf + total_bytes, 10000 - total_bytes)) > 0)
        total_bytes += bytes_read;

    if (bytes_read < 0)
    {
        free(buf);
        return NULL;
    }
    buf[total_bytes] = '\0';
    return buf;
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s <needle>\n", av[0]);
        return 1;
    }

    char *buf = read_input();
    if (!buf)
    {
        fprintf(stderr, "Error: Can't read input\n");
        return 1;
    }

    char *hs = copy_str(buf);
    free(buf);
    if (!hs)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    char *ndl = copy_str(av[1]);
    if (*ndl)
        str_replace(&hs, strlen(hs), ndl, strlen(ndl));

    put_stdout(hs);

    free(hs);
    free(ndl);
    return 0;
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use ./program <needle> < test1.txt


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:19:56 by ameechan          #+#    #+#             */
/*   Updated: 2024/11/15 00:45:54 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*copy_str(char *str)
{
	char	*res;
	int		i = 0;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	put_stdout(char *str)
{
	int	i = 0;

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	str_replace(char **hs, int hs_len, char *ndl, int ndl_len)
{
	int		ndl_count = 0;
	char	*ptr;
	char	*start = *hs;
	int		i = 0;

	ptr = *hs;
	if (!memmem(*hs, hs_len, ndl, ndl_len))
		return ;
	while (memmem(ptr, hs_len - (ptr - start), ndl, ndl_len))
	{
		ptr = memmem(ptr, hs_len - (ptr - start), ndl, ndl_len);
		ptr += ndl_len;
		ndl_count++;
	}
	ptr = *hs;
	while (ndl_count > 0 && (ptr = memmem(ptr, hs_len - (ptr - start), ndl, ndl_len)))
	{
		ptr = memmem(ptr, strlen(ptr), ndl, ndl_len);
		i = 0;
		while (i < ndl_len)
		{
			ptr[i] = '*';
			i++;
		}
		ndl_count--;
	}
}

int	main(int ac, char **av)
{
	char	*buf = calloc(10000, sizeof(char));
	char	*hs;
	char	*ndl;
	int bytes_read;
	int total_bytes_read = 0;

	(void)ac;
	while ((bytes_read = read(0, buf + total_bytes_read, 10000 - total_bytes_read)) > 0)
	{
		total_bytes_read += bytes_read;
	}
	if (bytes_read < 0)
	{
		fprintf(stderr, "Error: Can't read file\n");
		free(buf);
		return (1);
	}
	buf[total_bytes_read] = '\0'; // Null-terminate the buffer
	if (!(*buf))
		return (0);
	hs = copy_str(buf);
	free(buf);
	if (!hs)
	{
		fprintf(stderr, "Error: Memory allocation\n");
		return (1);
	}
	ndl = copy_str(av[1]);
	if (*ndl)
		str_replace(&hs, strlen(hs), ndl, strlen(ndl));
	put_stdout(hs);
	return (0);
}

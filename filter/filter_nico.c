#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	handle_error(const char *errmsg)
{
	// Use perror for error messages and exit
	perror(errmsg);
	exit(1);
}

int	strings_match(const char *str1, const char *str2, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

char	*ft_replacestr(const char *buf, const char *ndl)
{
	size_t	buf_len = strlen(buf);
	size_t	ndl_len = strlen(ndl);
	size_t	i = 0, j = 0, k;
	char	*result;

	if (ndl_len == 0)
	{
		// Simulate error using perror
		//errno = 22; // EINVAL: Invalid argument
		handle_error("Error: Pattern string cannot be empty");
	}

	// Allocate memory for the worst-case scenario: everything replaced by '*'
	result = calloc(buf_len * (ndl_len ? ndl_len : 1) + 1, sizeof(char));
	if (!result)
		handle_error("Error: Memory Allocation Failed");

	while (i < buf_len)
	{
		if (i <= buf_len - ndl_len && strings_match(&buf[i], ndl, ndl_len))
		{
			for (k = 0; k < ndl_len; k++)
				result[j++] = '*';
			i += ndl_len;
		}
		else
		{
			result[j++] = buf[i++];
		}
	}
	return result;
}

int	main(int ac, char **av)
{
	char	*result;
	char	*buf;
	const char	*ndl;
	size_t	buffer_size = 1024;
	size_t	total_read = 0;
	ssize_t	bytes_read;

	if (ac > 2)
	{
		//errno = 22; // EINVAL: Invalid argument
		handle_error("Error: Too many arguments");
	}

	ndl = (ac == 2) ? av[1] : NULL;

	buf = malloc(buffer_size);
	if (!buf)
		handle_error("Error: Memory Allocation Failed");

	while ((bytes_read = read(0, buf + total_read, buffer_size - total_read - 1)) > 0)// -1 to leave space for null terminator
	{
		total_read += bytes_read;
		if (total_read >= buffer_size - 1)
		{
			buffer_size *= 2;
			buf = realloc(buf, buffer_size);
			if (!buf)
				handle_error("Error: Memory Allocation Failed");
		}
	}
	if (bytes_read == -1)
		handle_error("Error: Failed to read input");

	buf[total_read] = '\0';

	if (!ndl)
	{
		printf("%s", buf);
		free(buf);
		return 0;
	}

	result = ft_replacestr(buf, ndl);
	if (!result)
		handle_error("Error: Failed to replace strings");

	printf("%s", result);
	free(buf);
	free(result);

	return 0;
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program <needle> < test1.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	handle_error(void)
{
	perror("Error: ");
	exit (1);
}

char	*replace_str(const char *buf, const char *ndl)
{
	char	*result;
	size_t	buf_len, ndl_len;
	size_t	i, j, k;

}

int		main(int ac, char **av)
{
	char		*res;
	char		*buf;
	const char	*ndl;
	size_t		buf_size = 20;
	size_t		total_read = 0;
	ssize_t		bytes_read;

	if (ac > 2)
		handle_error();
	if (av[1])
		ndl = av[1];
	else
		ndl = NULL;
	buf = malloc(buffer_size)
	if (!buf)
		handle_error();
	while((bytes_read = read(STDIN_FILENO, buf + total_read, buf_size - total_read)) > 0)
	{
		total_read += bytes_read;
		if (total_read > buf_size)
		{
			buf_size *= 2;
			realloc(buf, buf_size);
			if (!buf)
				handle_error();
		}
	}
}

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void swap(char *a, char *b)
{
	char temp = *a;
	*a = *b; 
	*b = temp;
}

int string_length(char *str) {
	int len = 0; 
	while (str[len]) 
		len++; 
	return len;
}

char *string_duplicate(char *str)
{
	int len = string_length(str);
	char *copy = malloc(len + 1);
	for (int i = 0; i <= len; i++) 
		copy[i] = str[i];
	return copy;
}

int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2) 
	{
		if (*str1 != *str2) 
			return *str1 - *str2;
		str1++; str2++;
	}
	return *str1 - *str2;
}

void sort_results(char **results, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (string_compare(results[i], results[j]) > 0) 
			{
				char *temp = results[i];
				results[i] = results[j];
				results[j] = temp;
			}
	}
}

void permute(char *str, int l, int r, char **results, int *index)
{
	if (l == r) 
	{
		results[(*index)++] = string_duplicate(str); 
		return;
		}
	for (int i = l; i <= r; i++)
	{
		bool seen = false;
		for (int j = l; j < i; j++) 
			if (str[j] == str[i]) 
			{ 
				seen = true;
				break; 
			}
		if (seen) 
			continue;
		swap(&str[l], &str[i]);
		permute(str, l + 1, r, results, index);
		swap(&str[l], &str[i]);
	}
}

int main(int argc, char **argv) {
	if (argc != 2) 
	{
		write(1, "Usage: ./permutations <string>\n", 33);
		return 1;
	}

	char *input = argv[1];
	int len = string_length(input), fact = 1;
	for (int i = 2; i <= len; i++) 
		fact *= i;

	char **results = malloc(fact * sizeof(char *));
	if (!results) 
	{
		write(1, "Memory allocation failed\n", 25);
		return 1;
	}

	int index = 0;
	permute(input, 0, len - 1, results, &index);
	sort_results(results, index);

	for (int i = 0; i < index; i++) {
		write(1, results[i], string_length(results[i]));
		write(1, "\n", 1);
		free(results[i]);
	}

	free(results);
	return 0;
}


// to compile use gcc -Wall -Wextra -Werror -o program permutations.c
// to run use ./program abc
// leaks --atExit -- ./program abc

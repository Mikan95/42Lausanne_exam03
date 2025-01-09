#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct
{
	float x, y;
} City;

float distance(City a, City b)
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float calculate_path(City *cities, int *order, int n)
{
	float total = 0;
	for (int i = 0; i < n; i++)
		total += distance(cities[order[i]], cities[order[(i + 1) % n]]);
	return total;
}

void permute(int *order, int start, int n, float *min_path, City *cities)
{
	if (start == n)
	{
		float path_len = calculate_path(cities, order, n);
		if (path_len < *min_path)
			*min_path = path_len;
		return;
	}
	for (int i = start; i < n; i++)
	{
		int temp = order[start];
		order[start] = order[i];
		order[i] = temp;
		permute(order, start + 1, n, &*min_path, cities);
		temp = order[start];
		order[start] = order[i];
		order[i] = temp;
	}
}

int main()
{
	FILE *input = stdin; // Read input from standard input
	City cities[11];
	int n = 0;
	while (n < 11 && !feof(input))
	{
		if (fscanf(input, "%f, %f\n", &cities[n].x, &cities[n].y) != 2)
		{
			fprintf(stderr, "Error: Invalid input\n");
			return 1;
		}
		n++;
	}
	if (n < 2)
	{
		fprintf(stderr, "Error: Not enough cities\n");
		return 1;
	}
	int order[11];
	for (int i = 0; i < n; i++)
		order[i] = i;

	float min_path = 1e9;
	permute(order, 0, n, &min_path, cities);
	fprintf(stdout, "%.2f\n", min_path); //changed from write_result if needed
	//write_result(min_path); // Output the result with write_result
	return 0;
}
//to execute: gcc -Wall -Wextra -Werror tsp.c -lm -o tsp
// cat test_tsp/filename.txt | ./tsp


// void write_result(float result)
// {
//     int int_part = (int)result;
//     int frac_part = (int)((result - int_part) * 100);

//     char buffer[32];
//     int len = 0;

//     // Convert integer part
//     if (int_part == 0)
//         buffer[len++] = '0';
//     else
//     {
//         char temp[16];
//         int temp_len = 0;
//         while (int_part > 0)
//         {
//             temp[temp_len++] = (int_part % 10) + '0';
//             int_part /= 10;
//         }
//         for (int i = temp_len - 1; i >= 0; i--)
//             buffer[len++] = temp[i];
//     }

//     // Add decimal point and fractional part
//     buffer[len++] = '.';
//     buffer[len++] = (frac_part / 10) + '0';
//     buffer[len++] = (frac_part % 10) + '0';
//     buffer[len++] = '\n';

//     write(STDOUT_FILENO, buffer, len);
// }




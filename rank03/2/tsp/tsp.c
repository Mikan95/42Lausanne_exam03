#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
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

        permute(order, start + 1, n, min_path, cities);

        temp = order[start];
        order[start] = order[i];
        order[i] = temp;
    }
}

int main()
{
    City cities[11];
    int n = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1 && n < 11)
    {
        if (sscanf(line, "%f, %f", &cities[n].x, &cities[n].y) != 2)
        {
            fprintf(stderr, "Error: Invalid input\n");
            free(line);
            return 1;
        }
        n++;
    }
    free(line);
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

    printf("%.2f\n", min_path);
    return 0;
}

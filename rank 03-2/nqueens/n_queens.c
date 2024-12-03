#include <stdlib.h>
#include <unistd.h>

void print_solution(int *board, int n)
{
    for (int i = 0; i < n; i++)
    {
        char c = board[i] + '0';
        write(1, &c, 1);
        if (i < n - 1)
            write(1, " ", 1);
    }
    write(1, "\n", 1);
}

int is_safe(int *board, int col, int row)
{
    for (int i = 0; i < col; i++)
        if (board[i] == row || col - i == (row > board[i] ? row - board[i] : board[i] - row))
            return 0;
    return 1;
}

void solve(int *board, int col, int n)
{
    if (col == n)
        print_solution(board, n);
    for (int row = 0; row < n; row++)
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, col + 1, n);
        }
}

int main(int argc, char **argv)
{
    int n = argc == 2 ? atoi(argv[1]) : 0;
    if (n <= 0)
        return 1;
    int *board = malloc(n * sizeof(int));
    if (!board)
        return 1;
    solve(board, 0, n);
    free(board);
    return 0;
}

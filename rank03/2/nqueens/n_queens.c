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
	write(1, "\n", 1); // Print solution in required format
	//draw_board(board, n); // Draw the board
}

int is_safe(int *board, int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
			return 0;
		if ((col - i) == (row > board[i] ? row - board[i] : board[i] - row))
			return 0;
	}
	return 1;
}

void solve(int *board, int col, int n)
{
	if (col == n)
	{
		print_solution(board, n);
		return;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;         // Place queen
			solve(board, col + 1, n); // Recur to place the next queen
		}
	}
}

int main(int argc, char **argv)
{
	int n = argc == 2 ? atoi(argv[1]) : 0;
	if (n <= 0)
		return 1;
	int *board = malloc(n * sizeof(int)); // Allocate memory for the board
	if (!board)
		return 1;
	solve(board, 0, n); // Start solving from the first column
	free(board);        // Free allocated memory
	return 0;
}

// Function to draw the board
// void draw_board(int *board, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             if (board[i] == j)
//                 write(1, "X ", 2); // Queen position
//             else
//                 write(1, "0 ", 2); // Empty space
//         }
//         write(1, "\n", 1); // Newline after each row
//     }
//     write(1, "\n", 1); // Extra newline after the board
// }

#include <unistd.h>

void print_solution(char *str)
{
    for (int i = 0; str[i]; i++)
        write(1, str[i] ? (str[i] == '(' || str[i] == ')' ? &str[i] : " ") : "", 1);
    write(1, "\n", 1);
}

void solve(char *str, int pos, int open, char *temp, int temp_pos)
{
    if (!str[pos])
    {
        if (open == 0)
        {
            temp[temp_pos] = '\0';
            print_solution(temp);
        }
        return;
    }
    solve(str, pos + 1, open, temp, temp_pos); // Skip
    if (str[pos] == '(')
    {
        temp[temp_pos] = '(';
        solve(str, pos + 1, open + 1, temp, temp_pos + 1);
    }
    else if (str[pos] == ')' && open > 0)
    {
        temp[temp_pos] = ')';
        solve(str, pos + 1, open - 1, temp, temp_pos + 1);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = 0;
    while (argv[1][n])
        n++;
    char temp[n + 1];
    solve(argv[1], 0, 0, temp, 0);
    return 0;
}

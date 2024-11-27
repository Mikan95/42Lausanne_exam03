#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>


int main()
{
    int num;
    char str[100];
    char ch;

    // Test integer parsing
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered the integer: %d\n", num);

    // Test string parsing
    printf("Enter a string: ");
    scanf("%s", str);
    printf("You entered the string: %s\n", str);

    // Test character parsing
    printf("Enter a character: ");
    scanf("%c", &ch);
    printf("You entered the character: %c\n", ch);

    return 0;
}

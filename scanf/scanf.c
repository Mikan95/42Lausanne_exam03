/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:33:29 by nryser            #+#    #+#             */
/*   Updated: 2024/11/19 20:16:44 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int my_parse_int(FILE *input, va_list args);
int my_parse_string(FILE *input, va_list args);
int my_parse_char(FILE *input, va_list args);
void skip_white_space(FILE *input);

int my_scanf(char *format, ...)
{
    va_list args;
    int result = 0;
    va_start(args, format);

    while (*format) {
        if (isspace(*format)) {
            skip_white_space(stdin);
            format++;
        }
        else if (*format == 'd') {
            result += my_parse_int(stdin, args);
            format++;
        }
        else if (*format == 's') {
            result += my_parse_string(stdin, args);
            format++;
        }
        else if (*format == 'c') {
            result += my_parse_char(stdin, args);
            format++;
        }
        else {
            // If the format is invalid or not supported, move to next character
            format++;
        }
    }

    va_end(args);
    return result;
}

void skip_white_space(FILE *input)
{
    char ch;

    // Read the first character to check if it's whitespace
    ch = fgetc(input);
	ungetc(ch, input);

    // Keep skipping white space (spaces, tabs, newlines, etc.)
    while (isspace(ch)) {
        ch = fgetc(input);  // Read the next character
    }

    //After the loop, ch holds the first non-whitespace character, or EOF
    // if (ch != EOF) {
    //     ungetc(ch, input);  // Push back the last read character if it's not EOF
    // }
}


int my_parse_int(FILE *input, va_list args)
{
    int num = 0;
    int sign = 1;
    char ch;

    // Skip any leading white space
    skip_white_space(input);

    // Read the first character
    ch = fgetc(input);


    // Handle optional sign
    if (ch == '-') {
        sign = -1;
        ch = fgetc(input);  // Read the next character
    }
    else if (ch == '+') {
        ch = fgetc(input);  // Read the next character
    }

    // Ensure the first character is a digit
    if (!isdigit(ch)) {
        ungetc(ch, input);  // Push back the invalid character
        return 0;  // If the first non-whitespace character is not a digit, return 0
    }

    // Parse the integer value
    while (isdigit(ch)) {
        num = num * 10 + (ch - '0');
        ch = fgetc(input);  // Read the next character
    }

    // If an integer was read, store it in the corresponding argument
    num *= sign; // Apply sign
    *(va_arg(args, int *)) = num;
    return 1; // Successfully parsed one integer
}

int my_parse_string(FILE *input, va_list args)
{
    char *str = va_arg(args, char *);
    char ch;

    // Skip any leading white space
    skip_white_space(input);

    // Read the first character
    ch = fgetc(input);

    // Ensure there is a valid character to read
    if (ch == EOF) {
        return 0; // No valid string
    }

    // Push back the first character for proper string parsing
    ungetc(ch, input);  // Only ungetc if there is valid character to process

    // Read non-whitespace characters into the string
    while (1) {
        ch = fgetc(input);  // Read a character

        // Break if we hit EOF or whitespace
        if (ch == EOF || isspace(ch)) {
            break;
        }

        *str = ch;  // Store the character
        str++;  // Move to next position in the string
    }

    *str = '\0'; // Null-terminate the string

    return 1; // Successfully parsed one string
}

int my_parse_char(FILE *input, va_list args)
{
    char *ch = va_arg(args, char *);

    // Skip any leading white space
    skip_white_space(input);

    *ch = fgetc(input);  // Directly read one character

    // Ensure that a valid character was read
    if (*ch != EOF) {
        return 1; // Successfully parsed one character
    }

    return 0; // Failed to parse
}

int main()
{
    int num;
    char str[100];
    char ch;

    // Test the 'd' specifier for integers
    printf("Enter an integer: ");
    my_scanf("%d", &num);
    printf("You entered the integer: %d\n", num);

    // Test the 's' specifier for strings
    printf("Enter a string: ");
    my_scanf("%s", str);
    printf("You entered the string: %s\n", str);

    // Test the 'c' specifier for a single character
    printf("Enter a character: ");
    my_scanf("%c", &ch);
    printf("You entered the character: %c\n", ch);

    return 0;

}


//compile: gcc -Wall -Wextra -Werror -o scanf_test scanf.c
//run: ./scanf_test

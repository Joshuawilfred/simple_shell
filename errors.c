#include "shell.h"

/**
 * error_msg - prints an error message to stderr
 * @vars: pointer to struct of variables
 * @msg: error message to print
 *
 * This function takes a pointer to a struct of variables and an error message,
 * and prints the message to standard error along with some additional
 * information about the program name and line number.
 */
void error_msg(vars_t *vars, char *msg)
{
    char *count_str; // string representation of vars->count

    // print program name and line number to standard error
    _puts2(vars->argv[0]);
    _puts2(": ");
    count_str = _uitoa(vars->count);
    _puts2(count_str);
    free(count_str);
    _puts2(": ");
    _puts2(vars->av[0]);

    // print the error message (if provided) or the system error message
    if (msg)
        _puts2(msg);
    else
        perror("");
}

/**
 * _puts2 - prints a string to standard error
 * @str: string to print
 *
 * This function takes a string and prints it to standard error using the
 * write system call. It also checks if the entire string was printed
 * successfully, and if not, it prints a fatal error message and exits the program.
 */
void _puts2(char *str)
{
    ssize_t num, len;

    // get the length of the string and print it to standard error
    num = _strlen(str);
    len = write(STDERR_FILENO, str, num);

    // check if the entire string was printed successfully
    if (len != num)
    {
        perror("Fatal Error");
        exit(1);
    }
}

/**
 * _uitoa - converts an unsigned integer to a string
 * @count: unsigned integer to convert
 *
 * This function takes an unsigned integer and converts it to a string
 * representation, which is returned as a pointer to a newly allocated string.
 * If memory allocation fails, it prints a fatal error message and exits the program.
 */
char *_uitoa(unsigned int count)
{
    char *numstr; // string representation of count
    unsigned int tmp, digits;

    // count the number of digits in the unsigned integer
    tmp = count;
    for (digits = 0; tmp != 0; digits++)
        tmp /= 10;

    // allocate memory for the string representation of the unsigned integer
    numstr = malloc(sizeof(char) * (digits + 1));
    if (numstr == NULL)
    {
        perror("Fatal Error");
        exit(127);
    }

    // convert the unsigned integer to a string and store it in the allocated memory
    numstr[digits] = '\0';
    for (--digits; count; --digits)
    {
        numstr[digits] = (count % 10) + '0';
        count /= 10;
    }

    return (numstr);
}

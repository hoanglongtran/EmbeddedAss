#include "stdio.h"
char getc(void) // Gets a single character from the standard i/o
{
    return uart_getc(); // Function definition is later defined
}
void putc(char c) // Places a single character to the standard i/o
{
    uart_putc(c); // Function definition is later defined
}

void gets(char* buf, int buflen) // Gets a C string from the standard i/o
{
    int i;
    char c;
    for (i = 0; (c = getc()) != '\r' && (buflen > 1); i++, buflen--)
    {   // How do the parameters in the for loop work?
        // What is '\r' and how is it different from '\n'?
        putc(c);
        buf[i] = c;
    }
    putc('\n');
    if (c == '\n')    // Why does this condition exist?
        buf[i] = '\0';
    else
        buf[buflen-1] = '\0';
}
    
void puts(const char* buf) // Places a C string to the standard i/o
{
    char str[1000];
    int i;
    for(i = 0; i < 1000; i++)
    {
        str[i] = buf[i];
    }
    for (int i = 0; str[i] != '\0'; i++)
    putc(str[i]);
}


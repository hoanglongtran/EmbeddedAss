#include "uart.h"

char getc(void); // Gets a single character from the standard i/o

void putc(char c); // Places a single character to the standard i/o

void gets(char* buf, int buflen); // Gets a C string from the standard i/o
    
void puts(const char* buf); // Places a C string to the standard i/o
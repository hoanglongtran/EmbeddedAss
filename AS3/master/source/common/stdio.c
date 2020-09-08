#include "stdio.h"
char getc(void) {
	return uart_getc();
}

void putc(char c){
	uart_putc(c);
}

void gets(char* buf, int buflen){
	int i; unsigned char c;
	for (i = 0; (c = getc()) != '\r' && (buflen > 1); i++, buflen--)
	{   // How do the parameters in the for loop work?
		// What is '\r' and how is it different from '\n'?
		putc(c);
		buf[i] = c;
	}
	putc('\n');
	if (c == '\r')    // Why does this condition exist?
		buf[i] = '\0';
	else
		buf[buflen-1] = '\0';
}

void puts(const char* buf) {
	for (int i = 0; buf[i] != '\0'; i++)
    	putc(buf[i]);
}
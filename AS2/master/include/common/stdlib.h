#include "stddef.h"
#include "stdint.h"
#ifndef STDLIB_H
#define STDLIB_H
char* itoa(int i);     // Converts an integer value to C string

int atoi(char* cstring); // Converts a C string to an integer

char* dectohex(int i);

void bzero(void* dest, int bytes);

void delay(uint32_t count);
#endif
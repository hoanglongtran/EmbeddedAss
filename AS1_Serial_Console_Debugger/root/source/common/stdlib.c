#include "stdlib.h"
char* itoa(int i)     // Converts an integer value to C string
{
    char cstring[12];
    int isneg;
    int j = 0;
    if (i == 0)
    {
        cstring[0] = '0';
        cstring[1] = '\0';
        return cstring;
    }
    if (i < 0)
    {
        isneg = 1;  
        i = -i;
    }
    while (i != 0)
    {
        cstring[j++] = '0' + (i % 10); // '0' + any number will convert it to an char 
                                   
        i /= 10;
    }
    if (isneg)
    {
        cstring[j++] = '-';
        cstring[j] = '\0';
        j--;    // Move the j variable back to start reversing the number, with '\0' at the
                // end of the array 
        
        i = 0;
    }
    while (i < j)    
    {
        isneg = cstring[i]; // Put index i's element into a temp variable
        cstring[i] = cstring[j];    // Swap with index j's element
        cstring[j] = isneg; // Put index i's element inside temp variable into index j's spot
        j--;
        i++;
    }
    return cstring;
}

int atoi(char* cstring) // Converts a C string to an integer
{
    int res = 0;
    for (int i = 0; cstring[i] != '\r'; i++)
    res = res * 10 + cstring[i] - '0';    // Any char number - '0' (character 0) will convert it into an int
                                        
    return res;

}

/*char* dectohex(int i)
{
    while (i != 0)    // Where does i come from?
    {
        if ((i % 16) < 10)  // Why does this condition exist?
                            // Hint: Look at the ASCII table
                            // How should hexvalue be declared?
            hexvalue[j++] = 48 + (i % 16);
        else                  // What is the purpose of decimal values 48 and 55?
            hexvalue[j++] = 55 + (i % 16);
        i /= 16;
    }
}*/

void bzero(void* dest, int bytes)   // Zeros out a segment of 'bytes' in memory
{
    char* d = dest;
    while (bytes--)
    *d++ = 0; 
}

void delay(uint32_t count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
              : "=r"(count) : [count] "0" (count) : "cc");
}


#include "stdlib.h"

char* itoa(int i) {
    static char cstring[12]; // the function returns its memory address, therefore it must be a static variable
    int isneg = 0, j = 0;// cstring is char array with 12 elements
    if (i == 0) {
		cstring[0] = '0';
		cstring[1] = '\0';
		return cstring;
	}
    if (i < 0)
    {
        isneg = 1;    // isneg can be declared as an integer variable
        i = -i;
    }
    while (i != 0)
    {
        cstring[j++] = '0' + (i % 10); // What is '0' for? 
                                    	// Hint: Have a look at the ASCII table
        i /= 10;
    }
	if (isneg)
    cstring[j++] = '-';
	cstring[j] = '\0';
	j--;    // Why is j decremented here? - current j denote the index of NULL character, decrement it to reverse the string later
        // Hint: Look at the purpose of the next step
    i = 0;
	while (i < j)    // What does this while loop do? -reverse the string to exact orders
	{
		isneg = cstring[i];
		cstring[i] = cstring[j];
		cstring[j] = isneg;
		j--;
		i++;
	}
	return cstring;
};	

int atoi(char* cstring) {
	int res = 0;
	for (int i = 0; cstring[i] != '0'; i++)
    res = res * 10 + cstring[i] - '0';    // What is this line of code doing? - convert the ascii value to integer value
                                          // In particular, '0'?
	return res;    // res will need to be declared in this function?
};

char* dectohex(int i) {
	static char hexvalue[12];
	int j = 0;
	while (i != 0)    // Where does i come from?
	{
		if ((i % 16) < 10)    // Why does this condition exist?
							// Hint: Look at the ASCII table
							// How should hexvalue be declared?
			hexvalue[j++] = (i % 16) + '0';
		else                  // What is the purpose of '0'?
			hexvalue[j++] = (i % 16) + 'A' - 10;
		i /= 16;
	}
	hexvalue[j++] = 'x';
	hexvalue[j++] = '0';
	hexvalue[j--] = '\0';
	i = 0;
	int temp = 0;
	while (i < j)    // What does this while loop do?
	{
		temp = hexvalue[i];
		hexvalue[i] = hexvalue[j];
		hexvalue[j] = temp;
		j--;
		i++;
	} 
	return hexvalue;
};

void bzero(void* dest, int bytes) {
	char* d = dest;
	while (bytes--)
		*d++ = 0; // What does this line of code do?
};

void delay(uint32_t count) {
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
              : "=r"(count) : [count] "0" (count) : "cc");
};


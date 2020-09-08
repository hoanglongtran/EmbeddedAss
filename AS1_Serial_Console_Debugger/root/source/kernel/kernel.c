#include "kernel.h"


void kernel_main()
{
    uart_init();
    char *greeting =    "EEET2490: Embedded Systems - Operating Systems & Interfacing\n"
                        "------------------------------------------------------------\n"
                        "Assessment Group: 8\n"
                        "s3698200: Do Bao Ngoc\n"
                        "s3373237: Le Minh Quang\n"
                        "s3635165: Tran Hoang Long\n";
    puts(greeting);
    
    while (1)
    {
        char c;
        c = getc();
        putc(c);
    }
}
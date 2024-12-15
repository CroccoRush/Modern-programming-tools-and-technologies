#include <stdio.h>

int main()
{
    puts("STDOUT\n");
    fputs("STDERR\n", stderr);
    return 0;
}
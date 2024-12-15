#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    bool use_newline = false;
    bool use_fflush = false;
    int c;

    while ((c = getopt(argc, argv, "nf")) != -1) {
        switch (c) {
            case 'n':
                use_newline = true;
                break;
            case 'f':
                use_fflush = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] [-f]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (use_newline) {
        puts("STDOUT\n");
    } else {
        puts("STDOUT");
    }
    if (use_fflush) {
        fflush(stdout);
    }
    if (use_newline) {
        fputs("STDERR\n", stderr);
    } else {
        fputs("STDERR", stderr);
    }
    if (use_fflush) {
        fflush(stderr);
    }

    return 0;
}
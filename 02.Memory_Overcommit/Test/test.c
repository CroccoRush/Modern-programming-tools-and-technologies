#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PAGE_SIZE 4096 // Page size (4 KB)

void usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s -s <size> -m <r|w> [-p <pause>]\n", prog_name);
    fprintf(stderr, "  -s <size>    The size of the allocated memory in bytes\n");
    fprintf(stderr, "  -m <r|w>     Mode: r - read, w - write\n");
    fprintf(stderr, "  -p <pause>   Pause between requests in microseconds (default is 1000)\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    long long size = 0;         // The size of the allocated memory in bytes
    char mode = 0;              // Mode: r - read, w - write
    long pause = 1000;          // Pause between requests in microseconds
    int opt;

    // Processing command line parameters
    while ((opt = getopt(argc, argv, "s:m:p:")) != -1) {
        switch (opt) {
            case 's':
                size = atoll(optarg); // Converting a string to a long long
                if (size <= 0) {
                    fprintf(stderr, "Error: The size must be a positive number.\n");
                    usage(argv[0]);
                }
                break;
            case 'm':
                if (strlen(optarg) != 1 || (optarg[0] != 'r' && optarg[0] != 'w')) {
                    fprintf(stderr, "Error: The mode should be 'r' or 'w'.\n");
                    usage(argv[0]);
                }
                mode = optarg[0];
                break;
            case 'p':
                pause = atol(optarg); // Converting a string to a long
                if (pause < 0) {
                    fprintf(stderr, "Error: the pause must be non-negative.\n");
                    usage(argv[0]);
                }
                break;
            default:
                usage(argv[0]);
        }
    }

    // Checking that all required parameters are set
    if (size == 0 || mode == 0) {
        fprintf(stderr, "Error: Required parameters are not set.\n");
        usage(argv[0]);
    }

    // Measuring the execution time
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Memory allocation
    char *memory = (char *)malloc(size);
    if (!memory) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    printf("Allocated %lld bytes of memory.\n", size);

    // Accessing memory
    for (long long i = 0; i < size; i += PAGE_SIZE) {
        if (mode == 'r') {
            // Read from memory
            char value = memory[i];
        } else { // mode == 'w'
            // Write to memory the value from 0 to 255
            memory[i] = (char)(i % 256);
        }

        // Pause once every 1000 pages
        if (i % (1000 * PAGE_SIZE) == 0) {
            usleep(pause);
        }
    }

    // Calculation of the execution time
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (double)(end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("The memory access is complete.\n");
    printf("Working time is %.4f sec.\n", elapsed);

    // Freeing up memory
    free(memory);

    return 0;
}
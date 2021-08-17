#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: Not enough arguments.\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "wb");

    for (int i = 0; i < 100; i++) {
        fwrite(&i, sizeof(int), 1, file);
    }
}
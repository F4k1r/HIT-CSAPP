//
// Created by along on 17-10-10.
//

#include <stdio.h>
#include <string.h>

#define BFSIZE (20)
#define BATCHSIZE (16)

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; ++i)
        printf(" %.2x", start[i]);
    printf("\n");
}

int main(int argc, char **args) {
    if (argc != 2) {
        printf("ERROR!!!");
        return 0;
    }

    printf("Open %s\n", args[1]);
    FILE *file = fopen(args[1], "r");
    char buffer[BFSIZE];
    size_t length = fread(buffer, sizeof(char), BATCHSIZE, file);
    while (length != 0) {
        printf("文本：----------\n |%s|\n 16进制码:\n", buffer);
        show_bytes((byte_pointer) buffer, length);
        length = fread(buffer, sizeof(char), BATCHSIZE, file);
    }
    fclose(file);
    return 0;
}
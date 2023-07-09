#include "cat.h"
#include <stdio.h>

#define PARTITION_LENGTH 4096

int cat(char* filename)
{
    FILE* file;
    int offset, filesize, n;
    char buffer[PARTITION_LENGTH];

    if ((file = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    offset = 0;
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    while (offset < filesize)
    {
        n = (filesize - offset) < PARTITION_LENGTH ? filesize - offset : PARTITION_LENGTH;
         
        if (fread(buffer, 1, n, file) != n)
        {
            fprintf(stderr, "Error reading from file.\n");
            return 1;
        }

        fwrite(buffer, 1, n, stdout);

        offset += n;
    }

    fclose(file);

    return 0;
}
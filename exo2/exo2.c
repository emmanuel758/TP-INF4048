#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int countOccurrencesInLine(const char *line, const char *target) {
    int count = 0;
    const char *temp = line;
    while ((temp = strstr(temp, target)) != NULL) {
        count++;
        temp += strlen(target);
    }
    return count;
}


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_name> <word> \n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *target = argv[2];
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "An error occurred while opening the file: %s\n", filename);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        count += countOccurrencesInLine(line, target);
    }

    fclose(file);

    printf("The string \"%s\" appears %d times in the file.\n", target, count);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    q_0,
    q_1,
    q_2,
    q_final
} State;

State nextState(State current, char c) {
    switch(current) {
        case q_0:
            return (c == 'i') ? q_1 : q_0;
        case q_1:
            return (c == 'f') ? q_2 : q_0;
        case q_2:
            return q_final;
        case q_final:
            return (c == 'n') ? q_final : q_2;
    }

    return q_0;
}

int matchIfStarN(const char *line) {
    State state = q_0;
    for(int i = 0; line[i] != '\0'; i++) {
        state = nextState(state, line[i]);
    }
    return (state == q_final);
}

int main(int argc, char *argv[])
{
     if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "An error occurred while opening the file: %s\n", filename);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        if (matchIfStarN(line)) {
            count++;
        }
    }

    fclose(file);

    printf("The regex \"^if.*n$\" matches %d lines in the file.\n", count);

    return 0;
}

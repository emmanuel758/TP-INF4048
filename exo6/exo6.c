#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    q_0,
    q_1,
    q_2,
    q_final,
    q_reject
} State;

State nextState(State current, char c) {
    switch(current) {
        case q_0:
            return (c == 'i') ? q_1 : q_reject;
        case q_1:
            return (c == 'f') ? q_2 : q_0;
        case q_2:
            return (c == 'n') ? q_final : q_2;
        case q_final:
            return q_final;

    }

    return q_0;
}

int matchIfStarN(const char *line) {
    State state = q_0;
    for(int i = 0; line[i] != '\0'; i++) {
        state = nextState(state, line[i]);
    }
    return (state == q_final ? 1 : 0);
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


    if(count > 0) {
        printf("The automate reconaized the regex \"^if.*n$\" in the file.\n");
    } else {
         printf("The automate not reconaized the regex \"^if.*n$\" in the file.\n");
    }

    return 0;
}

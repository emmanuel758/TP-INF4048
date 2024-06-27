
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNextState(const char *target, int state, char c) {
    if (state < strlen(target) && c == target[state]) {
        return state + 1;
    }
    for (int nextState = state; nextState > 0; nextState--) {
        if (target[nextState - 1] == c) {
            int match = 1;
            for (int i = 0; i < nextState - 1; i++) {
                if (target[i] != target[state - nextState + 1 + i]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return nextState;
            }
        }
    }
    return (c == target[0]) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *target = "mur";
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "An error occurred while opening the file: %s\n", filename);
        return 1;
    }

    int state = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        state = getNextState(target, state, c);
        if (state == strlen(target)) {
            count++;
            state = 0; // Reset state to start looking for next occurrence
        }
    }

    fclose(file);

    printf("The string \"%s\" appears %d times in the file.\n", target, count);

    return 0;
}

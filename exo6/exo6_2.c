#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    initial_state,
    final_state
} State;

State nextState(State current, char c) {
    switch(current){
        case initial_state:
            return (c == 'a' || c == 'b' || c == 'c') ? initial_state : final_state;
        case final_state:
            return final_state;
    }
    return initial_state;
}

int matchABCStart(const char *line) {
    State state = initial_state;
    int size = 0;
    for(int i = 0; line[i] != '\0'; i++){
        state = nextState(state, line[i]);
        if(state == initial_state) {
            size+=1;
        }
    }
    return size;
}

int characterNumber(const char *line) {
    int size = 0;
    for(int i = 0; line[i] != '\0'; i++){
        size+=1;
    }
    return size;
}

int main(int argc, char *argv[]){
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
            return 1;
        }

    const char *filename = argv[1];
    int count = 0;
    int file_size = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "An error occurred while opening the file: %s\n", filename);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        file_size += characterNumber(line);
       count += matchABCStart(line);
    }

    fclose(file);

    if(count == file_size) {
        printf("This file reconized regex \"[abc]*\"");
    } else {
        printf("This file not reconized regex \"[abc]*\"");
    }
//     printf("The regex \"[abc]*\" matches %d lines in the file.\n", count);

    return 0;
}

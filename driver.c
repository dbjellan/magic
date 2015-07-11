#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "y.tab.h"
#include "magic.h"
#include "ast.h"
#define MAX_LINE_LENGTH 1024

extern ast_node *root;

FILE *fp = NULL;
char *line;
char *linepos;
bool readfrombuf;

int readInputForLexer(char *buffer, int *numBytesRead, int maxBytesToRead ) {
    if (readfrombuf) {
        int char_left = strlen(linepos);
        if (char_left > maxBytesToRead) {
            memcpy(buffer, linepos, maxBytesToRead);
            *numBytesRead = maxBytesToRead;
            linepos += maxBytesToRead;
        } else {
            memcpy(buffer, linepos, char_left);
            *numBytesRead = char_left;
            linepos += char_left;
        }
        return 1;
    }
    else {
        if (fgets(buffer, maxBytesToRead, fp)) {
            *numBytesRead = strlen(buffer);
            return 1;
        } else {
            return 0;
        }
    }
}

int main(int argc, char *argv[]) {
    m_state* our_state = new_magic_state();
    m_object* result;
    char *result_str;
    if (argc > 1) {
        readfrombuf = false;
        fp = fopen(argv[1], "r");
        yyparse();
        result = ast_execute(our_state, root);
    } else {
        readfrombuf = true;
        size_t length = MAX_LINE_LENGTH;
        while (true) {
            printf(">> ");
            line = NULL;
            if(getline(&line, &length, stdin) != -1) {
                linepos = line;
                yyparse();
                result = ast_execute(our_state, root);
                result_str = magic_object_tostring(result);
                printf("%s\n", result_str);
                free(result_str);
                free(line);
            } else {
                printf("[*] Failed to read line from stdin\n");
            }
        }
    }
    return 0;
}
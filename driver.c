#include <stdio.h>
#include "y.tab.h"

#define MAX_LINE_LENGTH 1024

FILE *fp = NULL;

int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) {

}

int main(int argc, char *argv[]) {
    printf("%d", argc);
    if (argc > 1){
        fp = fopen(argv[1], "r");
    } else {
        char line[MAX_LINE_LENGTH];
        while (true) {
            printf(">> ");
            fgets(line, MAX_LINE_LENGTH, 0);
        }
    }
    yyparse();
    return 0;
}
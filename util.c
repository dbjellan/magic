#include <stdlib.h>
#include <stdio.h>

#include "util.h"

void fatal(char *msg) {
    printf("[*] Fatal error encountered: %s\n", msg);
    exit(1);
}
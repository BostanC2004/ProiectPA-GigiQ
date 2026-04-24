#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "task1.h"
#include "task2.h"

static int is_task1_input(FILE *fin) {
    long pos = ftell(fin);
    char line[256];
    int ok = 0;

    while (fgets(line, sizeof(line), fin) != NULL) {
        char *p = line;
        while (*p && isspace((unsigned char)*p)) p++;

        if (*p == '\0' || *p == '\n' || *p == '\r') {
            continue;
        }

        if (*p == '-' || *p == '+' || isdigit((unsigned char)*p)) {
            ok = 1;
        }
        break;
    }

    fseek(fin, pos, SEEK_SET);
    return ok;
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    if (fin == NULL || fout == NULL) {
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return 1;
    }

    if (is_task1_input(fin)) {
        solveTask1(fin, fout);
    } else {
        solveTask2(fin, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
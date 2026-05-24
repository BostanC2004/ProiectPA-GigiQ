#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"

/*
 * Main-ul doar identifica formatul inputului
 * si apeleaza taskul potrivit.
 */

static void skip_left(char **p) {
    while (**p != '\0' && isspace((unsigned char)**p)) {
        (*p)++;
    }
}

static int parse_int_line(const char *s, int *value) {
    char *end;
    long x = strtol(s, &end, 10);

    if (s == end) return 0;
    while (*end != '\0' && isspace((unsigned char)*end)) end++;
    if (*end != '\0') return 0;

    *value = (int)x;
    return 1;
}

static int first_nonempty(FILE *fin, char *line, int size) {
    while (fgets(line, size, fin) != NULL) {
        char *p = line;
        skip_left(&p);
        if (*p != '\0' && *p != '\n' && *p != '\r') {
            return 1;
        }
    }
    return 0;
}

static int count_nonempty(FILE *fin) {
    char line[512];
    int cnt = 0;

    while (fgets(line, sizeof(line), fin) != NULL) {
        char *p = line;
        skip_left(&p);
        if (*p != '\0' && *p != '\n' && *p != '\r') {
            cnt++;
        }
    }

    return cnt;
}

int main(int argc, const char *const argv[]) {
    if (argc < 3) return 1;

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    if (fin == NULL || fout == NULL) {
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return 1;
    }

    long pos = ftell(fin);
    char line[512];

    if (!first_nonempty(fin, line, sizeof(line))) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    if (strchr(line, ',') != NULL) {
        /* Task 3: simboluri separate prin virgula */
        fseek(fin, pos, SEEK_SET);
        solveTask3(fin, fout);
    } else if (isalpha((unsigned char)line[0])) {
        /* Task 2: inputul incepe cu numele pietelor */
        fseek(fin, pos, SEEK_SET);
        solveTask2(fin, fout);
    } else {
        int n;
        if (parse_int_line(line, &n)) {
            /*
             * Task 4 are exact N + 4 linii non-goale:
             * N, d, K, Pstart, Ptarget si apoi N preturi.
             */
            int rem = count_nonempty(fin);
            fseek(fin, pos, SEEK_SET);

            if (rem == n + 4) {
                solveTask4(fin, fout);
            } else {
                solveTask1(fin, fout);
            }
        } else {
            fseek(fin, pos, SEEK_SET);
            solveTask1(fin, fout);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
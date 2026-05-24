#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "task3.h"

/*
 * Task 3:
 * - prima linie contine simbolurile celor 10 actiuni
 * - apoi citesc randurile de preturi
 * - pentru fiecare actiune construiesc o semnatura U/D
 *
 * U = urcare sau stagnare
 * D = scadere
 *
 * La final compar semnaturile doua cate doua.
 * Daca una este inversul celeilalte, afisez perechea.
 */

#define MAX_STOCKS 10
#define MAX_SYMBOL 32
#define MAX_LINE 512
#define MAX_SIG 4096

static void trim(char *s) {
    int len = (int)strlen(s);

    while (len > 0 &&
           (s[len - 1] == '\n' || s[len - 1] == '\r' ||
            isspace((unsigned char)s[len - 1]))) {
        s[len - 1] = '\0';
        len--;
    }

    int start = 0;
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }

    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
}

static int parse_symbols(char *line, char names[MAX_STOCKS][MAX_SYMBOL]) {
    int count = 0;
    char *token = strtok(line, ",");

    while (token != NULL && count < MAX_STOCKS) {
        trim(token);
        strncpy(names[count], token, MAX_SYMBOL - 1);
        names[count][MAX_SYMBOL - 1] = '\0';
        count++;
        token = strtok(NULL, ",");
    }

    return count;
}

static int parse_prices(char *line, double vals[], int expected) {
    int count = 0;
    char *token = strtok(line, ",");

    while (token != NULL && count < expected) {
        trim(token);
        vals[count] = strtod(token, NULL);
        count++;
        token = strtok(NULL, ",");
    }

    return count;
}

static void append_sig(char sig[MAX_STOCKS][MAX_SIG], int len[MAX_STOCKS], int idx, char c) {
    if (len[idx] + 1 >= MAX_SIG) {
        return;
    }
    sig[idx][len[idx]] = c;
    len[idx]++;
    sig[idx][len[idx]] = '\0';
}

static int is_opposite(const char *a, const char *b) {
    size_t la = strlen(a);
    size_t lb = strlen(b);

    if (la != lb) {
        return 0;
    }

    for (size_t i = 0; i < la; i++) {
        if (!((a[i] == 'U' && b[i] == 'D') || (a[i] == 'D' && b[i] == 'U'))) {
            return 0;
        }
    }

    return 1;
}

void solveTask3(FILE *fin, FILE *fout) {
    char line[MAX_LINE];
    char names[MAX_STOCKS][MAX_SYMBOL];
    char sig[MAX_STOCKS][MAX_SIG];
    int sigLen[MAX_STOCKS] = {0};

    for (int i = 0; i < MAX_STOCKS; i++) {
        sig[i][0] = '\0';
    }

    int nstocks = 0;

    /* Prima linie: simbolurile actiunilor */
    while (fgets(line, sizeof(line), fin) != NULL) {
        trim(line);
        if (line[0] == '\0') continue;

        char first[MAX_LINE];
        strncpy(first, line, MAX_LINE - 1);
        first[MAX_LINE - 1] = '\0';

        nstocks = parse_symbols(first, names);
        break;
    }

    if (nstocks <= 0) {
        return;
    }

    double prev[MAX_STOCKS];
    double curr[MAX_STOCKS];
    int hasPrev = 0;

    /*
     * Primul rand cu preturi devine baza.
     * De la al doilea incolo pot compara evolutia fiecarui stock.
     */
    while (fgets(line, sizeof(line), fin) != NULL) {
        trim(line);
        if (line[0] == '\0') continue;

        char copy[MAX_LINE];
        strncpy(copy, line, MAX_LINE - 1);
        copy[MAX_LINE - 1] = '\0';

        int cnt = parse_prices(copy, curr, nstocks);
        if (cnt != nstocks) {
            continue;
        }

        if (!hasPrev) {
            for (int i = 0; i < nstocks; i++) {
                prev[i] = curr[i];
            }
            hasPrev = 1;
            continue;
        }

        for (int i = 0; i < nstocks; i++) {
            if (curr[i] >= prev[i]) {
                append_sig(sig, sigLen, i, 'U');
            } else {
                append_sig(sig, sigLen, i, 'D');
            }
            prev[i] = curr[i];
        }
    }

    /*
     * Daca doua semnaturi sunt exact inverse, stock-urile se misca opus.
     */
    int first_out = 1;

    for (int i = 0; i < nstocks; i++) {
        for (int j = i + 1; j < nstocks; j++) {
            if (is_opposite(sig[i], sig[j])) {
                if (!first_out) {
                    fprintf(fout, "\n");
                }
                fprintf(fout, "%s-%s", names[i], names[j]);
                first_out = 0;
            }
        }
    }
}
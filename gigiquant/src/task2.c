#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "task2.h"

#define MAX_NAME 100
#define MAX_LINE 256

typedef struct StackNode {
    double val;
    struct StackNode *next;
} StackNode;

typedef struct QNode {
    int day;
    double diff;
    char name[MAX_NAME];
    struct QNode *next;
} QNode;

// Folosim memmove in trim() pentru ca zonele de memorie se suprapun
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

// strtod e mult mai sigur decat atof. endptr ne spune exact unde s-a oprit parsarea
// permitandu-ne sa detectam daca linia contine si gunoi dupa numar
static int is_number_line(const char *s, double *val) {
    char *endptr;
    double x = strtod(s, &endptr);
    // Verificam daca am consumat tot string-ul sau doar spatiile de dupa
    if (s == endptr) {
        return 0;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    *val = x;
    return 1;
}

// 1e-9 (epsilon) este marja de eroare standard pentru a considera doua numere reale egale
static int equalDouble(double a, double b) {
    return fabs(a - b) < 1e-9;
}

static void push(StackNode **top, double val) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (node == NULL) exit(1);
    node->val = val;
    node->next = *top;
    *top = node;
}

static double pop(StackNode **top) {
    if (*top == NULL) return 0.0;
    StackNode *node = *top;
    double val = node->val;
    *top = node->next;
    free(node);
    return val;
}

static void freeStack(StackNode **top) {
    while (*top != NULL) {
        pop(top);
    }
}

static void enqueue(QNode **head, QNode **tail, int day, double diff, const char *name) {
    QNode *node = (QNode *)malloc(sizeof(QNode));
    if (node == NULL) exit(1);

    node->day = day;
    node->diff = diff;
    strncpy(node->name, name, MAX_NAME - 1);
    node->name[MAX_NAME - 1] = '\0';
    node->next = NULL;

    if (*head == NULL) {
        *head = *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
}

static void print2(FILE *fout, double x) {
    long long scaled = llround(x * 100.0);

    if (scaled < 0) {
        fprintf(fout, "-");
        scaled = -scaled;
    }

    fprintf(fout, "%lld.%02lld", scaled / 100, scaled % 100);
}

void solveTask2(FILE *fin, FILE *fout) {
    char line[MAX_LINE];

    StackNode *st[3] = {NULL, NULL, NULL};
    char names[3][MAX_NAME];
    int market = -1;

    names[0][0] = '\0';
    names[1][0] = '\0';
    names[2][0] = '\0';

    while (fgets(line, sizeof(line), fin) != NULL) {
        trim(line);
        if (line[0] == '\0') continue;

        double val;
        if (is_number_line(line, &val)) {
            if (market >= 0 && market < 3) {
                push(&st[market], val);
            }
        } else {
            market++;
            if (market < 3) {
                strncpy(names[market], line, MAX_NAME - 1);
                names[market][MAX_NAME - 1] = '\0';
            }
        }
    }

    QNode *qHead = NULL, *qTail = NULL;
    int day = 1;

    while (st[0] != NULL && st[1] != NULL && st[2] != NULL) {
        double a = st[0]->val;
        double b = st[1]->val;
        double c = st[2]->val;

        if (equalDouble(a, b) && !equalDouble(a, c)) {
            enqueue(&qHead, &qTail, day, fabs(c - a), names[2]);
        } else if (equalDouble(a, c) && !equalDouble(a, b)) {
            enqueue(&qHead, &qTail, day, fabs(b - a), names[1]);
        } else if (equalDouble(b, c) && !equalDouble(a, b)) {
            enqueue(&qHead, &qTail, day, fabs(a - b), names[0]);
        }

        pop(&st[0]);
        pop(&st[1]);
        pop(&st[2]);
        day++;
    }

    while (qHead != NULL) {
        fprintf(fout, "ziua %d - ", qHead->day);
        print2(fout, qHead->diff);
        fprintf(fout, " - %s\n", qHead->name);

        QNode *aux = qHead;
        qHead = qHead->next;
        free(aux);
    }

    freeStack(&st[0]);
    freeStack(&st[1]);
    freeStack(&st[2]);
}
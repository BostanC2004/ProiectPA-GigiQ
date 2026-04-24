#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task1.h"
#include "list.h"

// Funcții ajutătoare de formatare (vizibile doar în acest fișier)
static double trunc3(double x) {
    return trunc(x * 1000.0) / 1000.0;
}

static void print3(FILE *fout, double x) {
    x = trunc3(x);
    if (fabs(x) < 0.0005) {
        x = 0.0;
    }
    fprintf(fout, "%.3f\n", x);
}

void solveTask1(FILE *fin, FILE *fout) {
    int N;
    if (fscanf(fin, "%d", &N) != 1 || N <= 0) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        return;
    }

    Node *prices = NULL;
    for (int i = 0; i < N; i++) {
        double p;
        if (fscanf(fin, "%lf", &p) == 1) {
            addAtEnd(&prices, p);
        }
    }

    if (prices == NULL || prices->next == NULL) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        if (prices) freeList(&prices);
        return;
    }

    double sum = 0.0;
    int count = 0;
    Node *p = prices;

    // Media randamentelor
    while (p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sum += r;
        count++;
        p = p->next;
    }
    double mu = sum / count;

    // Deviatia standard
    double sumSq = 0.0;
    p = prices;
    while (p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sumSq += (r - mu) * (r - mu);
        p = p->next;
    }
    double sigma = sqrt(sumSq / count);

    // Sharpe Ratio
    double sharpe = (sigma != 0.0) ? (mu / sigma) : 0.0;

    // Afisare
    print3(fout, mu);
    print3(fout, sigma);
    print3(fout, sharpe);

    freeList(&prices);
}
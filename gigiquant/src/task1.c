#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task1.h"
#include "list.h"

static void print3(FILE *fout, double x) {
    long long scaled = (long long)trunc(x * 1000.0);

    if (scaled == 0) {
        fprintf(fout, "0.000\n");
        return;
    }

    if (scaled < 0) {
        fprintf(fout, "-");
        scaled = -scaled;
    }
    // %03lld e un "trick" care pune zerouri in fata daca restul e < 100
    fprintf(fout, "%lld.%03lld\n", scaled / 1000, scaled % 1000);
}

void solveTask1(FILE *fin, FILE *fout) {
    int n;
    if (fscanf(fin, "%d", &n) != 1 || n <= 0) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        return;
    }

    Node *prices = NULL;

    for (int i = 0; i < n; i++) {
        double x;
        if (fscanf(fin, "%lf", &x) != 1) {
            freeList(&prices);
            fprintf(fout, "0.000\n0.000\n0.000\n");
            return;
        }
        addAtEnd(&prices, x);
    }

    if (prices == NULL || prices->next == NULL) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        freeList(&prices);
        return;
    }

    double sum = 0.0;
    int cnt = 0;

    Node *p = prices;
    while (p != NULL && p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sum += r;
        cnt++;
        p = p->next;
    }

    double mu = (cnt > 0) ? sum / cnt : 0.0;

    double sumSq = 0.0;
    p = prices;
    while (p != NULL && p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sumSq += (r - mu) * (r - mu);
        p = p->next;
    }

    double sigma = (cnt > 0) ? sqrt(sumSq / cnt) : 0.0;
    double sharpe = (sigma != 0.0) ? (mu / sigma) : 0.0;

    print3(fout, mu);
    print3(fout, sigma);
    print3(fout, sharpe);

    freeList(&prices);
}
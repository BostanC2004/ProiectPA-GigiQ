#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

// Taie zecimalele dupa a treia cifra (fara rotunjire)
static double trunc3(double x) {
    return trunc(x * 1000.0) / 1000.0;
}

// Afiseaza rezultatul si curata valorile foarte mici (evita -0.000)
static void print3(FILE *fout, double x) {
    x = trunc3(x);
    if (fabs(x) < 0.0005) {
        x = 0.0;
    }
    fprintf(fout, "%.3f\n", x);
}

int main(int argc, char *const argv[]) {
    // Verificam prezenta argumentelor in linia de comanda
    if (argc < 3) {
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    if (fin == NULL || fout == NULL) {
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 1;
    }

    // Citim numarul de preturi
    int N;
    if (fscanf(fin, "%d", &N) != 1 || N <= 0) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    Node *prices = NULL;

    // Citim preturile si le salvam in lista
    for (int i = 0; i < N; i++) {
        double p;
        if (fscanf(fin, "%lf", &p) == 1) {
            addAtEnd(&prices, p);
        }
    }

    // Verificam daca avem destule date pentru a calcula randamente
    if (prices == NULL || prices->next == NULL) {
        fprintf(fout, "0.000\n0.000\n0.000\n");
        freeList(&prices);
        fclose(fin);
        fclose(fout);
        return 0;
    }

    double sum = 0.0;
    int count = 0;
    Node *p = prices;

    // Calculam suma randamentelor simple
    while (p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sum += r;
        count++;
        p = p->next;
    }

    // Media randamentelor (Mu)
    double mu = sum / count;

    double sumSq = 0.0;
    p = prices;
    // Calculam suma patratelor diferentelor pentru deviata standard
    while (p->next != NULL) {
        double r = (p->next->val - p->val) / p->val;
        sumSq += (r - mu) * (r - mu);
        p = p->next;
    }

    // Deviatia standard (Sigma) si Sharpe Ratio
    double sigma = sqrt(sumSq / count);
    double sharpe = 0.0;

    if (sigma != 0.0) {
        sharpe = mu / sigma;
    }

    // Afisare rezultate folosind functia speciala de formatare
    print3(fout, mu);
    print3(fout, sigma);
    print3(fout, sharpe);

    // Eliberam memoria si inchidem fisierele
    freeList(&prices);
    fclose(fin);
    fclose(fout);

    return 0;
}
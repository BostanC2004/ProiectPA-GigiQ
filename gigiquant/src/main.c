#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");
    if (!fin || !fout) return 1;
    int N;
    double Rf = 0.01 / 252.0; 
    Node *prices = NULL;
    Node *returns = NULL;
    if (fscanf(fin, "%d", &N) != 1) {
        fclose(fin); fclose(fout);
        return 1;
    }
    // Citim prețurile și le punem în listă
    for (int i = 0; i < N; i++) {
        double p;
        if (fscanf(fin, "%lf", &p) == 1) {
            addAtEnd(&prices, p);
        }
    }
    // Calculăm randamentele: (P_azi - P_ieri) / P_ieri
    Node *curr = prices;
    while (curr != NULL && curr->next != NULL) {
        double r = (curr->next->val - curr->val) / curr->val;
        addAtEnd(&returns, r);
        curr = curr->next;
    }

    int n_ret = getLength(returns);
    if (n_ret >= 1) {
        // 1. Calcul media (Mu)
        double sum = 0;
        Node *temp = returns;
        while (temp != NULL) {
            sum += temp->val;
            temp = temp->next;
        }
        double mu = sum / n_ret;
        // 2. Calcul Deviatia Standard (Sigma) - folosim formula cu (n-1)
        double sum_sq_diff = 0;
        temp = returns;
        while (temp != NULL) {
            sum_sq_diff += pow(temp->val - mu, 2);
            temp = temp->next;
        }
        double sigma = (n_ret > 1) ? sqrt(sum_sq_diff / (n_ret - 1)) : 0;
        // 3. Calcul Sharpe Ratio
        double sharpe = (sigma != 0) ? (mu - Rf) / sigma : 0;
        fprintf(fout, "%.3f\n", mu);
        fprintf(fout, "%.3f\n", sigma);
        fprintf(fout, "%.3f\n", sharpe);
    }
    // Curatam memoria
    freeList(&prices);
    freeList(&returns);
    fclose(fin);
    fclose(fout);

    return 0;
}
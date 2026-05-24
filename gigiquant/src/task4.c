#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task4.h"

/*
 * Task 4:
 * - transform preturile in stari Markov (intervale de marime d)
 * - numar tranzitiile observate intre stari
 * - simulez zi cu zi probabilitatile
 *
 * Aici folosesc ideea de DP bottom-up:
 * cur = ziua curenta
 * nxt = ziua urmatoare
 */

typedef struct {
    long long n, d;
} Fr;

static long long absll(long long x) {
    return x < 0 ? -x : x;
}

static long long gcdll(long long a, long long b) {
    a = absll(a);
    b = absll(b);
    while (b) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a ? a : 1;
}

static Fr norm(Fr f) {
    if (f.d < 0) {
        f.d = -f.d;
        f.n = -f.n;
    }
    if (f.n == 0) {
        f.d = 1;
        return f;
    }
    long long g = gcdll(f.n, f.d);
    f.n /= g;
    f.d /= g;
    return f;
}

static Fr add(Fr a, Fr b) {
    if (a.n == 0) return b;
    if (b.n == 0) return a;

    long long g = gcdll(a.d, b.d);
    long long ad = a.d / g;
    long long bd = b.d / g;

    return norm((Fr){ a.n * bd + b.n * ad, ad * b.d });
}

static Fr mul(Fr a, long long n, long long d) {
    if (a.n == 0 || n == 0) return (Fr){ 0, 1 };

    long long g1 = gcdll(absll(a.n), d);
    long long g2 = gcdll(absll(n), a.d);

    a.n /= g1;
    d /= g1;
    n /= g2;
    a.d /= g2;

    return norm((Fr){ a.n * n, a.d * d });
}

static void printF(FILE *fout, Fr f) {
    f = norm(f);
    if (f.n == 0) {
        fprintf(fout, "0");
    } else if (f.d == 1) {
        fprintf(fout, "%lld", f.n);
    } else {
        fprintf(fout, "%lld/%lld", f.n, f.d);
    }
}

static long long state_of(double p, double d) {
    return (long long)floor(p / d + 1e-12);
}

static int cmp_ll(const void *a, const void *b) {
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    return (x > y) - (x < y);
}

static int find_state(const long long *v, int m, long long x) {
    for (int i = 0; i < m; i++) {
        if (v[i] == x) return i;
    }
    return -1;
}

void solveTask4(FILE *fin, FILE *fout) {
    int N, K;
    double d, pStart, pTarget;

    if (fscanf(fin, "%d", &N) != 1) return;
    if (fscanf(fin, "%lf", &d) != 1) return;
    if (fscanf(fin, "%d", &K) != 1) return;
    if (fscanf(fin, "%lf", &pStart) != 1) return;
    if (fscanf(fin, "%lf", &pTarget) != 1) return;

    double *p = (double *)malloc((size_t)N * sizeof(double));
    if (p == NULL) return;

    for (int i = 0; i < N; i++) {
        if (fscanf(fin, "%lf", &p[i]) != 1) {
            free(p);
            return;
        }
    }

    long long *all = (long long *)malloc((size_t)(N + 2) * sizeof(long long));
    if (all == NULL) {
        free(p);
        return;
    }

    for (int i = 0; i < N; i++) all[i] = state_of(p[i], d);
    all[N] = state_of(pStart, d);
    all[N + 1] = state_of(pTarget, d);

    qsort(all, (size_t)(N + 2), sizeof(long long), cmp_ll);

    int M = 0;
    for (int i = 0; i < N + 2; i++) {
        if (i == 0 || all[i] != all[i - 1]) {
            all[M++] = all[i];
        }
    }

    long long *cnt = (long long *)calloc((size_t)M * (size_t)M, sizeof(long long));
    long long *out = (long long *)calloc((size_t)M, sizeof(long long));
    Fr *cur = (Fr *)calloc((size_t)M, sizeof(Fr));
    Fr *nxt = (Fr *)calloc((size_t)M, sizeof(Fr));

    if (cnt == NULL || out == NULL || cur == NULL || nxt == NULL) {
        free(nxt);
        free(cur);
        free(out);
        free(cnt);
        free(all);
        free(p);
        return;
    }

    /*
     * cnt[i][j] = cate tranzitii observate am avut din starea i in starea j
     * out[i]    = cate tranzitii pleaca din starea i
     */
    for (int i = 0; i < N - 1; i++) {
        int a = find_state(all, M, state_of(p[i], d));
        int b = find_state(all, M, state_of(p[i + 1], d));
        if (a >= 0 && b >= 0) {
            cnt[a * M + b]++;
            out[a]++;
        }
    }

    int s = find_state(all, M, state_of(pStart, d));
    int t = find_state(all, M, state_of(pTarget, d));
    if (s < 0 || t < 0) {
        free(nxt);
        free(cur);
        free(out);
        free(cnt);
        free(all);
        free(p);
        return;
    }

    /* Ziua 1: suntem sigur in starea initiala */
    cur[s] = (Fr){ 1, 1 };

    for (int day = 1; day <= K; day++) {
        if (day > 1) fprintf(fout, "\n");
        printF(fout, cur[t]);

        if (day == K) break;

        for (int i = 0; i < M; i++) {
            nxt[i] = (Fr){ 0, 1 };
        }

        for (int i = 0; i < M; i++) {
            if (cur[i].n == 0) continue;

            /* Daca o stare nu are iesiri, ramane in ea */
            if (out[i] == 0) {
                nxt[i] = add(nxt[i], cur[i]);
                continue;
            }

            for (int j = 0; j < M; j++) {
                long long c = cnt[i * M + j];
                if (c > 0) {
                    nxt[j] = add(nxt[j], mul(cur[i], c, out[i]));
                }
            }
        }

        Fr *tmp = cur;
        cur = nxt;
        nxt = tmp;
    }

    free(nxt);
    free(cur);
    free(out);
    free(cnt);
    free(all);
    free(p);
}
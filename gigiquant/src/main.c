#include <stdio.h>
#include <stdlib.h>
#include "task1.h"

int main(int argc, char *const argv[]) {
    // Verificăm dacă avem: ./giquant <nr_task> <in> <out>
    if (argc < 4) {
        return 1;
    }

    int task_nr = atoi(argv[1]);
    FILE *fin = fopen(argv[2], "r");
    FILE *fout = fopen(argv[3], "w");

    if (fin == NULL || fout == NULL) {
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 1;
    }

    // Alegem task-ul de executat
    if (task_nr == 1) {
        solveTask1(fin, fout);
    } 
    /* else if (task_nr == 2) {
        solveTask2(fin, fout);
    }
    */

    fclose(fin);
    fclose(fout);
    return 0;
}
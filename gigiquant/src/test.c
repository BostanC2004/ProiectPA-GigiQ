#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* const argv[]) {
   FILE *fi= fopen(argv[1], "r");
   FILE *fo= fopen(argv[2], "w");;
   fprintf(fo, "DEMO\n");
   fclose(fi);
   fclose(fo);
   return 0;
}

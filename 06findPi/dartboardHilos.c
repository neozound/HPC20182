#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define REAL_PI   3.141592653589793238462643383279

int main(int argc, char *argv[]){
  int i;
  int lanzamientos = atoi(argv[1]);
  int pntsCirculo = 0;

  int p;
  p = omp_get_num_procs();
  omp_set_num_threads(p);

  long double randX, randY, pi;

  srand(time(NULL));

  double start = omp_get_wtime();

  #pragma omp parallel for shared(lanzamientos) private(i, randX, randY) reduction(+:pntsCirculo)
  for (i = 0; i < lanzamientos; ++i) {
    randX = rand() / (double)RAND_MAX;
    //printf("randX=%Lf\n", randX);
    randY = rand() / (double)RAND_MAX;
    //printf("randY=%Lf\n", randY);
    if (((randX*randX) + (randY*randY)) < 1)
      ++pntsCirculo;
      //printf("pntsCirculo=%d\n", pntsCirculo);
  }

  double end = omp_get_wtime();

  printf("pntsCirculo=%d\n", pntsCirculo);
  printf("lanzamientos=%d\n", lanzamientos);

  printf("Tiempo: %f\n", end - start);

  pi = (long double) (4 * ((long double) pntsCirculo /  (long double) lanzamientos));

  printf("pi=%Lf\n", pi);

  printf("Eabs=%Lf o/o \n", pi - REAL_PI);

  printf("Erel=%Lf o/o \n", ((pi - REAL_PI) / REAL_PI)  * 100);

  return 0;
}

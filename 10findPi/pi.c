#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

#define REAL_PI         3.141592653589793238462643383279
#define NUM_OF_SHOTS    100000

int main(int argc, char *argv[]){
  
  MPI_Init(&argc, &argv);
  
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  if (world_size < 2) {
        printf("Esta operación no puede realizarse con menos de 2 procesos");
        MPI_Abort(MPI_COMM_WORLD, 1);
  }
  
  int i;
  int numOfShots = atoi(argv[1]);
  int circlePoints = 0;
  
  long double randX, randY;
  
  double t1, t2;
  
  srand(time(NULL));
  
  t1 = MPI_Wtime();
  MPI_Barrier(MPI_COMM_WORLD);
  
  for (i = 0; i < numOfShots; ++i) {
    randX = rand() / (double)RAND_MAX;
    //printf("randX=%Lf\n", randX);
    randY = rand() / (double)RAND_MAX;
    //printf("randY=%Lf\n", randY);
    if (((randX*randX) + (randY*randY)) < 1)
      ++circlePoints;
      //printf("pntsCirculo=%d\n", pntsCirculo);
  }
  
  MPI_Barrier(MPI_COMM_WORLD);
  t2 = MPI_Wtime();
  
  
  int *all_circlePoints = (int *)malloc(sizeof(int)*world_size);
  
  printf("pntsCirculo=%d\n", circlePoints);
  printf("lanzamientos=%d\n", numOfShots);
  
  MPI_Gather(&circlePoints, 1, MPI_INT, all_circlePoints, 1, 
             MPI_INT, 0, MPI_COMM_WORLD);
  
  if (world_rank == 0) {
    int avg_cp = 0;
    long double pi = 0;
    
    for(i = 0; i < world_size; i++) {
        avg_cp += all_circlePoints[i];
    }
    
    pi = (long double) (4 * ((long double) avg_cp /  (long double) (numOfShots * world_size)));
    
    printf("pi=%Lf\n", pi);
    printf("Eabs=%Lf o/o \n", pi - REAL_PI);
    printf("Erel=%Lf o/o \n", ((pi - REAL_PI) / REAL_PI)  * 100);
    
    printf( "Elapsed time is %f\n", t2 - t1 ); 
  }
  
  
  
  MPI_Finalize();
  
  return 0;
}

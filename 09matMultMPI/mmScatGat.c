#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAT_SIZE    4

int main (int argc, char** argv) {
    
    MPI_Init(&argc, &argv);
    
    MPI_Status status;
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    // Inicializacion de matrices
    int size = atoi(argv[1]);
    
    int i, j, k, n;
    
    if (world_size < 2) {
        printf("Esta operación no puede realizarse con menos de 2 procesos");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    // Partimos en los trozos en partes iguales
    int num_elements = size * size;

    float *a = (float *)malloc(sizeof(float) * num_elements);
    float *b = (float *)malloc(sizeof(float) * num_elements);
    float *c = (float *)malloc(sizeof(float) * num_elements);
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    
    // inicializar la matriz a
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
          a[(i*size)+j] = 1;
        }
    }
    
    // inicializar la matriz b
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
          b[(i*size)+j] = 2;
        }
    }
    
    // inicializar la matriz c
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
          c[(i*size)+j] = 0;
        }
    }
    
    int sum = 0;
    int rem = (size*size)%world_size;
    int *sendcounts = malloc(sizeof(int)*world_size);
    int *displs = malloc(sizeof(int)*world_size);
    
    //printf("rem: %d\n", rem);
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Calculate send counts and displacements
    for (int i = 0; i < world_size; i++) {
        
        sendcounts[i] = (size*size)/world_size;
        
        if (rem > 0) {
            sendcounts[i]++;
            rem--;
        }
        
        displs[i] = sum;
        sum += sendcounts[i];
        
    }
    
    float *part = (float *)malloc(sizeof(float) * sendcounts[0]);
    
    //print calculated send counts and displacements for each process
    /*
    if (world_rank == 0) {
        for (i = 0; i < world_size; i++) {
            printf("sendcounts[%d] = %d\tdispls[%d] = %d\n", i, sendcounts[i], i, displs[i]);
            
        }
    }
    */
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Divide the data among processes as described by sendcounts and displs
    MPI_Scatterv(c, sendcounts, displs, MPI_FLOAT, part, sendcounts[0], MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    // print what each process received
    
    /*
    printf("%d: ", world_rank);
    for (int i = 0; i < sendcounts[world_rank]; i++) {
        printf("%f ", part[i]);
    }
    */
    
    //printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);
    
    int ini = displs[world_rank];
    int fin = displs[world_rank] + sendcounts[world_rank];
    
    MPI_Barrier(MPI_COMM_WORLD);
    double t1 = MPI_Wtime();
    
    // multiplicacion matrices de cada elemento
    for (n = ini; n < fin; n++) {
        i = n/size;
        j = n%size;
        
        for (k = 0; k < size; k++) {
          part[ n - ini ] += a[(i*size)+k]*b[(k*size)+j];
        }
    }
    
    double t2 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    
    //Aqui intento recibir la matriz en c
    
    MPI_Gatherv(part, sendcounts[world_rank], MPI_FLOAT, c, sendcounts, displs, 
                MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if (world_rank == 0) {
        
        // mostrar la matriz c
        
        /*
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
              printf("%f ", c[(i*size)+j]);
            }
            printf("\n");
        }
        */
        
        printf( "Elapsed time is %f\n", t2 - t1 );
    }
    
    MPI_Finalize();
    
    free(sendcounts);
    free(displs);
    free(a);
    free(b);
    free(c);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void fillMatrixWithNumber(float *M, int size, float v)
{
  int i, j;
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    {
      M[(i*size)+j] = v;
    }
  }
}

void printMatrix(float *M, int size){
  int i, j;
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    {
      printf("%f ", M[(i*size) + j]);
    }
    printf("\n");
  }
}

void multMatrixSeq(float *Ma, float *Mb, float *Mc, int size){
  int i, j, k;
  
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    {
      
      for (k = 0; k < size; k++) 
      {
        Mc[i*size+j] += Ma[(i*size)+k]*Mb[(k*size)+j];
      }
      
      
    }
  }
}

void multMatrixHilos(float *Ma, float *Mb, float *Mc, int size){
  int i, j, k;
  
  #pragma omp parallel for shared(Ma, Mb, Mc, size) private(i, j, k)
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    {
      
      for (k = 0; k < size; k++) 
      {
        Mc[i*size+j] += Ma[(i*size)+k]*Mb[(k*size)+j];
      }
      
      
    }
  }
}



void multMatrixFilas(float *Ma, float *Mb, float *Mc, int size){
  int i, j, k;
    
  for (i = 0; i < size; i++) 
  {
    #pragma omp parallel for shared(Ma, Mb, Mc, size, i) private(j, k)
    for (j = 0; j < size; j++) 
    {
      
      for (k = 0; k < size; k++) 
      {
        Mc[i*size+j] += Ma[(i*size)+k]*Mb[(k*size)+j];
      }
      
      
      
    }
  }
}

void multMatrixCeldas(float *Ma, float *Mb, float *Mc, int size){
  int i, j, k;
  int t;

  
  for (i = 0; i < size; i++) 
  {
    for (j = 0; j < size; j++) 
    { 
      t = 0;
      
      #pragma omp parallel for ordered shared(Ma, Mb, Mc, size, i, j) private(k) reduction(+:t)
      for (k = 0; k < size; k++) 
      {
        t += Ma[(i*size)+k]*Mb[(k*size)+j];
      }
      
      Mc[i*size+j] = t;
    }
  }
}

/*
El programa puede cargar la matriz de un archivo, llenarla
aleatoriamente o llenarla con un valor

multMatSeq.c  mms  fill   2 1 2   --    2x2 1 2
multMatSeq.c  mmh  fill   2 1 2   --    2x2 1 2
multMatSeq.c  mmf  fill   2 1 2   --    2x2 1 2
multMatSeq.c  mmc  fill   2 1 2   --    2x2 1 2

multMatSeq.c random 2       --    2x2 random
multMatSeq.c load   d.txt   --    carga las matrices
*/

int main (int argc, char*argv[]){
  
  int s;
  float *a, *b, *c;
  
  
  if( strcmp(argv[2],"fill") == 0 )
  {
    //printf("Filling up...\n");
    
    s = atoi(argv[3]);
    
    int v1 = atoi(argv[4]);
    int v2 = atoi(argv[5]);
    
    //printf("size: %d\nv1: %d\nv2: %d\n", s, v1, v2);
    
    a = (float *)malloc(sizeof(float)*s*s);
    b = (float *)malloc(sizeof(float)*s*s);
    c = (float *)malloc(sizeof(float)*s*s);
    
    fillMatrixWithNumber(a, s, v1);
    //printMatrix(a, s);
    
    fillMatrixWithNumber(b, s, v2);
    //printMatrix(b, s);
    
    fillMatrixWithNumber(c, s, 0);
    //printMatrix(c, s);
    
    
  }
  
  double start = omp_get_wtime();
  if( strcmp(argv[1],"mms") == 0 )
  {
    multMatrixSeq(a, b, c, s);
  }
  else if ( strcmp(argv[1],"mmh") == 0 )
  {
    multMatrixHilos(a, b, c, s);
  }
  else if ( strcmp(argv[1],"mmf") == 0 )
  {
    multMatrixFilas(a, b, c, s);
  }
  else if ( strcmp(argv[1],"mmc") == 0 )
  {
    multMatrixCeldas(a, b, c, s);
  }
  else
  {
    printf("La opcion no existe\n");
    return 0;
  }
  double end = omp_get_wtime();
  
  //printMatrix(c, s);
  
  printf("Tiempo: %f\n", end - start);
  
  free(a);
  free(b);
  free(c);
  
  
  return 0;

}

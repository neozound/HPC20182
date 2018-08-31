#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillMatrixWithNumber(float *M, int size, float v){
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      M[(i*size)+j] = v;
    }
  }
}

void printMatrix(float *M, int size){
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      printf("%f ", M[(i*size) + j]);
    }
    printf("\n");
  }
}

void multMatrix(float *Ma, float *Mb, float *Mc, int size){
  float t = 0;
  int i, j, k;
  
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      
      for (k = 0; k < size; k++) {
        t += Ma[(i*size)+k]*Mb[(k*size)+j];
      }
      Mc[i*size+j] = t;
      t = 0;
      
    }
  }
}

/*
El programa puede cargar la matriz de un archivo, llenarla
aleatoriamente o llenarla con un valor

multMatSeq.c fill   2 1 2   --    2x2 1 2
multMatSeq.c random 2       --    2x2 random
multMatSeq.c load   d.txt   --    carga las matrices
*/

int main (int argc, char*argv[]){
  
  int s;
  float *a, *b, *c;
  
  if( strcmp(argv[1],"fill") == 0 ){
    //printf("Filling up...\n");
    
    s = atoi(argv[2]);
    
    int v1 = atoi(argv[3]);
    int v2 = atoi(argv[4]);
    
    //printf("size: %d\nv1: %d\nv2: %d\n", s, v1, v2);
    
    a = (float *)malloc(sizeof(float)*s*s);
    b = (float *)malloc(sizeof(float)*s*s);
    c = (float *)malloc(sizeof(float)*s*s);
    
    fillMatrixWithNumber(a, s, v1);
    printMatrix(a, s);
    
    fillMatrixWithNumber(b, s, v2);
    printMatrix(b, s);
    
    fillMatrixWithNumber(c, s, 0);
    printMatrix(c, s);
    
    
  }
  
  multMatrix(a, b, c, s);
  printMatrix(c, s);
  
  return 0;

}

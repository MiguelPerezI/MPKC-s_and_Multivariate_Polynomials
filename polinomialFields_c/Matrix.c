#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Matrix.h"
#include "vector.h"

int digitCounter(int n) {
    int count = 0;
    if (n == 0) {return 1;}
    while (n != 0) {
          n /= 10; 
          ++count;
    }
    
return count;
}

void space(int n) {
     int i;
     for (i = 0; i < n; i++) 
         printf(" ");
}

MATRIZ creaEspacioMatriz(int m, int n)
{
  MATRIZ ret = {m:m, n:n, A:NULL};
  int i;

  ret.A = (double**) malloc (m * sizeof(double*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (double *) malloc (n * sizeof(double));
      if (ret.A[i] == NULL){
        while(i > 0){
          free(ret.A[--i]);
          ret.A[i] = NULL;
        }
        break;
      }
    }
  }

  return ret;
}

MatrixV creaEspacioMatrixV(int m, int n) {
  MatrixV ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (Vector**) malloc (m * sizeof(Vector*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (Vector *) malloc (n * sizeof(Vector));
      if (ret.A[i] == NULL){
        while(i > 0){
          free(ret.A[--i]);
          ret.A[i] = NULL;
        }
        break;
      }
    }
  }

  return ret;
}

MatrixInt creaEspacioMatrixInt(int m, int n) {
  MatrixInt ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (int**) malloc (m * sizeof(int*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (int *) malloc (n * sizeof(int));
      if (ret.A[i] == NULL){
        while(i > 0){
          free(ret.A[--i]);
          ret.A[i] = NULL;
        }
        break;
      }
    }
  }

  return ret;
}

MatrixIntList initMatrixIntList(int n) {
  MatrixIntList ret = {
                  n : n, 
                  M : NULL
                };
  int i;
  ret.M = (MatrixInt*) malloc (n * sizeof(MatrixInt));

  return ret;
}

int leeMatriz(MATRIZ *mat)
{
  int m, n, i, j;

  if (mat == NULL) return -1; /*codigo de error*/
  printf("Digite numero de renglones m:");
  scanf("%d", &m);
  printf("Digite numero de columnas n:");
  scanf("%d", &n);
  *mat = creaEspacioMatriz(m, n);
  printf("digite las entradas de la matriz:\n");
  for(i = 0; i < m; i++)
    for (j = 0; j < n; j++){
      printf("[%2d, %2d]=", i, j);
      scanf("%lg", &(mat->A[i][j]));
    }

  return 0; /*codigo de terminacion exita*/
}

int escMatriz(MATRIZ mat)
{
  int i, j;

  for (j = 0; j < mat.n; j++){
    printf("\n");
    for (i = 0; i < mat.m; i++){
      printf("%6lg ", mat.A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}

int liberaEspacioMatriz(MATRIZ * mat)
{
  int i;

  for (i=0; i<mat->m; i++){
    free(mat->A[i]);
    mat->A[i]=NULL;
  }
  free(mat->A);
  mat->A=NULL;
  mat->m = mat->n = 0;

  return 0;
}

MATRIZ sumaM(MATRIZ a, MATRIZ b)
{
  MATRIZ C={0,0};
  int i, j;
  if(a.n!=b.n || a.m!=b.m) return C;
  C.m=a.m;
  C.n=a.n;
  C=creaEspacioMatriz(C.m, C.n);
  for(i=0; i<C.m; i++)
      for(j=0; j<C.n; j++)
      C.A[i][j]=a.A[i][j]+b.A[i][j];
      
  return C;
}

MATRIZ restaM(MATRIZ a, MATRIZ b)
{
  MATRIZ C={0,0};
  int i, j;
  if(a.n!=b.n || a.m!=b.m) return C;
  C.m=a.m;
  C.n=a.n;
  C=creaEspacioMatriz(C.m, C.n);
  for(i=0; i<C.m; i++)
      for(j=0; j<C.n; j++)
      C.A[i][j]=a.A[i][j]-b.A[i][j];
      
  return C;
}

 MATRIZ prodM(MATRIZ a, MATRIZ b)
 {      
  MATRIZ C={0,0};
  int k, i, j;
  if(a.n!=b.m) return C;
  
  C.m=a.m;
  C.n=b.n;
  C=creaEspacioMatriz(C.m, C.n); 
  
   for(i=0; i<C.m; i++)
      for(j=0; j<C.n; j++)
          C.A[i][j]=0.0;
  
  for(i=0; i<C.m; i++)
      for(j=0; j<C.n; j++)
      {
         for(k=0; k<a.n; k++)
           C.A[i][j]=a.A[i][k]*b.A[k][j]+C.A[i][j];   
        }   
 return C;
}


MATRIZ tableZeroReal(MATRIZ Table1, int n) {
      int i;
      int j;
    
      Table1 = creaEspacioMatriz(n, n);
               for (i = 0; i < n; i++)
                   for (j = 0; j < n; j++) 
                       Table1.A[i][j] = 0;
      return Table1;
}

struct rotationMats initRotation(double theta) {

  struct rotationMats U = {theta : theta};

  MATRIZ mat;
  mat = tableZeroReal(mat, 3);
  mat.A[0][0] = cos(theta);  mat.A[0][1] =-sin(theta); mat.A[0][2] = 0;
  mat.A[1][0] = sin(theta);  mat.A[1][1] = cos(theta); mat.A[1][2] = 0;
  mat.A[2][0] = 0;           mat.A[2][1] = 0;          mat.A[2][2] = 1;

  vectorGo(&U.aX, 3, mat.A[0][0], mat.A[1][0], mat.A[2][0]);
  vectorGo(&U.aY, 3, mat.A[0][1], mat.A[1][1], mat.A[2][1]);
  vectorGo(&U.aZ, 3, mat.A[0][2], mat.A[1][2], mat.A[2][2]);

  vectorGo(&U.aux, 3, 0, 0, 0);

  U.rotZ = mat;

  return U;
}

struct rotationMats initRotationY(double theta) {

  struct rotationMats U = {theta : theta};

  MATRIZ mat;
  mat = tableZeroReal(mat, 3);
  mat.A[0][0] = cos(theta);  mat.A[0][1] = 0;          mat.A[0][2] = sin(theta);
  mat.A[1][0] =          0;  mat.A[1][1] = 1;          mat.A[1][2] = 0;
  mat.A[2][0] =-sin(theta);  mat.A[2][1] = 0;          mat.A[2][2] = cos(theta);

  vectorGo(&U.aX, 3, mat.A[0][0], mat.A[1][0], mat.A[2][0]);
  vectorGo(&U.aY, 3, mat.A[0][1], mat.A[1][1], mat.A[2][1]);
  vectorGo(&U.aZ, 3, mat.A[0][2], mat.A[1][2], mat.A[2][2]);

  vectorGo(&U.aux, 3, 0, 0, 0);

  U.rotZ = mat;

  return U;
}

void updateRotation(struct rotationMats * U, double theta) {
  U->theta = theta;

  U->rotZ.A[0][0] = cos(theta);  U->rotZ.A[0][1] =-sin(theta); U->rotZ.A[0][2] = 0;
  U->rotZ.A[1][0] = sin(theta);  U->rotZ.A[1][1] = cos(theta); U->rotZ.A[1][2] = 0;
  U->rotZ.A[2][0] = 0;           U->rotZ.A[2][1] = 0;          U->rotZ.A[2][2] = 1;

  U->aX.v[0] = cos(theta); U->aX.v[1] =-sin(theta); U->aX.v[2] = 0;
  U->aY.v[0] = sin(theta); U->aY.v[1] = cos(theta); U->aY.v[2] = 0;
  U->aZ.v[0] =          0; U->aZ.v[1] =          0; U->aZ.v[2] = 1;
}

void updateRotationY(struct rotationMats * U, double theta) {
  U->theta = theta;

  U->rotZ.A[0][0] = cos(theta);  U->rotZ.A[0][1] = 0; U->rotZ.A[0][2] = sin(theta);
  U->rotZ.A[1][0] =          0;  U->rotZ.A[1][1] = 1; U->rotZ.A[1][2] = 0;
  U->rotZ.A[2][0] =-sin(theta);  U->rotZ.A[2][1] = 0; U->rotZ.A[2][2] = cos(theta);

  U->aX.v[0] = cos(theta); U->aX.v[1] = 0; U->aX.v[2] = sin(theta);
  U->aY.v[0] =          0; U->aY.v[1] = 1; U->aY.v[2] = 0;
  U->aZ.v[0] =-sin(theta); U->aZ.v[1] = 0; U->aZ.v[2] = cos(theta);
}

void rot3D(struct rotationMats * U, Vector v) {

  U->aux.v[0] = (v.v[0] * U->aX.v[0]) + (v.v[1] * U->aX.v[1]) + (v.v[2] * U->aX.v[2]);
  U->aux.v[1] = (v.v[0] * U->aY.v[0]) + (v.v[1] * U->aY.v[1]) + (v.v[2] * U->aY.v[2]);
  U->aux.v[2] = (v.v[0] * U->aZ.v[0]) + (v.v[1] * U->aZ.v[1]) + (v.v[2] * U->aZ.v[2]);

}

void rot3DP(struct rotationMats * U, Vector * v) {

  U->aux.v[0] = (v->v[0] * U->aX.v[0]) + (v->v[1] * U->aX.v[1]) + (v->v[2] * U->aX.v[2]);
  U->aux.v[1] = (v->v[0] * U->aY.v[0]) + (v->v[1] * U->aY.v[1]) + (v->v[2] * U->aY.v[2]);
  U->aux.v[2] = (v->v[0] * U->aZ.v[0]) + (v->v[1] * U->aZ.v[1]) + (v->v[2] * U->aZ.v[2]);

  updateVectorR3(v, U->aux.v[0], U->aux.v[1], U->aux.v[2]);
}

struct rotationMats initAxeRotation(Vector head, Vector base, double theta) {

  struct rotationMats U = {
                            theta : theta,
                            head : head,
                            base : base};
  subVector(&head, base);
  Vector rot = getSubVector(head);
  unitVector(&rot);
  updateVectorR3(&rot, rot.w[0], rot.w[1], rot.w[2]);
  //printf("norma = %lg\n\n", rot.norma);
  double x = rot.v[0];
  double y = rot.v[1];
  double z = rot.v[2];
  double s = sin(theta);
  double c = 1.0 - cos(theta);
  U.identity = creaEspacioMatriz(3, 3);
  U.identity.A[0][0] = 1.0;  U.identity.A[1][0] = 0.0;  U.identity.A[2][0] = 0.0;
  U.identity.A[0][1] = 0.0;  U.identity.A[1][1] = 1.0;  U.identity.A[2][1] = 0.0;
  U.identity.A[0][2] = 0.0;  U.identity.A[1][2] = 0.0;  U.identity.A[2][2] = 1.0;

  U.anti1 = creaEspacioMatriz(3, 3);
  U.anti1.A[0][0] = 0;  U.anti1.A[1][0] =-z;  U.anti1.A[2][0] = y;
  U.anti1.A[0][1] = z;  U.anti1.A[1][1] = 0;  U.anti1.A[2][1] =-x;
  U.anti1.A[0][2] =-y;  U.anti1.A[1][2] = x;  U.anti1.A[2][2] = 0;

  U.anti2 = creaEspacioMatriz(3, 3);
  U.anti2.A[0][0] =   0;  U.anti2.A[1][0] =-s*z;  U.anti2.A[2][0] = s*y;
  U.anti2.A[0][1] = s*z;  U.anti2.A[1][1] =   0;  U.anti2.A[2][1] =-s*x;
  U.anti2.A[0][2] =-s*y;  U.anti2.A[1][2] = s*x;  U.anti2.A[2][2] = 0;

  U.anti3 = creaEspacioMatriz(3, 3);
  U.anti3.A[0][0] =   0;  U.anti3.A[1][0] =-c*z;  U.anti3.A[2][0] = c*y;
  U.anti3.A[0][1] = c*z;  U.anti3.A[1][1] =   0;  U.anti3.A[2][1] =-c*x;
  U.anti3.A[0][2] =-c*y;  U.anti3.A[1][2] = c*x;  U.anti3.A[2][2] = 0;
  
    U.mat = sumaM(U.identity, U.anti2);
    U.mat = sumaM(U.mat, prodM(U.anti3, U.anti1));

  vectorGo(&U.aX, 3, U.mat.A[0][0], U.mat.A[1][0], U.mat.A[2][0]);
  vectorGo(&U.aY, 3, U.mat.A[0][1], U.mat.A[1][1], U.mat.A[2][1]);
  vectorGo(&U.aZ, 3, U.mat.A[0][2], U.mat.A[1][2], U.mat.A[2][2]);

  vectorGo(&U.aux, 3, 0, 0, 0);

  return U;
}

Vector rot3DAxe(struct rotationMats * U, Vector v) {

  subVector(&v, U->base);
  Vector aa = getSubVector(v);
  U->aux.v[0] = (aa.v[0] * U->aX.v[0]) + (aa.v[1] * U->aX.v[1]) + (aa.v[2] * U->aX.v[2]);
  U->aux.v[1] = (aa.v[0] * U->aY.v[0]) + (aa.v[1] * U->aY.v[1]) + (aa.v[2] * U->aY.v[2]);
  U->aux.v[2] = (aa.v[0] * U->aZ.v[0]) + (aa.v[1] * U->aZ.v[1]) + (aa.v[2] * U->aZ.v[2]);

  addVector(&U->aux, U->base);
  Vector ret;
  vectorGo(&ret, 3, U->aux.w[0], U->aux.w[1], U->aux.w[2]);

  return ret;
}
#include <stdbool.h>
#include "vector.h"

#ifndef _MATRIX_
#define _MATRIX_

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _matriz_{
  int m, n;
  double **A;
}MATRIZ;

int digitCounter(int n);
void space(int n);

MATRIZ creaEspacioMatriz(int m, int n);
int leeMatriz(MATRIZ *mat);
int escMatriz(MATRIZ mat);
MATRIZ tableZeroReal(MATRIZ Table1, int n);
MATRIZ AdjMatrixWeights(int n);
int liberaEspacioMatriz(MATRIZ *mat);
MATRIZ sumaM(MATRIZ a, MATRIZ b);
MATRIZ restaM(MATRIZ a, MATRIZ b);
MATRIZ prodM(MATRIZ a, MATRIZ b);
//Vector3D matMult3D(MATRIZ mat, Vector3D v);

typedef struct _matrixV_{
	int m, n;
	Vector **A;
}MatrixV;

MatrixV creaEspacioMatrixV(int m, int n);

struct rotationMats{
	double theta;
	MATRIZ rotZ;
	Vector aX;
	Vector aY;
	Vector aZ;
	Vector aux;
	Vector head;
	Vector base;
	MATRIZ identity;
	MATRIZ anti1;
	MATRIZ anti2;
	MATRIZ anti3;
	MATRIZ mat;
};

struct rotationMats initRotation(double theta);
struct rotationMats initRotationY(double theta);
void updateRotation(struct rotationMats * U, double theta);
void rot3D(struct rotationMats * U, Vector v);
void rot3DP(struct rotationMats * U, Vector * v);
struct rotationMats initAxeRotation(Vector head, Vector base, double theta);
Vector rot3DAxe(struct rotationMats * U, Vector v);

typedef struct _matrixInt_{
	int m, n;
	int **A;
}MatrixInt;

MatrixInt creaEspacioMatrixInt(int m, int n);

typedef struct _matrixIntList_{
	int n;
	MatrixInt *M;
}MatrixIntList;

MatrixIntList initMatrixIntList(int n);

#ifdef __cplusplus
}
#endif

#endif
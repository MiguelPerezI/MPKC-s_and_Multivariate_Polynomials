#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include <stdarg.h>
#include "Arista.h"
#include "vector.h"

#ifndef _AnilloZn_
#define _AnilloZn_

#ifdef __cplusplus
extern "C" {
#endif

struct AnilloZp {

	int id;
	int mod;
	MatrixInt linearSpace;
	MatrixV latticeSpace;
	MatrixV latticeSpace0;
	MatrixV	vectorSpace;
	MatrixInt addAuxMat;
	MatrixInt multAuxMat;
	MatrixVecindadCubica campo;
	MatrixVecindadCubica campo0;

};

void initAnilloZp(struct AnilloZp * AnilloZp, int id, int mod);
void printAnilloZp(struct AnilloZp anillo);
void renderAnilloZp(struct AnilloZp anillo, struct rotationMats U);

typedef struct _MatrixAnilloZp_{
	int m, n;
	struct AnilloZp **A;
}MatrixAnilloZp;

MatrixAnilloZp creaMatrixAnilloZp(int m, int n);

typedef struct _PolinomioZp_{

	int mod;
	int grado;
	int * a;
	int * aux;

}PolinomioZp;

void initPolinomioZp(PolinomioZp * p, int mod, int grado, ...); 
void printPolinomioZp(PolinomioZp p);
PolinomioZp addPolinomioZp(PolinomioZp p, PolinomioZp q);
PolinomioZp subPolinomioZp(PolinomioZp p, PolinomioZp q);
PolinomioZp vecToPolinomioZp2D(Vector p, int mod);
Vector PolinomioZpToVec(PolinomioZp p);
void additionInZp(struct AnilloZp * anillo, PolinomioZp p);
void subtractionInZp(struct AnilloZp * anillo, PolinomioZp p);
PolinomioZp multPolinomioZp(PolinomioZp p, PolinomioZp q);
PolinomioZp multSPolinomioZp(int k, PolinomioZp p);
int pot(int p, int n);
int max(int a, int b);
int irreducibleEnZp( PolinomioZp p);
int potMod(int n, int m, int mod);
int inversoZp(int a, int mod);
int divideZp(int num, int den, int mod);
int zero(PolinomioZp p);
int zeroP(PolinomioZp * p);
void checkPolinomioZp(PolinomioZp * p);
void subPolinomioZpP(PolinomioZp * p, PolinomioZp q);
PolinomioZp auxPoli(int head, int num, int mod);
PolinomioZp modP(PolinomioZp a, PolinomioZp p);
void printPolinomioZpP(PolinomioZp * p);
void checkNegativesPoli(PolinomioZp * p);
void multiplicationInZp(struct AnilloZp * anillo, PolinomioZp p);

typedef struct _Fields_{

	MatrixAnilloZp fields;
}Fields;

#ifdef __cplusplus
}
#endif

#endif
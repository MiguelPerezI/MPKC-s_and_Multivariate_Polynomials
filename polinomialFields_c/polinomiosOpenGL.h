#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include <stdarg.h>
#include "Arista.h"
#include "vector.h"

#ifndef _AnilloOpenGL_
#define _AnilloOpenGL_

#ifdef __cplusplus
extern "C" {
#endif

struct AnilloZp {
	int id;
	int mod;
	MatrixInt linearSpace;
	MatrixV latticeSpace;
	MatrixV	vectorSpace;
	MatrixInt addAuxMat;
	MatrixInt multAuxMat;
};

void initAnilloZp(struct AnilloZp * AnilloZp, int id, int mod);
void printAnilloZp(struct AnilloZp anillo);

typedef struct _PolinomioZp_{

	int mod;
	int grado;
	int * a;
}PolinomioZp;

void initPolinomioZp(PolinomioZp * p, int mod, int grado, ...); 
void printPolinomioZp(PolinomioZp p);
PolinomioZp addPolinomioZp(PolinomioZp p, PolinomioZp q);
PolinomioZp subPolinomioZp(PolinomioZp p, PolinomioZp q);
PolinomioZp vecToPolinomioZp2D(Vector p, int mod);
Vector PolinomioZpToVec(PolinomioZp p);

#ifdef __cplusplus
}
#endif

#endif
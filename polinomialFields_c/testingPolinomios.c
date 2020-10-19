#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "polinomios.h"
#include "Matrix.h"
#include "vector.h"
#include <stdarg.h>

struct AnilloZp Z3;
PolinomioZp p;
PolinomioZp q;

void main() {

	printf("\nTesting Polinomial structure ------ >\n\n");
	printf("Lets begin by creating our Ring R = Z3: \n");
	int id = 3;
	int mod = 3;

	initAnilloZp(&Z3, id, mod);
	printAnilloZp(Z3);

	printf("\n\n");
	initPolinomioZp(&p, mod, 3, 1, 2, 1);
	initPolinomioZp(&q, mod, 3, 0, 1, 1);
	printPolinomioZp(p);
	printf("\n");
	printPolinomioZp(q);

	PolinomioZp ret = multPolinomioZp(p, q);
	printf("\n\n");
	printPolinomioZp(ret);
	printf("\n");

	Vector v;
	v = PolinomioZpToVec(ret);
	printVector(v, 0);

	printf("\n\n\n");
}

void printPolinomioZp(PolinomioZp p) {

	int i;
	for (i = 0; i < p.grado + 1; i++) {

		if (i == 0) 
			printf(" %d", p.a[i]);
		else 
			printf("+ %d(x^%d)", p.a[i], i);
	}
}

void initAnilloZp(struct AnilloZp * anillo, int id, int mod) {

	printf("Defining a ring structure R = Z%d ------ >\n", mod);
	anillo->id = id;
	anillo->mod = mod;
	anillo->linearSpace = creaEspacioMatrixInt(1, mod);
	anillo->latticeSpace = creaEspacioMatrixV(mod, mod);
	anillo->addAuxMat = creaEspacioMatrixInt(mod, mod);
	anillo->multAuxMat = creaEspacioMatrixInt(mod, mod);
	anillo->vectorSpace = creaEspacioMatrixV(mod, mod);

	int i, j;
	for (i = 0; i < 1; i++) 
		for (j = 0; j < mod; j++) 
			anillo->linearSpace.A[i][j] = j;

	for (i = 0; i < mod; i++) 
		for (j = 0; j < mod; j++) {
			double i0 = i;
			double j0 = j;
			vectorGo(&anillo->latticeSpace.A[i][j], 2, i0, j0);
		}
}

void printAnilloZp(struct AnilloZp anillo) {

	printf("\n\n-----------------------------------\n");
	printf("Ring R has mod := %d, so R = Z%d.\n", anillo.mod, anillo.mod);

	printf("\n---> Z%d = {", anillo.mod);
	int i, j;
	for (i = 0; i < 1; i++) 
		for (j = 0; j < anillo.mod; j++) 
			printf(" %d", anillo.linearSpace.A[i][j]);
	printf(" }\n\n");

	printf("\n---> Z%dxZ%d = {\n\n", anillo.mod, anillo.mod);
	for (i = 0; i < anillo.mod; i++) {
		for (j = 0; j < anillo.mod; j++) {
			printf("	");
			printVector(anillo.latticeSpace.A[i][j], 0);
		}
		printf("\n\n");
	}
	printf(" }\n\n");
}

void initPolinomioZp(PolinomioZp * p, int mod, int grado, ...) {

	va_list list;
	p->grado = grado - 1;
	p->mod = mod;
	int i;

	p->a = (int *) malloc (grado * sizeof(int));

	va_start(list, grado);
	for (i = 0; i < grado; i++) {
		p->a[i] = va_arg(list, int);
		p->a[i] = p->a[i] % mod;
	}

	va_end(list);
}

PolinomioZp addPolinomioZp(PolinomioZp p, PolinomioZp q) {

	PolinomioZp ret = {
		grado : p.grado + q.grado + 1,
		mod : p.mod,
		a : NULL
	};

	if (p.mod == q.mod) {
		ret.mod = p.mod;
		if (p.grado == q.grado) {
			ret.grado = p.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));

			int i;
			for (i = 0; i < ret.grado + 1; i++)
				ret.a[i] = (p.a[i] + q.a[i])%ret.mod;
		}	
	}

	return ret;
}

PolinomioZp subPolinomioZp(PolinomioZp p, PolinomioZp q) {

	PolinomioZp ret = {
		grado : p.grado + q.grado + 1,
		mod : p.mod,
		a : NULL
	};

	if (p.mod == q.mod) {
		ret.mod = p.mod;
		if (p.grado == q.grado) {
			ret.grado = p.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));

			int i;
			for (i = 0; i < ret.grado + 1; i++)
				ret.a[i] = (p.a[i] - q.a[i])%ret.mod;
		}	
	}

	return ret;
}

PolinomioZp vecToPolinomioZp2D(Vector p, int mod) {

	int v0 = p.v[0];
	int v1 = p.v[1];

	PolinomioZp ret = {mod : mod, a : NULL};

	if (v1 == 0) {
		ret.grado = 0;

		ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
		ret.a[0] = v0%mod;
	} else {
		ret.grado = 1;

		ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
		ret.a[0] = v0%mod;
		ret.a[1] = v1%mod;
	}

	return ret;

}

Vector PolinomioZpToVec(PolinomioZp p) {

	double v0 = p.a[0];
	double v1 = p.a[1];
	Vector ret;
	vectorGo(&ret, 2, v0, v1);

	return ret;
}
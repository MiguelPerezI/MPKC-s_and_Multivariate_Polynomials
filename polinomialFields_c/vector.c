#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

void vectorGo(Vector * V, int count, ...) {

	va_list list;
	V->n = count;
	V->auxI = 0;
	V->auxJ = 0;
	V->v = (double *) malloc (count * sizeof(double));
	V->w = (double *) malloc (count * sizeof(double));
	int i;

	va_start(list, count);
	/**/
	/**/	for (int i = 0; i < count; i++)
	/**/		V->v[i] = va_arg(list, double);
	/**/
	va_end(list);

	for (int i = 0; i < count; i++)
		V->w[i] = V->v[i];

	double norma = 0;
	for (i = 0; i < V->n; i++)
		norma += V->v[i] * V->v[i];

	double normaW = 0;
	for (i = 0; i < V->n; i++)
		normaW += V->w[i] * V->w[i];

	V->norma = sqrt(norma);
	V->normaW = sqrt(normaW);
}

Vector vector3DFast(double x, double y, double z) {

	Vector V;
	vectorGo(&V, 3, x, y, z);
	return V;
}

Vector getSubVector(Vector a) {

	Vector ret;
	vectorGo(&ret, 3, a.w[0], a.w[1], a.w[2]);

	return ret;
}

Vector getSubVector00(Vector * a) {

	Vector ret;
	vectorGo(&ret, 3, a->w[0], a->w[1], a->w[2]);

	return ret;
}

void printVector(Vector V, int k) {

	printf("(");
	int i;
	for (i = 0; i < V.n; i++)
		if (k == 0) {
			if (i < V.n - 1) printf(" %lg,", V.v[i]);
			else printf(" %lg)", V.v[i]);}
		else {
			if (i < V.n - 1) printf(" %lg,", V.w[i]);
			else printf(" %lg)", V.w[i]);}
	//printf("\n");
}

void updateVectorType1(Vector * p, Vector w) {

	p->n = w.n;
	for (p->auxI = 0; p->auxI < p->n; p->auxI++) {
		p->v[p->auxI] = w.v[p->auxI];
		p->w[p->auxI] = p->v[p->auxI];
	}
	p->norma = w.norma;
	p->normaW = w.normaW;

}

void updateVectorR2(Vector * p, double x, double y) {

	if (p->n != 2) printf("\n\nWarning vector not updated.\n\n");
	else {
		p->v[0] = x;
		p->v[1] = y;
		p->w[0] = x;
		p->w[1] = y;
	}

	p->norma = sqrt((x*x) + (y*y));
	p->normaW = sqrt((x*x) + (y*y));
}

void updateVectorR3(Vector * p, double x, double y, double z) {

	if (p->n != 3) printf("\n\nWarning vector not updated.\n\n");
	else {
		p->v[0] = x;
		p->v[1] = y;
		p->v[2] = z;

		p->w[0] = x;
		p->w[1] = y;
		p->w[2] = z;
	}

	p->norma = sqrt((x*x) + (y*y) + (z*z));
	p->normaW = sqrt((x*x) + (y*y) + (z*z));
}

void updateVectorR4(Vector * p, double x, double y, double z, double t) {

	if (p->n != 4) printf("\n\nWarning vector not updated.\n\n");
	else {
		p->v[0] = x;
		p->v[1] = y;
		p->v[2] = z;
		p->v[3] = t;

		p->w[0] = x;
		p->w[1] = y;
		p->w[2] = z;
		p->w[3] = t;
	}

	p->norma = sqrt((x*x) + (y*y) + (z*z) + (t*t));
	p->normaW = sqrt((x*x) + (y*y) + (z*z) + (t*t));
}

void addVector(Vector * p, Vector q) {

	if (p->n == q.n)
		for (p->auxI = 0; p->auxI < p->n; p->auxI++)
			p->w[p->auxI] = p->v[p->auxI] + q.v[p->auxI];
	else printf("\n\nDIMENSION ERROR\n\n");
}

Vector addVectorGo(Vector p, Vector q) {

	Vector ret = {
					n : p.n,
					auxI : 0,
					auxJ : 0
				};

	ret.v = (double *) malloc (p.n * sizeof(double));
	ret.w = (double *) malloc (p.n * sizeof(double));
	int i;

	for (i = 0; i < p.n; i++)
		ret.v[i] = p.v[i] + q.v[i];

	for (int i = 0; i < p.n; i++)
		ret.w[i] = ret.v[i];

	double norma = 0;
	for (i = 0; i < ret.n; i++)
		norma += ret.v[i] * ret.v[i];

	ret.norma = sqrt(norma);

	double normaW = 0;
	for (i = 0; i < ret.n; i++)
		normaW += ret.w[i] * ret.w[i];

	ret.normaW = sqrt(normaW);

	return ret;
}

void subVector(Vector * p, Vector q) {

	if (p->n == q.n) {
		for (p->auxI = 0; p->auxI < p->n; p->auxI++)
			p->w[p->auxI] = p->v[p->auxI] - q.v[p->auxI];

		p->normaW = 0;
		for (p->auxI = 0; p->auxI < p->n; p->auxI++)
			p->normaW += (p->w[p->auxI])*(p->w[p->auxI]);
		p->normaW = sqrt(p->normaW);
	}
	else printf("\n\nDIMENSION ERROR\n\n");
}

Vector subVectorGo(Vector p, Vector q) {

	Vector ret = {
					n : p.n,
					auxI : 0,
					auxJ : 0
				};

	ret.v = (double *) malloc (p.n * sizeof(double));
	ret.w = (double *) malloc (p.n * sizeof(double));
	int i;

	for (i = 0; i < p.n; i++)
		ret.v[i] = p.v[i] - q.v[i];

	for (int i = 0; i < p.n; i++)
		ret.w[i] = ret.v[i];

	double norma = 0;
	for (i = 0; i < ret.n; i++)
		norma += ret.v[i] * ret.v[i];

	ret.norma = sqrt(norma);

	double normaW = 0;
	for (i = 0; i < ret.n; i++)
		normaW += ret.w[i] * ret.w[i];

	ret.normaW = sqrt(normaW);

	return ret;
}

void updateScaleVector(double a, Vector * p) {

	for (p->auxI = 0; p->auxI < p->n; p->auxI++)
		p->w[p->auxI] = a * p->v[p->auxI];
}

Vector scaleVectorGo(double a, Vector p) {

	Vector ret = {
					n : p.n,
					auxI : 0,
					auxJ : 0
				};

	ret.v = (double *) malloc (p.n * sizeof(double));
	ret.w = (double *) malloc (p.n * sizeof(double));
	int i;

	for (i = 0; i < p.n; i++)
		ret.v[i] = a * p.v[i];

	for (int i = 0; i < p.n; i++)
		ret.w[i] = ret.v[i];

	double norma = 0;
	for (i = 0; i < ret.n; i++)
		norma += ret.v[i] * ret.v[i];

	ret.norma = sqrt(norma);

	double normaW = 0;
	for (i = 0; i < ret.n; i++)
		normaW += ret.w[i] * ret.w[i];

	ret.normaW = sqrt(normaW);

	return ret;
}

double distanceVector(Vector p, Vector q) {

	subVector(&p, q);
	return p.normaW;
}

void cruzVectorR3(Vector * p, Vector q) {

	if (p->n == q.n && p->n == 3) {
		p->w[0] = ( p->v[1] * q.v[2]) - (p->v[2] * q.v[1]);
		p->w[1] = (-p->v[0] * q.v[2]) + (p->v[2] * q.v[0]);
		p->w[2] = ( p->v[0] * q.v[1]) - (p->v[1] * q.v[0]);

		p->normaW = 0;
		for (p->auxI = 0; p->auxI < p->n; p->auxI++)
			p->normaW += (p->w[p->auxI])*(p->w[p->auxI]);
		p->normaW = sqrt(p->normaW);
	}
	else printf("\n\nDIMENSION ERROR\n\n");
}

void cruzVectorR3P(Vector * p, Vector q) {

	if (p->n == q.n && p->n == 3) {
		p->w[0] = ( p->w[1] * q.v[2]) - (p->w[2] * q.v[1]);
		p->w[1] = (-p->w[0] * q.v[2]) + (p->w[2] * q.v[0]);
		p->w[2] = ( p->w[0] * q.v[1]) - (p->w[1] * q.v[0]);

		p->normaW = 0;
		for (p->auxI = 0; p->auxI < p->n; p->auxI++)
			p->normaW += (p->w[p->auxI])*(p->w[p->auxI]);
		p->normaW = sqrt(p->normaW);
	}
	else printf("\n\nDIMENSION ERROR\n\n");
}

void unitVector(Vector * p) {

	updateScaleVector(1/p->norma, p);
}

void vectorCapsuleGo( struct VectorCapsule * ret, int n) {

	ret->n = n;
	ret->A = (Vector *) malloc (n * sizeof(Vector));
}

int equalDouble(double a, double b) {

	if (sqrt((a-b) * (a-b)) < 1e-28) return 1;
	else return 0;
}

Vector centerOfMass(int count, ...) {

	va_list list;
	Vector ret;
	vectorGo(&ret, 3, 0, 0, 0);

	va_start(list, count);
	/**/
	/**/	for (int i = 0; i < count; i++)
	/**/		ret = addVectorGo(ret, va_arg(list, Vector));
	/**/
	va_end(list);

	double aa = 1/(count);
	ret = scaleVectorGo(aa, ret);
	return ret;
}

Vector dilateVector(Vector a, Vector b, double lambda) {

	Vector ret;
	ret = subVectorGo(a, b);
	ret = scaleVectorGo(lambda, ret);
	ret = addVectorGo(ret, b);

	return ret;
}
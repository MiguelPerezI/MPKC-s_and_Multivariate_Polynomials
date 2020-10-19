#include <math.h>
#include <GL/glut.h>
#include "vector.h"

#ifndef _ARISTA_
#define _ARISTA_

#ifdef __cplusplus
extern "C" {
#endif

/**//**//**//**//**//**//**//**//**//**//**/
/*FACET UTILITIES*/
/**/
/**/
struct facet {
	
	Vector a;
	Vector b;
	Vector c;
	Vector normal;

	Vector aPrime;
	Vector bPrime;
	Vector cPrime;
	Vector normalPrime;

	Vector resta1;
	Vector resta2;
};

void facet(struct facet * f, Vector x, Vector y, Vector z);
void updateFacet(struct facet * f, Vector new_a, Vector new_b, Vector new_c);
void renderFacet(struct facet sim, struct rotationMats U, int mod);

/*FACET STORAGE*/
typedef struct _matrixFacet_{
		int m, n;
		struct facet **A;
	} MatrixFacet; 

MatrixFacet creaMatrixFacet(int m, int n);

/**//**//**//**//**//**//**//**//**//**//**/
/*ARISTA UTILITIES*/
struct Arista {
	Vector base;
	Vector head;
	double width;
	struct VectorCapsule points;
	MatrixFacet mesh;

	Vector D;

	Vector h0;
	Vector h1;
	Vector h2;
	Vector h3;
	double longitud;

	struct rotationMats Rz_phi1;
	struct rotationMats Ry_teta1;
	struct rotationMats Rz_phi2;
	struct rotationMats Ry_teta2;

	Vector help;
};

void aristaGo(struct Arista * arista, Vector a, Vector b, double width);
void aristaSet(struct Arista * arista, Vector a, Vector b, double width);
void renderArista(struct Arista arista, struct rotationMats U);
void aristaUpdate(struct Arista * arista, Vector a, Vector b, double width);
void updateArista(struct Arista * arista, Vector a, Vector b, double width);

typedef struct _MatrixArista_{
	int m, n;
	struct Arista **A;
}MatrixArista;

MatrixArista creaEspacioMatrixArista(int m, int n);

typedef struct _MatrixAristaList_{
		int n;
		MatrixArista * m;
	} MatrixAristaList;

MatrixAristaList initMatrixAristaList(int n);

struct Arista dilateArista(struct Arista arista, Vector d, double lambda);
struct Arista rotateArista(struct Arista arista, struct rotationMats A);

struct VecindadCubica {

	Vector center;
	double radius;
	MatrixFacet mesh;
	int color;
};

void initVecindadCubica(struct VecindadCubica * cubo, Vector center, double radius);
void renderVecindadCubica (struct VecindadCubica cubo, struct rotationMats U);
void updateVecindadCubica(struct VecindadCubica * cubo, Vector newCenter, double newRadius);

typedef struct _MatrixVecindadCubica_{
	int m, n;
	struct VecindadCubica **A;
}MatrixVecindadCubica;

MatrixVecindadCubica creaEspacioMatrixVecindadCubica(int m, int n);

#ifdef __cplusplus
}
#endif

#endif

#include "vector.h"
#include "Matrix.h"
#include "Arista.h"

#ifndef _HILBERT_
#define _HILBERT_

#ifdef __cplusplus
extern "C" {
#endif

struct HilbertPiece {

	Vector a, b, c, d;
	Vector aPrime, bPrime, cPrime, dPrime;
	int id;
	struct Arista A0, A1, A2, A3;
	struct Arista H0, H1, H2;
	Vector center;
	double width;
	Vector f;
	Vector l;

};

void HilbertPieceGo(struct HilbertPiece * hilbert, Vector a, Vector b, Vector c, Vector d); 
void renderHilbertPiece(struct HilbertPiece hilbert, struct rotationMats U);
struct HilbertPiece dilateHilbertPiece(struct HilbertPiece hilbert, Vector base, double lambda);
struct HilbertPiece rotateHilbertPiece(struct HilbertPiece hilbert, struct rotationMats A);

typedef struct _MatrixHilbertPiece_{

	int m, n;
	struct HilbertPiece * * A;
	Vector f;
	Vector l;
}MatrixHilbertPiece;

MatrixHilbertPiece MatrixHilbertPieceGo(int m, int n);

typedef struct _MatrixHilbertPieceList_{
		int n;
		MatrixHilbertPiece * m;
	} MatrixHilbertPieceList;

MatrixHilbertPieceList initMatrixHilbertList(int n);

struct HilbertCurve {

	int order;
	Vector v0, v1, v2, v3;
	MatrixHilbertPieceList hilbertList; 
	Vector center;
	struct rotationMats rotAxe0;
	struct rotationMats rotAxe1;
	Vector aux;
	struct Arista auxA;
	MatrixArista conection;
	MatrixAristaList prime;
};

void initHilbertCurve(
						struct HilbertCurve * hilbert, 
						Vector v0, 
						Vector v1,
						Vector v2, 
						Vector v3, int n);

void renderHilbertCurve(struct HilbertCurve hilbert, struct rotationMats U);

#ifdef __cplusplus
}
#endif

#endif
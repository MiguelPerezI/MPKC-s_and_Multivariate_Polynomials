#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdbool.h>
#include "vector.h"
#include "Matrix.h"
#include "Arista.h"
#include "Hilbert.h"

void HilbertPieceGo(struct HilbertPiece * hilbert, Vector a, Vector b, Vector c, Vector d) {

	hilbert->center = centerOfMass(4, a, b, c, d);
	hilbert->a = a;
	hilbert->b = b;
	hilbert->c = c;
	hilbert->d = d;
	hilbert->aPrime = dilateVector(a, hilbert->center, 0.5);
	hilbert->bPrime = dilateVector(b, hilbert->center, 0.5);
	hilbert->cPrime = dilateVector(c, hilbert->center, 0.5);
	hilbert->dPrime = dilateVector(d, hilbert->center, 0.5);

	hilbert->width = 0.02;
	hilbert->id = 0;
	aristaSet(&hilbert->A0, hilbert->a, hilbert->b, hilbert->width);
	aristaSet(&hilbert->A1, hilbert->b, hilbert->c, hilbert->width);
	aristaSet(&hilbert->A2, hilbert->c, hilbert->d, hilbert->width);
	aristaSet(&hilbert->A3, hilbert->d, hilbert->a, hilbert->width);

	aristaSet(&hilbert->H0, hilbert->aPrime, hilbert->bPrime, hilbert->width);
	aristaSet(&hilbert->H1, hilbert->bPrime, hilbert->cPrime, hilbert->width);
	aristaSet(&hilbert->H2, hilbert->cPrime, hilbert->dPrime, hilbert->width);
}

struct HilbertPiece dilateHilbertPiece(struct HilbertPiece hilbert, Vector base, double lambda) {

	struct HilbertPiece ret;
	ret.a = dilateVector(hilbert.a, base, lambda);
	ret.b = dilateVector(hilbert.b, base, lambda);
	ret.c = dilateVector(hilbert.c, base, lambda);
	ret.d = dilateVector(hilbert.d, base, lambda);

	ret.aPrime = dilateVector(hilbert.aPrime, base, lambda);
	ret.bPrime = dilateVector(hilbert.bPrime, base, lambda);
	ret.cPrime = dilateVector(hilbert.cPrime, base, lambda);
	ret.dPrime = dilateVector(hilbert.dPrime, base, lambda);

	ret.width = hilbert.width * lambda * 1.8;

	aristaSet(&ret.A0, ret.a, ret.b, ret.width);
	aristaSet(&ret.A1, ret.b, ret.c, ret.width);
	aristaSet(&ret.A2, ret.c, ret.d, ret.width);
	aristaSet(&ret.A3, ret.d, ret.a, ret.width);

	aristaSet(&ret.H0, ret.aPrime, ret.bPrime, ret.width);
	aristaSet(&ret.H1, ret.bPrime, ret.cPrime, ret.width);
	aristaSet(&ret.H2, ret.cPrime, ret.dPrime, ret.width);

	return ret;
}

struct HilbertPiece rotateHilbertPiece(struct HilbertPiece hilbert, struct rotationMats A) {

	struct HilbertPiece ret;
	ret.a = rot3DAxe(&A, hilbert.a);
	ret.b = rot3DAxe(&A, hilbert.b);
	ret.c = rot3DAxe(&A, hilbert.c);
	ret.d = rot3DAxe(&A, hilbert.d);

	ret.aPrime = rot3DAxe(&A, hilbert.aPrime);
	ret.bPrime = rot3DAxe(&A, hilbert.bPrime);
	ret.cPrime = rot3DAxe(&A, hilbert.cPrime);
	ret.dPrime = rot3DAxe(&A, hilbert.dPrime);

	ret.width = hilbert.width;

	aristaSet(&ret.A0, ret.a, ret.b, ret.width);
	aristaSet(&ret.A1, ret.b, ret.c, ret.width);
	aristaSet(&ret.A2, ret.c, ret.d, ret.width);
	aristaSet(&ret.A3, ret.d, ret.a, ret.width);

	aristaSet(&ret.H0, ret.aPrime, ret.bPrime, ret.width);
	aristaSet(&ret.H1, ret.bPrime, ret.cPrime, ret.width);
	aristaSet(&ret.H2, ret.cPrime, ret.dPrime, ret.width);

	return ret;
}

void renderHilbertPiece(struct HilbertPiece hilbert, struct rotationMats U) {

	//renderArista(hilbert.A0, U);
	//renderArista(hilbert.A1, U);
	//renderArista(hilbert.A2, U);
	//renderArista(hilbert.A3, U);

	renderArista(hilbert.H0, U);
	renderArista(hilbert.H1, U);
	renderArista(hilbert.H2, U);
}

MatrixHilbertPiece MatrixHilbertPieceGo(int m, int n) {
	  MatrixHilbertPiece ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (struct HilbertPiece**) malloc (m * sizeof(struct HilbertPiece*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (struct HilbertPiece *) malloc (n * sizeof(struct HilbertPiece));
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

MatrixHilbertPieceList initMatrixHilbertPieceList(int n) {
	MatrixHilbertPieceList ret = {
						n : n,
						m : NULL
					};

	ret.m = (MatrixHilbertPiece *) malloc (n * sizeof(MatrixHilbertPiece));

	return ret;
}

void initHilbertCurve(
						struct HilbertCurve * hilbert, 
						Vector v0, 
						Vector v1,
						Vector v2, 
						Vector v3, int n) {

	hilbert->v0 = v0;
	hilbert->v1 = v1;
	hilbert->v2 = v2;
	hilbert->v3 = v3;
	hilbert->order = n;

	hilbert->center = centerOfMass(4, v0, v1, v2, v3);
	Vector v00 = dilateVector(v0, hilbert->center, 0.5);
	Vector v03 = dilateVector(v3, hilbert->center, 0.5);
	hilbert->aux = v03;

	//printVector(v00, 0);
	//printVector(v03, 0);

	struct rotationMats A, A1;
	vectorGo(&A.head, 3, v00.v[0], v00.v[1], 1.0);
	vectorGo(&A.base, 3, v00.v[0], v00.v[1], v00.v[2]);
	A = initAxeRotation(A.head, A.base, 0.5 * 3.1415);

	vectorGo(&A1.head, 3, v03.v[0], v03.v[1], 1.0);
	vectorGo(&A1.base, 3, v03.v[0], v03.v[1], v03.v[2]);
	aristaSet(&hilbert->auxA, A1.head, A1.base, 0.06);
	A1 = initAxeRotation(A1.head, A1.base,-0.5 * 3.1415);

	struct HilbertPiece auxPice;
	hilbert->hilbertList = initMatrixHilbertPieceList(hilbert->order + 1);
	hilbert->prime = initMatrixAristaList(hilbert->order + 1);
	hilbert->hilbertList.m[0] = MatrixHilbertPieceGo(1, 1);
	hilbert->conection = creaEspacioMatrixArista(hilbert->order+1, 3);

	HilbertPieceGo(&hilbert->hilbertList.m[0].A[0][0], hilbert->v0, hilbert->v1, hilbert->v2, hilbert->v3);	
	hilbert->hilbertList.m[0].f = hilbert->hilbertList.m[0].A[0][0].aPrime;
	hilbert->hilbertList.m[0].l = hilbert->hilbertList.m[0].A[0][0].dPrime;


	Vector first0 = dilateVector(hilbert->hilbertList.m[0].f, hilbert->v0, 0.5);
	first0 = rot3DAxe(&A, first0);

	Vector last0 = dilateVector(hilbert->hilbertList.m[0].l, hilbert->v0, 0.5);
	last0 = rot3DAxe(&A, last0);

	Vector first1 = dilateVector(hilbert->hilbertList.m[0].f, hilbert->v1, 0.5);
	Vector last1 = dilateVector(hilbert->hilbertList.m[0].l, hilbert->v1, 0.5);

	Vector first2 = dilateVector(hilbert->hilbertList.m[0].f, hilbert->v2, 0.5);
	Vector last2 = dilateVector(hilbert->hilbertList.m[0].l, hilbert->v2, 0.5);

	Vector first3 = dilateVector(hilbert->hilbertList.m[0].f, hilbert->v3, 0.5);
	first3 = rot3DAxe(&A1, first3);

	Vector last3 = dilateVector(hilbert->hilbertList.m[0].l, hilbert->v3, 0.5);
	last3 = rot3DAxe(&A1, last3);

	double width = hilbert->hilbertList.m[0].A[0][0].width;
	aristaSet(&hilbert->conection.A[0][0], first0, first1, width);
	aristaSet(&hilbert->conection.A[0][1], last1, first2, width);
	aristaSet(&hilbert->conection.A[0][2], last2, last3, width);

	hilbert->prime.m[0] = creaEspacioMatrixArista(1, 3);
	hilbert->prime.m[0].A[0][0] = hilbert->conection.A[0][0];
	hilbert->prime.m[0].A[0][1] = hilbert->conection.A[0][1];
	hilbert->prime.m[0].A[0][2] = hilbert->conection.A[0][2];

	int i;
	int pow = 1;
	int cycle = 1;

	if (n > 0) {

		while (cycle < n + 1) {

			pow *= 4;
			hilbert->hilbertList.m[cycle] = MatrixHilbertPieceGo(1, pow);
			hilbert->prime.m[cycle] = creaEspacioMatrixArista(pow, 3);
			
			int limit = hilbert->hilbertList.m[cycle-1].n;
			int counted = 0;
			int record;
			for (i = 0; i < limit; i++) {
				hilbert->hilbertList.m[cycle].A[0][i] = dilateHilbertPiece(hilbert->hilbertList.m[cycle-1].A[0][i], hilbert->v0, 0.5);
				hilbert->hilbertList.m[cycle].A[0][i] = rotateHilbertPiece(hilbert->hilbertList.m[cycle].A[0][i], A);
				hilbert->hilbertList.m[cycle].A[0][i].id = 0;			

				counted += 1;
			}
			int mmod = 0;
			for (i = 0; i < pow; i += 4) {
				hilbert->prime.m[cycle].A[i+0][0] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][0], hilbert->v0, 0.5);
				hilbert->prime.m[cycle].A[i+0][1] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][1], hilbert->v0, 0.5);
				hilbert->prime.m[cycle].A[i+0][2] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][2], hilbert->v0, 0.5);
	
				hilbert->prime.m[cycle].A[i+0][0] = rotateArista(hilbert->prime.m[cycle].A[i+0][0], A);
				hilbert->prime.m[cycle].A[i+0][1] = rotateArista(hilbert->prime.m[cycle].A[i+0][1], A);
				hilbert->prime.m[cycle].A[i+0][2] = rotateArista(hilbert->prime.m[cycle].A[i+0][2], A);
	
				hilbert->prime.m[cycle].A[i+1][0] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][0], hilbert->v1, 0.5);
				hilbert->prime.m[cycle].A[i+1][1] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][1], hilbert->v1, 0.5);
				hilbert->prime.m[cycle].A[i+1][2] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][2], hilbert->v1, 0.5);
	
				hilbert->prime.m[cycle].A[i+2][0] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][0], hilbert->v2, 0.5);
				hilbert->prime.m[cycle].A[i+2][1] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][1], hilbert->v2, 0.5);
				hilbert->prime.m[cycle].A[i+2][2] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][2], hilbert->v2, 0.5);
	
				hilbert->prime.m[cycle].A[i+3][0] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][0], hilbert->v3, 0.5);
				hilbert->prime.m[cycle].A[i+3][1] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][1], hilbert->v3, 0.5);
				hilbert->prime.m[cycle].A[i+3][2] = dilateArista(hilbert->prime.m[cycle-1].A[mmod][2], hilbert->v3, 0.5);
	
				hilbert->prime.m[cycle].A[i+3][0] = rotateArista(hilbert->prime.m[cycle].A[i+3][0], A1);
				hilbert->prime.m[cycle].A[i+3][1] = rotateArista(hilbert->prime.m[cycle].A[i+3][1], A1);
				hilbert->prime.m[cycle].A[i+3][2] = rotateArista(hilbert->prime.m[cycle].A[i+3][2], A1);
				mmod += 1;
			}

			for (i = 0; i < limit; i++) {
				hilbert->hilbertList.m[cycle].A[0][i + limit] = dilateHilbertPiece(hilbert->hilbertList.m[cycle-1].A[0][i], hilbert->v1, 0.5);
				hilbert->hilbertList.m[cycle].A[0][i + limit].id = 1;
				counted += 1;
			}

			for (i = 0; i < limit; i++) {
				hilbert->hilbertList.m[cycle].A[0][i + (2*limit)] = dilateHilbertPiece(hilbert->hilbertList.m[cycle-1].A[0][i], hilbert->v2, 0.5);
				hilbert->hilbertList.m[cycle].A[0][i + (2*limit)].id = 2;
				counted += 1;
			}

			for (i = 0; i < limit; i++) {
				hilbert->hilbertList.m[cycle].A[0][i + (3*limit)] = dilateHilbertPiece(hilbert->hilbertList.m[cycle-1].A[0][i], hilbert->v3, 0.5);
				hilbert->hilbertList.m[cycle].A[0][i + (3*limit)] = rotateHilbertPiece(hilbert->hilbertList.m[cycle].A[0][i + (3*limit)], A1);
				hilbert->hilbertList.m[cycle].A[0][i + (3*limit)].id = 3;
				counted += 1;
			}

			Vector primero0 = dilateVector(hilbert->hilbertList.m[cycle-1].f, hilbert->v0, 0.5);
			primero0 = rot3DAxe(&A, primero0);

			Vector ultimo0 = dilateVector(hilbert->hilbertList.m[cycle-1].l, hilbert->v0, 0.5);
			ultimo0 = rot3DAxe(&A, ultimo0);

			hilbert->hilbertList.m[cycle].f = ultimo0;

			Vector primero1 = dilateVector(hilbert->hilbertList.m[cycle-1].f, hilbert->v1, 0.5);
			Vector  ultimo1 = dilateVector(hilbert->hilbertList.m[cycle-1].l, hilbert->v1, 0.5);

			Vector primero2 = dilateVector(hilbert->hilbertList.m[cycle-1].f, hilbert->v2, 0.5);
			Vector  ultimo2 = dilateVector(hilbert->hilbertList.m[cycle-1].l, hilbert->v2, 0.5);

			Vector primero3 = dilateVector(hilbert->hilbertList.m[cycle-1].f, hilbert->v3, 0.5);
			primero3 = rot3DAxe(&A1, primero3);

			Vector ultimo3 = dilateVector(hilbert->hilbertList.m[cycle-1].l, hilbert->v3, 0.5);
			ultimo3 = rot3DAxe(&A1, ultimo3);

			hilbert->hilbertList.m[cycle].l = primero3;

			aristaSet(&hilbert->conection.A[cycle][0], primero0, primero1, width);
			aristaSet(&hilbert->conection.A[cycle][1], ultimo1, primero2, width);
			aristaSet(&hilbert->conection.A[cycle][2], ultimo2, ultimo3, width);

			cycle += 1;
		}
	}

}

void renderHilbertCurve(struct HilbertCurve hilbert, struct rotationMats U) {

	int i;
	for (i = 0; i < hilbert.hilbertList.m[3].n; i++) {
		renderHilbertPiece(hilbert.hilbertList.m[3].A[0][i], U);
	}

	renderArista(hilbert.conection.A[3][0], U);
	renderArista(hilbert.conection.A[3][1], U);
	renderArista(hilbert.conection.A[3][2], U);

	for (i = 0; i < 16; i++) {
		renderArista(hilbert.prime.m[2].A[i][0], U);
		renderArista(hilbert.prime.m[2].A[i][1], U);
		renderArista(hilbert.prime.m[2].A[i][2], U);
	}
} 
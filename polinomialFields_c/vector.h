#include <stdbool.h>

#ifndef _VECTOR_
#define _VECTOR_

#ifdef __cplusplus
extern "C" {
#endif

/*memory class*/
typedef struct _Vector_{
	int n;
	double * v;
	int auxI;
	int auxJ;
	double norma;
	double * w;
	double normaW;
}Vector;

void vectorGo(Vector * V, int count, ...);
Vector vector3DFast(double x, double y, double z);
Vector getSubVector(Vector a);
Vector getSubVector00(Vector * a);
void printVector(Vector V, int k);
void updateVectorType1(Vector * p, Vector w);
void updateVectorR2(Vector * p, double x, double y);
void updateVectorR3(Vector * p, double x, double y, double z);
void updateVectorR4(Vector * p, double x, double y, double z, double t);

void addVector(Vector * p, Vector q);
Vector addVectorGo(Vector p, Vector q);

void subVector(Vector * p, Vector q);
Vector subVectorGo(Vector p, Vector q);

void updateScaleVector(double a, Vector * p);
Vector scaleVectorGo(double a, Vector p);

double distanceVector(Vector p, Vector q);

void cruzVectorR3(Vector * p, Vector q);
void cruzVectorR3P(Vector * p, Vector q);

void unitVector(Vector * p);

struct VectorCapsule {

	int n;
	Vector * A;
};

void vectorCapsuleGo( struct VectorCapsule * ret, int n);

int equalDouble(double a, double b);
Vector centerOfMass(int count, ...);
Vector dilateVector(Vector a, Vector b, double lambda);

#ifdef __cplusplus
}
#endif

#endif

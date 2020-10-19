#include <stdbool.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"

#ifndef _TURTLE3D_
#define _TURTLE3D_

#ifdef __cplusplus
extern "C" {
#endif

struct Turtle3D {

	Vector head;
	Vector tail;
	double stepF;
	double angle;
	MatrixArista path;
	int counted;
	int Max;

	Vector preHeadRot;
	Vector preTailRot;
};

void initTurtle(struct Turtle * turtle, Vector b, Vector u, double theta, double angle, int Max);
void renderTurtle(struct Turtle turtle, struct rotationMats U);

#ifdef __cplusplus
}
#endif

#endif
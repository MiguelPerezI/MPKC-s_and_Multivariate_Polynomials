#include <stdbool.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"

#ifndef _TURTLE_
#define _TURTLE_

#ifdef __cplusplus
extern "C" {
#endif

struct Turtle {
	Vector head;
	Vector tail;
	double stepF;
	double angle;
	struct rotationMats A;
	struct rotationMats R;
	struct rotationMats L;
	MatrixArista path;
	MatrixV preMoves;
	int counted;
	int Max;
	int move;
	Vector K;

	struct VecindadCubica tHead;
	double thickness;

	struct rotationMats Rx;
	struct rotationMats Ry;
	struct rotationMats Rtt;
	Vector rotate;
	Vector axeHead;

	Vector preHead;
	Vector preTail;

	Vector preHeadRot;
	Vector preTailRot;
};

void initTurtle(struct Turtle * turtle, Vector b, Vector u, double theta, double angle, int Max);
void renderTurtle(struct Turtle turtle, struct rotationMats U);
void forwardTurtle(struct Turtle * turtle);
void rotateRightTurtle(struct Turtle * turtle);
void rotateLeftTurtle(struct Turtle * turtle);
void showTurtleHead(struct Turtle turtle, struct rotationMats U);
void rotXTurtle(struct Turtle * turtle);
void rotYTurtle(struct Turtle * turtle);
void rotTTTurtle(struct Turtle * turtle);
void forwardTurtleSpace(struct Turtle * turtle, double);
void saveTurtle(struct Turtle * turtle);
void goBackTurtle(struct Turtle * turtle);
void saveAxeRotTurtle(struct Turtle * turtle);
void goBackAxeRotTurtle(struct Turtle * turtle);
void rot1TTurtle(struct Turtle * turtle, double angle);
void jumpForwardTurtleSpace(struct Turtle * turtle);

#ifdef __cplusplus
}
#endif

#endif
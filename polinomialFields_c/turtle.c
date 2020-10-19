#include <math.h>
#include <stdio.h>
#include "vector.h"
#include "Matrix.h"
#include "Arista.h"
#include "turtle.h"

void initTurtle(struct Turtle * turtle, Vector b, Vector u, double stepF, double angle, int Max) {
	
	turtle->counted = 0;
	turtle->Max = Max;
	turtle->stepF = stepF;
	turtle->angle = angle;
	turtle->tail = b;
	vectorGo(&turtle->preTail, 3, b.v[0], b.v[1], b.v[2]);
	vectorGo(&turtle->preTailRot, 3, b.v[0], b.v[1], b.v[2]);
	Vector a = addVectorGo(b, u);
	vectorGo(&turtle->preHead, 3, a.v[0], a.v[1], a.v[2]);
	vectorGo(&turtle->preHeadRot, 3, a.v[0], a.v[1], a.v[2]);
	Vector w = scaleVectorGo(stepF, subVectorGo(a, b));
	w = addVectorGo(w, b);
	turtle->head = w;

	turtle->thickness = 0.05;
	initVecindadCubica(&turtle->tHead, turtle->tail, turtle->thickness);

	turtle->path = creaEspacioMatrixArista(1, turtle->Max);
	//aristaSet(&turtle->path.A[0][turtle->counted], turtle->head, turtle->tail, 0.03);

	vectorGo(&turtle->K, 3, turtle->tail.v[0], turtle->tail.v[1], 1.0);
}

void showTurtleHead(struct Turtle turtle, struct rotationMats U) {

	renderVecindadCubica(turtle.tHead, U);
}

void renderTurtle(struct Turtle turtle, struct rotationMats U) {
	int i;
	for (i = 0; i < turtle.Max; i++)
	renderArista(turtle.path.A[0][i], U);

}

void forwardTurtle(struct Turtle * turtle) {

	if (turtle->counted < turtle->Max) {
		aristaSet(&turtle->path.A[0][turtle->counted], turtle->head, turtle->tail, 0.03);
		turtle->counted += 1;
		Vector u = subVectorGo(turtle->head, turtle->tail);

		unitVector(&u);
		updateVectorR3(&u, u.w[0], u.w[1], u.w[2]);
		Vector a = addVectorGo(turtle->head, u);
		Vector w = scaleVectorGo(turtle->stepF, subVectorGo(a, turtle->head));
		w = addVectorGo(w, turtle->head);
		turtle->tail = turtle->head;

		turtle->head = w;
		turtle->thickness * 0.5;
		updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
	}
}

void forwardTurtleSpace(struct Turtle * turtle, double s) {

	if (turtle->counted < turtle->Max) {
		
		aristaSet(&turtle->path.A[0][turtle->counted], turtle->head, turtle->tail, 0.01);
		turtle->counted += 1;
		Vector u = subVectorGo(turtle->head, turtle->tail);

		unitVector(&u);
		updateVectorR3(&u, u.w[0], u.w[1], u.w[2]);
		Vector a = addVectorGo(turtle->head, u);
		Vector w = scaleVectorGo(turtle->stepF, subVectorGo(a, turtle->head));
		w = addVectorGo(w, turtle->head);
		turtle->tail = turtle->head;

		turtle->head = w;
		turtle->thickness * 0.5;
		updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
	}
}

void jumpForwardTurtleSpace(struct Turtle * turtle) {

	if (turtle->counted < turtle->Max) {
		
		//aristaSet(&turtle->path.A[0][turtle->counted], turtle->head, turtle->tail, 0.01);
		//turtle->counted += 1;
		Vector u = subVectorGo(turtle->head, turtle->tail);

		unitVector(&u);
		updateVectorR3(&u, u.w[0], u.w[1], u.w[2]);
		Vector a = addVectorGo(turtle->head, u);
		Vector w = scaleVectorGo(turtle->stepF, subVectorGo(a, turtle->head));
		w = addVectorGo(w, turtle->head);
		turtle->tail = turtle->head;

		turtle->head = w;
		turtle->thickness * 0.5;
		updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
	}
}

void saveTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->preHead, turtle->head.v[0], turtle->head.v[1], turtle->head.v[2]);
	updateVectorR3(&turtle->preTail, turtle->tail.v[0], turtle->tail.v[1], turtle->tail.v[2]);
}

void saveAxeRotTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->preHeadRot, turtle->head.v[0], turtle->head.v[1], turtle->head.v[2]);
	updateVectorR3(&turtle->preTailRot, turtle->tail.v[0], turtle->tail.v[1], turtle->tail.v[2]);
}

void goBackTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->head, turtle->preHead.v[0], turtle->preHead.v[1], turtle->preHead.v[2]);
	updateVectorR3(&turtle->tail, turtle->preTail.v[0], turtle->preTail.v[1], turtle->preTail.v[2]);
	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
}

void goBackAxeRotTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->head, turtle->preHeadRot.v[0], turtle->preHeadRot.v[1], turtle->preHeadRot.v[2]);
	updateVectorR3(&turtle->tail, turtle->preTailRot.v[0], turtle->preTailRot.v[1], turtle->preTailRot.v[2]);
	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
}

void rotateRightTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->K, turtle->tail.v[0], turtle->tail.v[1], 1.0);
	struct rotationMats A;
	A = initAxeRotation(turtle->K, turtle->tail, turtle->angle);
	Vector w;
	vectorGo(&w, 3, turtle->head.v[0], turtle->head.v[1], turtle->head.v[2]);
	w = rot3DAxe(&A, w);
	updateVectorR3(&turtle->head, w.v[0], w.v[1], w.v[2]);
}

void rotateLeftTurtle(struct Turtle * turtle) {

	updateVectorR3(&turtle->K, turtle->tail.v[0], turtle->tail.v[1], 1.0);
	struct rotationMats A;
	A = initAxeRotation(turtle->K, turtle->tail,-turtle->angle);
	Vector w;
	vectorGo(&w, 3, turtle->head.v[0], turtle->head.v[1], turtle->head.v[2]);
	w = rot3DAxe(&A, w);
	updateVectorR3(&turtle->head, w.v[0], w.v[1], w.v[2]);
}

void rotXTurtle(struct Turtle * turtle) {

	vectorGo(&turtle->axeHead, 3, turtle->tail.v[0] + 1.0, turtle->tail.v[1], turtle->tail.v[2]);
	turtle->Rx = initAxeRotation(turtle->axeHead, turtle->tail, 0.25 * 3.1415);

	turtle->head = rot3DAxe(&turtle->Rx, turtle->head);
	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);

}

void rotYTurtle(struct Turtle * turtle) {

	vectorGo(&turtle->axeHead, 3, turtle->tail.v[0], turtle->tail.v[1] + 1.0, turtle->tail.v[2]);
	turtle->Ry = initAxeRotation(turtle->axeHead, turtle->tail, 0.25 * 3.1415);

	turtle->head = rot3DAxe(&turtle->Ry, turtle->head);
	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);

}

void rotTTTurtle(struct Turtle * turtle) {
	//printVector(turtle->preTail, 0);
	
	turtle->Rtt = initAxeRotation(turtle->preHead, turtle->preTail, 0.25 * 3.1415);

	turtle->head = rot3DAxe(&turtle->Rtt, turtle->head);

	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
}

void rot1TTurtle(struct Turtle * turtle, double angle) {
	//printVector(turtle->preTailRot, 0);
	
	turtle->Rtt = initAxeRotation(turtle->preHeadRot, turtle->preTailRot, angle);

	turtle->head = rot3DAxe(&turtle->Rtt, turtle->head);

	updateVecindadCubica(&turtle->tHead, turtle->head, turtle->thickness);
}
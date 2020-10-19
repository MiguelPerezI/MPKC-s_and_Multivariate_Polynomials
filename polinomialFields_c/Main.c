#include <stdio.h>
#include "vector.h"
#include <stdarg.h>

Vector p, p0, p1;

int main(int argc, char **argv) {

	printf("**** Testing Various classes ****\n\n");

	/*Initializing Memory*/
	vectorGo( &p, 4, 1.0, 0.0, 0.0, 0.0);
	vectorGo(&p0, 3, 0.0, 0.0, 0.0);
	vectorGo(&p1, 3, 1.0, 0.0, 0.0);
	updateVectorType1(&p, p0);

	updateVectorR3(&p, 1.0, 1.0, 1.0);
	printVector(p, 0);
	printVector(p0, 0);

	Vector aa = subVectorGo(p, p0);
	//aa = scaleVectorGo(2.111, aa);
	unitVector(&aa);
	printVector(aa, 1);
	printf("normW := %lg\n", distanceVector(p, p0));

	printf("\n\n\n");
	return 0;
}
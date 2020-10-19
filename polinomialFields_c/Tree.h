#include <stdbool.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"

#ifndef _ARBOLES_
#define _ARBOLES_

#ifdef __cplusplus
extern "C" {
#endif

struct Leaf {

	MatrixV leafs;
	MatrixVecindadCubica cubicLeafs;

	Vector root;
};

void initLeafsInTree(struct Leaf * Leaf, MatrixV points, double leafSize);
void renderLeafsInTree(struct Leaf Leaf, struct rotationMats U);

#ifdef __cplusplus
}
#endif

#endif
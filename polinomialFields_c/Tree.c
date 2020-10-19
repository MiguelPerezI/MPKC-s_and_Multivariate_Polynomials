#include <stdbool.h>
#include <stdio.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"
#include "Tree.h"

void initLeafsInTree(struct Leaf * leaf, MatrixV points, double leafSize) {

	printf("--> Preparing memory space for leafs in leaf\n");
	leaf->leafs = creaEspacioMatrixV(points.m, points.n);
	//initVecindadCubica(&leaf->cubicLeafs, leaf->leafs.A[0][0], leafSize);
	leaf->cubicLeafs = creaEspacioMatrixVecindadCubica(points.m, points.n);
	int i, j;
	for (i = 0; i < points.m; i++)
		for (j = 0; j < points.n; j++)
			vectorGo(&leaf->leafs.A[i][j], 3, points.A[i][j].v[0], points.A[i][j].v[1], points.A[i][j].v[2]);

	for (i = 0; i < points.m; i++)
		for (j = 0; j < points.n; j++)
			initVecindadCubica(&leaf->cubicLeafs.A[i][j], leaf->leafs.A[i][j], leafSize);

}

void renderLeafsInTree(struct Leaf leaf, struct rotationMats U) {

	int i, j;
	for (i = 0; i < leaf.cubicLeafs.m; i++)
		for (j = 0; j < leaf.cubicLeafs.n; j++)
			renderVecindadCubica (leaf.cubicLeafs.A[i][j], U);
}
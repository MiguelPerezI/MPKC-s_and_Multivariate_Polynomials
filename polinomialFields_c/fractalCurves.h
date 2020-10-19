#include <stdbool.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"
#include "turtle.h"

#ifndef _FRACTALCURVES_
#define _FRACTALCURVES_

#ifdef __cplusplus
extern "C" {
#endif

struct KochFractal {
	
	int order;
	int axiom[8];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initKochFractal(struct KochFractal * koch, Vector b, Vector u, int order);
void initPath(struct KochFractal * koch);
void renderKochFractal(struct KochFractal koch, struct rotationMats U);

struct GosperFractal {
	
	int order;
	int axiom[15];
	int axiom0[15];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initGosperFractal(struct GosperFractal * gosper, Vector b, Vector u, int order);
void initPathGosper(struct GosperFractal * gosper);
void renderGosperFractal(struct GosperFractal gosper, struct rotationMats U);

struct HilbertFractal {
	
	int order;
	int axiom[11];
	int axiom0[11];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initHilbertFractal(struct HilbertFractal * hilbert, Vector b, Vector u, int order);
void initPathHilbert(struct HilbertFractal * hilbert);
void renderHilbertFractal(struct HilbertFractal hilbert, struct rotationMats U, int iter);

struct SierspinskiCurve {
	
	int order;
	int axiom[12];
	int axiom0[18];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initSierspinskiCurve(struct SierspinskiCurve * sier, Vector b, Vector u, int order);
void initPathSierspinskiCurve(struct SierspinskiCurve * sier);
void renderSierspinskiCurve(struct SierspinskiCurve sier, struct rotationMats U);

struct LevyCurve {
	
	int order;
	int axiom[6];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initLevyCurve(struct LevyCurve * levy, Vector b, Vector u, int order);
void initPathLevyCurve(struct LevyCurve * levy);
void renderLevyCurve(struct LevyCurve levy, struct rotationMats U, int iter);

struct DragonCurve {
	
	int order;
	int axiom[5];
	int axiom0[5];
	struct Turtle turtle;
	MatrixIntList grammar;
	int length;
};

void initDragonCurve(struct DragonCurve * dragon, Vector b, Vector u, int order);
void initPathDragonCurve(struct DragonCurve * dragon);
void renderDragonCurve(struct DragonCurve dragon, struct rotationMats U, int iter);

#ifdef __cplusplus
}
#endif

#endif
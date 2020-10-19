#include <stdio.h>
#include "vector.h"
#include "Matrix.h"
#include <math.h>
#include "Arista.h"
#include "turtle.h"
#include "fractalCurves.h"

//////////////////////////
//						//
//		KOCH CURVE 		//
//					   	//
//////////////////////////

void initKochFractal(struct KochFractal * koch, Vector b, Vector u, int order) {

	int aux = 1;
	int k;

	koch->order = order;
	//printf("Preparing arista size:\n");
	for (k = 0; k < koch->order; k++) {
		aux = aux * 4;
		//printf("%d \n", aux);
	}

	//printf("\n\nNumber of aristas := %d\n\n", aux);
	initTurtle(&koch->turtle, b, u, 0.01, 0.33 * 3.1415, aux);

	//0 -> F
	//1 -> +
	//2 -> -
	//printf("Key:\n");
	//printf("0 -> F\n");
	//printf("1 -> +\n");
	//printf("2 -> -\n\nAxiom:\n");

	koch->axiom[0] = 0;
	koch->axiom[1] = 1;
	koch->axiom[2] = 0;
	koch->axiom[3] = 2;
	koch->axiom[4] = 2;
	koch->axiom[5] = 0;
	koch->axiom[6] = 1;
	koch->axiom[7] = 0;

	int i;
	//for (i = 0; i < 8; i++)
		//printf(" %d", koch->axiom[i]);

	//printf("\n\n\n");

}

void initPath(struct KochFractal * koch) {

	koch->grammar = initMatrixIntList(koch->order);
	koch->grammar.M[0] = creaEspacioMatrixInt(1, 8);
	koch->grammar.M[0].A[0][0] = 0;
	koch->grammar.M[0].A[0][1] = 1;
	koch->grammar.M[0].A[0][2] = 0;
	koch->grammar.M[0].A[0][3] = 2;
	koch->grammar.M[0].A[0][4] = 2;
	koch->grammar.M[0].A[0][5] = 0;
	koch->grammar.M[0].A[0][6] = 1;
	koch->grammar.M[0].A[0][7] = 0; 

	if (koch->order > 1) 
	{
		int num = 8;
		int j;
		for (j = 1; j < koch->order; j++) {
			num *= 4;
			num += 4;
			koch->grammar.M[j] = creaEspacioMatrixInt(1, num);
		}

		//printf("---> Building Memory := %d\n\n\n", koch->grammar.M[2].n);

		int i;
		int cycle;

		for (cycle = 1; cycle < koch->order; cycle++) {

			int c = 0;
			int record = 0;

			for (i = 0; i < 8; i++) {
				if (koch->axiom[i] == 0) {

					for (j = 0; j < koch->grammar.M[cycle-1].n; j++) {
						koch->grammar.M[cycle].A[0][j + record] = koch->grammar.M[cycle-1].A[0][j];
						c += 1;
					}
				}
	
				if (koch->axiom[i] == 1) {
					koch->grammar.M[cycle].A[0][c] = 1;
					c += 1;}
	
				if (koch->axiom[i] == 2) {
					koch->grammar.M[cycle].A[0][c] = 2;
					c += 1;	}
	
				record = c;
			}
		}

	}

	int i, j;

	for (i = 0; i < koch->order; i++) {
		for (j = 0; j < koch->grammar.M[i].n; j++){
			//printf(" %d", koch->grammar.M[i].A[0][j]);
		}
		//printf("\n\n");
	}

	for (i = 0; i < koch->grammar.M[koch->order-1].n; i++) {
		if (koch->grammar.M[koch->order-1].A[0][i] == 0) {
			forwardTurtle(&koch->turtle);
			//printf("%d ", koch->grammar.M[koch->order-1].A[0][i]);
		}
		if (koch->grammar.M[koch->order-1].A[0][i] == 1) {
			rotateRightTurtle(&koch->turtle);
			//printf("%d ", koch->grammar.M[koch->order-1].A[0][i]);
		}
		if (koch->grammar.M[koch->order-1].A[0][i] == 2) {
			rotateLeftTurtle(&koch->turtle);
			//printf("%d ", koch->grammar.M[koch->order-1].A[0][i]);
		}
	}


	//printf("\n\n\n");
}

void renderKochFractal(struct KochFractal koch, struct rotationMats U) {

	int i;
	for (i = 0; i < koch.turtle.Max; i++)
		renderArista(koch.turtle.path.A[0][i], U);
}

//////////////////////////
//						//
//	   GOSPER CURVE 	//
//					   	//
//////////////////////////

void initGosperFractal(struct GosperFractal * gosper, Vector b, Vector u, int order) {

	int aux = 1;
	int k;

	gosper->order = order;
	//printf("Preparing arista size:\n");
	for (k = 0; k < gosper->order; k++) {
		aux = aux * 7;
		//printf("%d \n", aux);
	}

	//printf("\n\nNumber of aristas := %d\n\n", aux);
	initTurtle(&gosper->turtle, b, u, 0.04, 0.33 * 3.1415, aux);

	//0 -> F
	//1 -> +
	//2 -> -
	//printf("Key:\n");
	//printf("0 -> F\n");
	//printf("1 -> G\n");
	//printf("2 -> +\n");
	//printf("3 -> -\n\nAxiom:\n");

	gosper->axiom[0] = 0;	gosper->axiom0[0] = 2;
	gosper->axiom[1] = 3;	gosper->axiom0[1] = 0;
	gosper->axiom[2] = 1;	gosper->axiom0[2] = 3;
	gosper->axiom[3] = 3;	gosper->axiom0[3] = 1;
	gosper->axiom[4] = 3;	gosper->axiom0[4] = 1;
	gosper->axiom[5] = 1;	gosper->axiom0[5] = 3;
	gosper->axiom[6] = 2;	gosper->axiom0[6] = 3;
	gosper->axiom[7] = 0;	gosper->axiom0[7] = 1;
	gosper->axiom[8] = 2;	gosper->axiom0[8] = 3;
	gosper->axiom[9] = 2;	gosper->axiom0[9] = 0;
	gosper->axiom[10] = 0;	gosper->axiom0[10] = 2;
	gosper->axiom[11] = 0;	gosper->axiom0[11] = 2;
	gosper->axiom[12] = 2;	gosper->axiom0[12] = 0;
	gosper->axiom[13] = 1;	gosper->axiom0[13] = 2;
	gosper->axiom[14] = 3;	gosper->axiom0[14] = 1;

}

void initPathGosper(struct GosperFractal * gosper) {

	gosper->grammar = initMatrixIntList(gosper->order);
	//printf("Order %d Gosper Curve:\n", gosper->order);
	gosper->grammar.M[0] = creaEspacioMatrixInt(1, 15);

	gosper->grammar.M[0].A[0][0] = 0;
	gosper->grammar.M[0].A[0][1] = 3;
	gosper->grammar.M[0].A[0][2] = 1;
	gosper->grammar.M[0].A[0][3] = 3;
	gosper->grammar.M[0].A[0][4] = 3;
	gosper->grammar.M[0].A[0][5] = 1;
	gosper->grammar.M[0].A[0][6] = 2;
	gosper->grammar.M[0].A[0][7] = 0;
	gosper->grammar.M[0].A[0][8] = 2;
	gosper->grammar.M[0].A[0][9] = 2;
	gosper->grammar.M[0].A[0][10] = 0;
	gosper->grammar.M[0].A[0][11] = 0;
	gosper->grammar.M[0].A[0][12] = 2;
	gosper->grammar.M[0].A[0][13] = 1;
	gosper->grammar.M[0].A[0][14] = 3;

	if (gosper->order > 1) {

		int num = 15;
		int j;
		for (j = 1; j < gosper->order; j++) {
			num *= 7;
			num += 8;
			gosper->grammar.M[j] = creaEspacioMatrixInt(1, num);
		}

		//for (j = 0; j < gosper->order; j++)
		//	printf("---> Building Memory M[%d]:= %d\n", j, gosper->grammar.M[j].n);


		int i;
		int cycle;

		for (cycle = 1; cycle < gosper->order; cycle++) {
			int c = 0;
			int pivote = 0;

			//Leemos la pila anterior
			for (i = 0; i < gosper->grammar.M[cycle-1].n; i++) {

				//revisamos por F en la pila anterior
				if (gosper->grammar.M[cycle-1].A[0][i] == 0) {
					for (j = 0; j < 15; j++) {
						gosper->grammar.M[cycle].A[0][j + pivote] = gosper->axiom[j];
						c += 1;
					}
				}
			
				//revisamos por G en la pila anterior
				if (gosper->grammar.M[cycle-1].A[0][i] == 1) {
					for (j = 0; j < 15; j++) {
						gosper->grammar.M[cycle].A[0][j + pivote] = gosper->axiom0[j];
						c += 1;
					}
				}

				if (gosper->grammar.M[cycle-1].A[0][i] == 2) {
					gosper->grammar.M[cycle].A[0][c] = 2;
					c += 1;}
	
				if (gosper->grammar.M[cycle-1].A[0][i] == 3) {
					gosper->grammar.M[cycle].A[0][c] = 3;
					c += 1;	}
	
				pivote = c;

			}
		}
	}

	int i, j;
	//for (i = 0; i < gosper->order; i++) {
	//	for (j = 0; j < gosper->grammar.M[i].n; j++){
	//		printf(" %d", gosper->grammar.M[i].A[0][j]);
	//	}
	//	printf("\n\n");
	//}

	for (i = 0; i < gosper->grammar.M[gosper->order-1].n; i++) {
		if (gosper->grammar.M[gosper->order-1].A[0][i] == 0) {
			forwardTurtle(&gosper->turtle);
			//printf(" %d", gosper->grammar.M[gosper->order-1].A[0][i]);
		}
		if (gosper->grammar.M[gosper->order-1].A[0][i] == 1) {
			forwardTurtle(&gosper->turtle);
			//printf(" %d", gosper->grammar.M[gosper->order-1].A[0][i]);
		}
		if (gosper->grammar.M[gosper->order-1].A[0][i] == 2) {
			rotateRightTurtle(&gosper->turtle);
			//printf(" %d", gosper->grammar.M[gosper->order-1].A[0][i]);
		}
		if (gosper->grammar.M[gosper->order-1].A[0][i] == 3) {
			rotateLeftTurtle(&gosper->turtle);
			//printf(" %d", gosper->grammar.M[gosper->order-1].A[0][i]);
		}
	}

	//printf("\n\n\n");
}

void renderGosperFractal(struct GosperFractal gosper, struct rotationMats U) {

	int i;
	for (i = 0; i < gosper.turtle.Max; i++)
		renderArista(gosper.turtle.path.A[0][i], U);
}

//////////////////////////
//						//
//	   HILBERT CURVE 	//
//					   	//
//////////////////////////

void initHilbertFractal(struct HilbertFractal * hilbert, Vector b, Vector u, int order) {

	int aux = 3;
	int k;

	hilbert->order = order;
	//printf("Preparing arista size:\n");
	if (hilbert->order == 1)
		initTurtle(&hilbert->turtle, b, u, 0.04, 0.5 * 3.1415, aux);
	else {
		for (k = 0; k < hilbert->order - 1; k++) {
			aux *= 4;
			aux += 3;
			printf("%d \n", aux);
		}

		initTurtle(&hilbert->turtle, b, u, 0.04, 0.5 * 3.1415, aux);
	}

	//printf("\n\nNumber of aristas := %d\n\n", aux);

	hilbert->axiom[0] = 4;	hilbert->axiom0[0] = 3;
	hilbert->axiom[1] = 2;	hilbert->axiom0[1] = 1;
	hilbert->axiom[2] = 0;	hilbert->axiom0[2] = 0;
	hilbert->axiom[3] = 3;	hilbert->axiom0[3] = 4;
	hilbert->axiom[4] = 1;	hilbert->axiom0[4] = 2;
	hilbert->axiom[5] = 0;	hilbert->axiom0[5] = 0;
	hilbert->axiom[6] = 1;	hilbert->axiom0[6] = 2;
	hilbert->axiom[7] = 3;	hilbert->axiom0[7] = 4;
	hilbert->axiom[8] = 0;	hilbert->axiom0[8] = 0;
	hilbert->axiom[9] = 2;	hilbert->axiom0[9] = 1;
	hilbert->axiom[10] = 4;	hilbert->axiom0[10] = 3;

}

void initPathHilbert(struct HilbertFractal * hilbert) {

	hilbert->grammar = initMatrixIntList(hilbert->order);
	//printf("Order %d hilbert Curve:\n", hilbert->order);
	hilbert->grammar.M[0] = creaEspacioMatrixInt(1, 11);

	hilbert->grammar.M[0].A[0][0] = 4;	hilbert->grammar.M[0].A[0][6] = 1;
	hilbert->grammar.M[0].A[0][1] = 2;	hilbert->grammar.M[0].A[0][7] = 3;
	hilbert->grammar.M[0].A[0][2] = 0;	hilbert->grammar.M[0].A[0][8] = 0;
	hilbert->grammar.M[0].A[0][3] = 3;	hilbert->grammar.M[0].A[0][9] = 2;
	hilbert->grammar.M[0].A[0][4] = 1;	hilbert->grammar.M[0].A[0][10] = 4;
	hilbert->grammar.M[0].A[0][5] = 0;

	if (hilbert->order > 1) {

		int num = 11;
		int j;
		for (j = 1; j < hilbert->order; j++) {
			num *= 4;
			num += 7;
			hilbert->grammar.M[j] = creaEspacioMatrixInt(1, num);
		}

		//for (j = 0; j < hilbert->order; j++)
			//printf("---> Building Memory M[%d]:= %d\n", j, hilbert->grammar.M[j].n);
		
		int i;
		int cycle;

		for (cycle = 1; cycle < hilbert->order; cycle++) {
			int c = 0;
			int pivote = 0;

			//Leemos la pila anterior
			for (i = 0; i < hilbert->grammar.M[cycle-1].n; i++) {

				//revisamos por F en la pila anterior
				if (hilbert->grammar.M[cycle-1].A[0][i] == 0) {
					hilbert->grammar.M[cycle].A[0][c] = 0;
					c += 1;}

				//revisamos por A en la pila anterior
				if (hilbert->grammar.M[cycle-1].A[0][i] == 1) {
					for (j = 0; j < 11; j++) {
						hilbert->grammar.M[cycle].A[0][j + pivote] = hilbert->axiom[j];
						c += 1;
					}
				}

				//revisamos por B en la pila anterior
				if (hilbert->grammar.M[cycle-1].A[0][i] == 2) {
					for (j = 0; j < 11; j++) {
						hilbert->grammar.M[cycle].A[0][j + pivote] = hilbert->axiom0[j];
						c += 1;
					}
				}

				if (hilbert->grammar.M[cycle-1].A[0][i] == 3) {
					hilbert->grammar.M[cycle].A[0][c] = 3;
					c += 1;}

				if (hilbert->grammar.M[cycle-1].A[0][i] == 4) {
					hilbert->grammar.M[cycle].A[0][c] = 4;
					c += 1;}

				pivote = c;

			}
		}
	}

	int i, j;
	//for (i = 0; i < hilbert->order; i++) {
	//	for (j = 0; j < hilbert->grammar.M[i].n; j++){
	//		printf(" %d", hilbert->grammar.M[i].A[0][j]);
	//	}
	//	printf("\n\n");
	//}

	for (i = 0; i < hilbert->grammar.M[hilbert->order-1].n; i++) {
		if (hilbert->grammar.M[hilbert->order-1].A[0][i] == 0) {
			forwardTurtle(&hilbert->turtle);
			//printf(" %d", hilbert->grammar.M[hilbert->order-1].A[0][i]);
		}
		
		if (hilbert->grammar.M[hilbert->order-1].A[0][i] == 3) {
			rotateRightTurtle(&hilbert->turtle);
			//printf(" %d", hilbert->grammar.M[hilbert->order-1].A[0][i]);
		}

		if (hilbert->grammar.M[hilbert->order-1].A[0][i] == 4) {
			rotateLeftTurtle(&hilbert->turtle);
			//printf(" %d", hilbert->grammar.M[hilbert->order-1].A[0][i]);
		}
	}

}

void renderHilbertFractal(struct HilbertFractal hilbert, struct rotationMats U, int iter) {

	int i;
	for (i = 0; i < iter; i++)
		renderArista(hilbert.turtle.path.A[0][i], U);
}

//////////////////////////
//						//
//	 SIERSPINSKI CURVE 	//
//					   	//
//////////////////////////

void initSierspinskiCurve(struct SierspinskiCurve * sier, Vector b, Vector u, int order) {

	int aux = 4;
	int k;

	sier->order = order;
	printf("Preparing arista size:\n");
	for (k = 0; k < sier->order - 1; k++) {
		aux *= 4;
		printf("%d \n", aux);
	}

	initTurtle(&sier->turtle, b, u, 0.04, 0.25 * 3.1415, aux);
	

	printf("\n\nNumber of aristas := %d\n\n", aux);

	sier->axiom[0] = 0;		sier->axiom0[0] = 2;	sier->axiom0[12] = 2;
	sier->axiom[1] = 4;		sier->axiom0[1] = 0;	sier->axiom0[13] = 0;
	sier->axiom[2] = 4;		sier->axiom0[2] = 3;	sier->axiom0[14] = 3;
	sier->axiom[3] = 2;		sier->axiom0[3] = 1;	sier->axiom0[15] = 1;
	sier->axiom[4] = 0;		sier->axiom0[4] = 3;	sier->axiom0[16] = 3;
	sier->axiom[5] = 4;		sier->axiom0[5] = 2;	sier->axiom0[17] = 2;
	sier->axiom[6] = 4;		sier->axiom0[6] = 0;
	sier->axiom[7] = 0;		sier->axiom0[7] = 4;
	sier->axiom[8] = 4;		sier->axiom0[8] = 4;
	sier->axiom[9] = 4;		sier->axiom0[9] = 0;
	sier->axiom[10] = 2;	sier->axiom0[10] = 4;
	sier->axiom[11] = 0;	sier->axiom0[11] = 4;

}

void initPathSierspinskiCurve(struct SierspinskiCurve * sier) {

	sier->grammar = initMatrixIntList(sier->order);
	printf("Order %d sier Curve:\n", sier->order);
	sier->grammar.M[0] = creaEspacioMatrixInt(1, 12);

	sier->grammar.M[0].A[0][0] = 0;	sier->grammar.M[0].A[0][6] = 4;
	sier->grammar.M[0].A[0][1] = 4;	sier->grammar.M[0].A[0][7] = 0;
	sier->grammar.M[0].A[0][2] = 4;	sier->grammar.M[0].A[0][8] = 4;
	sier->grammar.M[0].A[0][3] = 2;	sier->grammar.M[0].A[0][9] = 4;
	sier->grammar.M[0].A[0][4] = 0;	sier->grammar.M[0].A[0][10] = 2;
	sier->grammar.M[0].A[0][5] = 4;	sier->grammar.M[0].A[0][11] = 0;

	if (sier->order > 1) {

		int num = 18;
		int P = 18;
		int j;
		for (j = 1; j < sier->order; j++) {

			if (j == 1) {
				num *= 2;
				num += 10;
				sier->grammar.M[j] = creaEspacioMatrixInt(1, num);
			} else {
				P *= 4;
				P += 14;
				sier->grammar.M[j] = creaEspacioMatrixInt(1, (2*P) + 10);
			}
		}

		for (j = 0; j < sier->order; j++)
			printf("---> Building Memory M[%d]:= %d\n", j, sier->grammar.M[j].n);

		int i;
		int cycle;

		for (cycle = 1; cycle < sier->order; cycle++) {
			int c = 0;
			int pivote = 0;

			//Leemos la pila anterior
			for (i = 0; i < sier->grammar.M[cycle-1].n; i++) {

				//revisamos por F en la pila anterior
				if (sier->grammar.M[cycle-1].A[0][i] == 0) {
					sier->grammar.M[cycle].A[0][c] = 0;
					c += 1;}

				//revisamos por G en la pila anterior
				if (sier->grammar.M[cycle-1].A[0][i] == 1) {
					sier->grammar.M[cycle].A[0][c] = 1;
					c += 1;}

				//revisamos por X en la pila anterior
				if (sier->grammar.M[cycle-1].A[0][i] == 2) {
					for (j = 0; j < 18; j++) {
						sier->grammar.M[cycle].A[0][j + pivote] = sier->axiom0[j];
						c += 1;
					}
				}

				if (sier->grammar.M[cycle-1].A[0][i] == 3) {
					sier->grammar.M[cycle].A[0][c] = 3;
					c += 1;}

				if (sier->grammar.M[cycle-1].A[0][i] == 4) {
					sier->grammar.M[cycle].A[0][c] = 4;
					c += 1;}

				pivote = c;
			}
		} 
	}

	int i, j;
	//printf("\n\nPrinting info;\n\n");
	//for (i = 0; i < sier->order; i++) {
	//	for (j = 0; j < sier->grammar.M[i].n; j++){
	//		printf(" %d", sier->grammar.M[i].A[0][j]);
	//	}
	//	printf("\n\n");
	//}

	for (i = 0; i < sier->grammar.M[sier->order-1].n; i++) {
		if (sier->grammar.M[sier->order-1].A[0][i] == 0) {
			forwardTurtle(&sier->turtle);
			//printf(" %d", sier->grammar.M[sier->order-1].A[0][i]);
		}

		if (sier->grammar.M[sier->order-1].A[0][i] == 1) {
			forwardTurtle(&sier->turtle);
			//printf(" %d", sier->grammar.M[sier->order-1].A[0][i]);
		}
		
		if (sier->grammar.M[sier->order-1].A[0][i] == 3) {
			rotateRightTurtle(&sier->turtle);
			//printf(" %d", sier->grammar.M[sier->order-1].A[0][i]);
		}

		if (sier->grammar.M[sier->order-1].A[0][i] == 4) {
			rotateLeftTurtle(&sier->turtle);
			//printf(" %d", sier->grammar.M[sier->order-1].A[0][i]);
		}
	}


}

void renderSierspinskiCurve(struct SierspinskiCurve sier, struct rotationMats U) {

	int i;
	for (i = 0; i < sier.turtle.Max; i++)
		renderArista(sier.turtle.path.A[0][i], U);
}

//////////////////////////
//						//
//	 	LEVY CURVE 		//
//					   	//
//////////////////////////

void initLevyCurve(struct LevyCurve * levy, Vector b, Vector u, int order) {

	int aux = 1;
	int k;

	levy->order = order;
	//printf("Preparing arista size:\n");
	for (k = 0; k < levy->order - 1; k++) {
		aux *= 2;
		printf("%d \n", aux);
	}

	initTurtle(&levy->turtle, b, u, 0.2, 0.25 * 3.1415, aux);
	

	//printf("\n\nNumber of aristas := %d\n\n", aux);

	levy->axiom[0] = 1;
	levy->axiom[1] = 0;
	levy->axiom[2] = 2;
	levy->axiom[3] = 2;
	levy->axiom[4] = 0;
	levy->axiom[5] = 1;

}

void initPathLevyCurve(struct LevyCurve * levy) {

	levy->grammar = initMatrixIntList(levy->order);
	//printf("Order %d levy Curve:\n", levy->order);
	levy->grammar.M[0] = creaEspacioMatrixInt(1, 6);

	levy->grammar.M[0].A[0][0] = 1;
	levy->grammar.M[0].A[0][1] = 0;
	levy->grammar.M[0].A[0][2] = 2;
	levy->grammar.M[0].A[0][3] = 2;
	levy->grammar.M[0].A[0][4] = 0;
	levy->grammar.M[0].A[0][5] = 1;

	if (levy->order > 1) {

		int P = 6;
		int j;
		for (j = 1; j < levy->order; j++) {
			P *= 2;
			P += 4;
			levy->grammar.M[j] = creaEspacioMatrixInt(1, P);
		}

		//for (j = 0; j < levy->order; j++)
		//	printf("---> Building Memory M[%d]:= %d\n", j, levy->grammar.M[j].n);

		int i;
		int cycle;

		for (cycle = 1; cycle < levy->order; cycle++) {

			int c = 0;
			int pivote = 0;

			//Leemos la pila anterior
			for (i = 0; i < levy->grammar.M[cycle-1].n; i++) {

				//revisamos por F en la pila anterior
				if (levy->grammar.M[cycle-1].A[0][i] == 0) {
					for (j = 0; j < 6; j++) {
						levy->grammar.M[cycle].A[0][j + pivote] = levy->axiom[j];
						c += 1;
					}
				}


				if (levy->grammar.M[cycle-1].A[0][i] == 1) {
					levy->grammar.M[cycle].A[0][c] = 1;
					c += 1;}

				if (levy->grammar.M[cycle-1].A[0][i] == 2) {
					levy->grammar.M[cycle].A[0][c] = 2;
					c += 1;}

				pivote = c;


			}
		}
	}

	int i, j;
	//printf("\n\nPrinting info;\n\n");
	//for (i = 0; i < levy->order; i++) {
	//	for (j = 0; j < levy->grammar.M[i].n; j++){
	//		printf(" %d", levy->grammar.M[i].A[0][j]);
	//	}
	//	printf("\n\n");
	//}

	for (i = 0; i < levy->grammar.M[levy->order-1].n; i++) {
		if (levy->grammar.M[levy->order-1].A[0][i] == 0) {
			forwardTurtle(&levy->turtle);
			//printf(" %d", levy->grammar.M[levy->order-1].A[0][i]);
		}
		
		if (levy->grammar.M[levy->order-1].A[0][i] == 1) {
			rotateRightTurtle(&levy->turtle);
			//printf(" %d", levy->grammar.M[levy->order-1].A[0][i]);
		}

		if (levy->grammar.M[levy->order-1].A[0][i] == 2) {
			rotateLeftTurtle(&levy->turtle);
			//printf(" %d", levy->grammar.M[levy->order-1].A[0][i]);
		}
	}

}

void renderLevyCurve(struct LevyCurve levy, struct rotationMats U, int iter) {

	int i;
	for (i = 0; i < levy.turtle.Max; i++)
		renderArista(levy.turtle.path.A[0][i], U);
}

//////////////////////////
//						//
//	 	DRAGON CURVE 	//
//					   	//
//////////////////////////

void initDragonCurve(struct DragonCurve * dragon, Vector b, Vector u, int order) {

	int aux = 1;
	int k;

	dragon->order = order;
	//printf("Preparing arista size:\n");
	for (k = 0; k < dragon->order - 1; k++) {
		aux *= 2;
		printf("%d \n", aux);
	}

	initTurtle(&dragon->turtle, b, u, 0.2, 0.5 * 3.1415, aux);
	

	//printf("\n\nNumber of aristas := %d\n\n", aux);

	dragon->axiom[0] = 1;	dragon->axiom0[0] = 4;
	dragon->axiom[1] = 3;	dragon->axiom0[1] = 0;
	dragon->axiom[2] = 2;	dragon->axiom0[2] = 1;
	dragon->axiom[3] = 0;	dragon->axiom0[3] = 4;
	dragon->axiom[4] = 3;	dragon->axiom0[4] = 2;

}

void initPathDragonCurve(struct DragonCurve * dragon) {

	dragon->grammar = initMatrixIntList(dragon->order);
	//printf("Order %d dragon Curve:\n", dragon->order);
	dragon->grammar.M[0] = creaEspacioMatrixInt(1, 5);

	dragon->grammar.M[0].A[0][0] = 1;
	dragon->grammar.M[0].A[0][1] = 3;
	dragon->grammar.M[0].A[0][2] = 2;
	dragon->grammar.M[0].A[0][3] = 0;
	dragon->grammar.M[0].A[0][4] = 3;

	if (dragon->order > 1) {

		int P = 5;
		int j;
		for (j = 1; j < dragon->order; j++) {
				P *= 2;
				P += 3;
				dragon->grammar.M[j] = creaEspacioMatrixInt(1, P);
		}

		//for (j = 0; j < dragon->order; j++)
		//	printf("---> Building Memory M[%d]:= %d\n", j, dragon->grammar.M[j].n);

		int i;
		int cycle;

		for (cycle = 1; cycle < dragon->order; cycle++) {

			int c = 0;
			int pivote = 0;

			//Leemos la pila anterior
			for (i = 0; i < dragon->grammar.M[cycle-1].n; i++) {

				//revisamos por F en la pila anterior
				if (dragon->grammar.M[cycle-1].A[0][i] == 0) {
						dragon->grammar.M[cycle].A[0][c] = 0;
						c += 1;}

				//revisamos por X en la pila anterior
				if (dragon->grammar.M[cycle-1].A[0][i] == 1) {
					for (j = 0; j < 5; j++) {
						dragon->grammar.M[cycle].A[0][j + pivote] = dragon->axiom[j];
						c += 1;
					}
				}

				//revisamos por Y en la pila anterior
				if (dragon->grammar.M[cycle-1].A[0][i] == 2) {
					for (j = 0; j < 5; j++) {
						dragon->grammar.M[cycle].A[0][j + pivote] = dragon->axiom0[j];
						c += 1;
					}
				}

				if (dragon->grammar.M[cycle-1].A[0][i] == 3) {
					dragon->grammar.M[cycle].A[0][c] = 3;
					c += 1;}

				if (dragon->grammar.M[cycle-1].A[0][i] == 4) {
					dragon->grammar.M[cycle].A[0][c] = 4;
					c += 1;}

				pivote = c;
			
			}
		}
	}

	int i, j;
	//printf("\n\nPrinting info;\n\n");
	//for (i = 0; i < dragon->order; i++) {
	//	for (j = 0; j < dragon->grammar.M[i].n; j++){
	//		printf(" %d", dragon->grammar.M[i].A[0][j]);
	//	}
	//	printf("\n\n");
	//}

	for (i = 0; i < dragon->grammar.M[dragon->order-1].n; i++) {
		if (dragon->grammar.M[dragon->order-1].A[0][i] == 0) {
			forwardTurtle(&dragon->turtle);
			//printf(" %d", dragon->grammar.M[dragon->order-1].A[0][i]);
		}
		
		if (dragon->grammar.M[dragon->order-1].A[0][i] == 3) {
			rotateRightTurtle(&dragon->turtle);
			//printf(" %d", dragon->grammar.M[dragon->order-1].A[0][i]);
		}

		if (dragon->grammar.M[dragon->order-1].A[0][i] == 4) {
			rotateLeftTurtle(&dragon->turtle);
			//printf(" %d", dragon->grammar.M[dragon->order-1].A[0][i]);
		}
	}

}

void renderDragonCurve(struct DragonCurve dragon, struct rotationMats U, int iter) {

	int i;
	for (i = 0; i < dragon.turtle.Max; i++)
		renderArista(dragon.turtle.path.A[0][i], U);
}
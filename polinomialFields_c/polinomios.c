#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "polinomios.h"
#include "Matrix.h"
#include "vector.h"
#include <stdarg.h>
#include "polinomios.h"

void initAnilloZp(struct AnilloZp * anillo, int id, int mod) {

	printf("Defining a ring structure R = Z%d ------ >\n", mod);
	anillo->id = id;
	anillo->mod = mod;
	anillo->linearSpace = creaEspacioMatrixInt(1, mod);
	anillo->latticeSpace = creaEspacioMatrixV(mod, mod);
	anillo->latticeSpace0 = creaEspacioMatrixV(mod, mod);
	anillo->addAuxMat = creaEspacioMatrixInt(mod, mod);
	anillo->multAuxMat = creaEspacioMatrixInt(mod, mod);
	anillo->vectorSpace = creaEspacioMatrixV(mod, mod);

	int i, j;
	for (i = 0; i < 1; i++) 
		for (j = 0; j < mod; j++) 
			anillo->linearSpace.A[i][j] = j;

	for (i = 0; i < mod; i++) 
		for (j = 0; j < mod; j++) {
			double i0 = i;
			double j0 = j;
			if (i == 0 && j == 0) vectorGo(&anillo->latticeSpace.A[i][j], 3, i0, j0, 2.5);
			else vectorGo(&anillo->latticeSpace.A[i][j], 3, i0, j0, 0.0);
		}

	for (i = 0; i < mod; i++) 
		for (j = 0; j < mod; j++) {
			double i0 = i;
			double j0 = j;
			if (i == 0 && j == 0) vectorGo(&anillo->latticeSpace0.A[i][j], 3, i0, j0, 2.5);
			else vectorGo(&anillo->latticeSpace0.A[i][j], 3, i0, 0.0, j0);
		}

	anillo->campo = creaEspacioMatrixVecindadCubica(mod, mod);
	for (i = 0; i < mod; i++) 
		for (j = 0; j < mod; j++) 
			initVecindadCubica(&anillo->campo.A[i][j], anillo->latticeSpace.A[i][j], 0.5);

	anillo->campo0 = creaEspacioMatrixVecindadCubica(mod, mod);
	for (i = 0; i < mod; i++) 
		for (j = 0; j < mod; j++) 
			initVecindadCubica(&anillo->campo0.A[i][j], anillo->latticeSpace0.A[i][j], 0.5);
}

MatrixAnilloZp creaMatrixAnilloZp(int m, int n) {
  MatrixAnilloZp ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (struct AnilloZp**) malloc (m * sizeof(struct AnilloZp*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (struct AnilloZp *) malloc (n * sizeof(struct AnilloZp));
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

void additionInZp(struct AnilloZp * anillo, PolinomioZp p) {

	int i, j;
	for (i = 0; i < anillo->mod; i++)
		for (j = 0; j < anillo->mod; j++) {
			if (i == 0 && j == 0) {
				updateVectorR3(&anillo->latticeSpace.A[i][j],	(int)(anillo->latticeSpace.A[i][j].v[0] + (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[1] + (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[2] + (double)p.a[2])%anillo->mod);
			} else {
				updateVectorR3(&anillo->latticeSpace.A[i][j],	(int)(anillo->latticeSpace.A[i][j].v[0] + (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[1] + (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[2] + (double)p.a[2])%anillo->mod);
			}
			updateVecindadCubica(&anillo->campo.A[i][j], anillo->latticeSpace.A[i][j], 0.48);
		}

	for (i = 0; i < anillo->mod; i++)
		for (j = 0; j < anillo->mod; j++) {
			if (i == 0 && j == 0) {
				updateVectorR3(&anillo->latticeSpace0.A[i][j],	(int)(anillo->latticeSpace0.A[i][j].v[0] + (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace0.A[i][j].v[1] + (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace0.A[i][j].v[2] + (double)p.a[2])%anillo->mod);
			} else {
				updateVectorR3(&anillo->latticeSpace0.A[i][j],	(int)(anillo->latticeSpace0.A[i][j].v[0] + (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace0.A[i][j].v[1] + (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace0.A[i][j].v[2] + (double)p.a[2])%anillo->mod);
			}
			updateVecindadCubica(&anillo->campo0.A[i][j], anillo->latticeSpace0.A[i][j], 0.48);
		}
}

void multiplicationInZp(struct AnilloZp * anillo, PolinomioZp p) {
	
	PolinomioZp I;
	initPolinomioZp(&I, 11, 3,   4, 1, 1);
	printPolinomioZp(I);printf("\n");
	int i, j;
	for (i = 0; i < anillo->mod; i++)
		for (j = 0; j < anillo->mod; j++) {
			PolinomioZp q = vecToPolinomioZp2D(anillo->latticeSpace.A[i][j], p.mod);
			PolinomioZp multResult = multPolinomioZp(p, q);
			PolinomioZp ret = modP(multResult, I);
			printf("---> (");printPolinomioZp(p);printf(")  *  (");printPolinomioZp(q);printf(") = ");printPolinomioZp(ret); printf("\n");
			updateVectorR3(&anillo->latticeSpace.A[i][j], ret.a[0], ret.a[1], anillo->latticeSpace.A[i][j].v[2]);
			updateVecindadCubica(&anillo->campo.A[i][j], anillo->latticeSpace.A[i][j], 0.48);
		}
}

void subtractionInZp(struct AnilloZp * anillo, PolinomioZp p) {

	int i, j;
	for (i = 0; i < anillo->mod; i++)
		for (j = 0; j < anillo->mod; j++) {
			if (i == 0 && j == 0) {
				updateVectorR3(&anillo->latticeSpace.A[i][j],	(int)(anillo->latticeSpace.A[i][j].v[0] - (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[1] - (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[2] - (double)p.a[2])%anillo->mod);
			} else {
				updateVectorR3(&anillo->latticeSpace.A[i][j],	(int)(anillo->latticeSpace.A[i][j].v[0] - (double)p.a[0])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[1] - (double)p.a[1])%anillo->mod,
																(int)(anillo->latticeSpace.A[i][j].v[2] - (double)p.a[2])%anillo->mod);
			}
			
			updateVecindadCubica(&anillo->campo.A[i][j], anillo->latticeSpace.A[i][j], 0.48);
		}		
}

void renderAnilloZp(struct AnilloZp anillo, struct rotationMats U) {

	int i, j;
	for (i = 0; i < anillo.mod; i++) 
		for (j = 0; j < anillo.mod; j++) {
			renderVecindadCubica(anillo.campo.A[i][j], U);
			//renderVecindadCubica(anillo.campo0.A[i][j], U);
		}
}

void printAnilloZp(struct AnilloZp anillo) {

	printf("\n\n-------------------------------------------------------------------------------------------\n");
	printf("Ring R has mod := %d, so R = Z%d.\n", anillo.mod, anillo.mod);

	printf("\n---> Z%d = {", anillo.mod);
	int i, j;
	for (i = 0; i < 1; i++) 
		for (j = 0; j < anillo.mod; j++) 
			printf(" %d", anillo.linearSpace.A[i][j]);
	printf(" }\n\n");

	printf("\n---> Z%dxZ%d = {\n\n", anillo.mod, anillo.mod);
	for (i = 0; i < anillo.mod; i++) {
		for (j = 0; j < anillo.mod; j++) {
			printf("	");
			printVector(anillo.latticeSpace.A[i][j], 0);
		}
		printf("\n\n");
	}
	printf(" }\n\n");
}

void initPolinomioZp(PolinomioZp * p, int mod, int grado, ...) {

	va_list list;
	p->mod = mod;
	int i;

	p->aux = (int *) malloc (grado * sizeof(int));

	va_start(list, grado);
	for (i = 0; i < grado; i++) {
		p->aux[i] = va_arg(list, int);
		p->aux[i] = p->aux[i] % mod;
	}
	va_end(list);

	i = grado - 1;
	int ceroCount = 0;
	while ( i > 0) {
		if (p->aux[i] == 0) ceroCount += 1;
		else break;

		i -= 1;
	}

	p->a = (int *) malloc ((grado - ceroCount) * sizeof(int));
	for (i = 0; i < grado - ceroCount; i++)
		p->a[i] = p->aux[i];
	p->grado = (grado - ceroCount) - 1;
}

void printPolinomioZp(PolinomioZp p) {

	int i;
	for (i = 0; i < p.grado + 1; i++) {

		if (i == 0) 
			printf(" %d", p.a[i]);
		else 
			printf("+ %d(x^%d)", p.a[i], i);
	}
}

void printPolinomioZpP(PolinomioZp * p) {

	int i;
	for (i = 0; i < p->grado + 1; i++) {

		if (i == 0) 
			printf(" %d", p->a[i]);
		else 
			printf("+ %d(x^%d)", p->a[i], i);
	}
}

PolinomioZp addPolinomioZp(PolinomioZp p, PolinomioZp q) {

	PolinomioZp ret = {
		grado : p.grado + q.grado + 1,
		mod : p.mod,
		a : NULL
	};

	if (p.mod == q.mod) {
		ret.mod = p.mod;
		if (p.grado == q.grado) {
			ret.grado = p.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));

			int i;
			for (i = 0; i < ret.grado + 1; i++)
				ret.a[i] = (p.a[i] + q.a[i])%ret.mod;
		}	
	}

	return ret;
}

void checkPolinomioZp(PolinomioZp * p) {

	int i;
	p->aux = realloc (p->aux, (p->grado + 1) * sizeof * p->aux);
	for (i = 0; i < p->grado + 1; i++)
		p->aux[i] = p->a[i];

	i = p->grado;
	int ceroCount = 0;
	while ( i > 0) {
		if (p->aux[i] == 0) ceroCount += 1;
		else break;
		i -= 1;
	}

	p->a = realloc (p->a, (p->grado - ceroCount + 1) * sizeof * p->a);
	for (i = 0; i < p->grado - ceroCount + 1; i++)
		p->a[i] = p->aux[i];

	p->grado = (p->grado - ceroCount);
}

void subPolinomioZpP(PolinomioZp * p, PolinomioZp q) {

	int i;
	if (p->mod == q.mod) {


		if (p->grado == q.grado) {	//////////////////
			for (i = 0; i < p->grado + 1; i++) {
				p->a[i] -= q.a[i];
				p->a[i] %= p->mod;
			}
		}

		if (p->grado > q.grado) {	///////////////////
			for (i = 0; i < q.grado + 1; i++) {
				p->a[i] -= q.a[i];
				p->a[i] %= p->mod;
			}
		}

		if (p->grado < q.grado) {	/////////////////////
			for (i = 0; i < p->grado + 1; i++)
				p->aux[i] = p->a[i];
			p->a = (int * ) malloc ((q.grado + 1) * sizeof(int));

			for (i = 0; i < p->grado + 1; i++)
				p->a[i] = (p->aux[i] - q.a[i])%p->mod;

			for (i = p->grado + 1; i < q.grado + 1; i++)
				p->a[i] = 0 - q.a[i];
			p->grado = q.grado;
		}
	}

	checkNegativesPoli(p);
	checkPolinomioZp(p);
}

PolinomioZp subPolinomioZp(PolinomioZp p, PolinomioZp q) {

	PolinomioZp ret = {
		grado : p.grado + q.grado + 1,
		mod : p.mod,
		a : NULL
	};

	if (p.mod == q.mod) {
		ret.mod = p.mod;
		

		if (p.grado == q.grado) {/////
			ret.grado = p.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));

			int i;
			for (i = 0; i < ret.grado + 1; i++)
				ret.a[i] = (p.a[i] - q.a[i])%ret.mod;
		} 
		
		if (p.grado > q.grado) {

			ret.grado = p.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
	
			int i;
			for (i = 0; i < q.grado + 1; i++)
				ret.a[i] = (p.a[i] - q.a[i])%ret.mod;

			for (i = q.grado + 1; i < p.grado + 1; i++)
				ret.a[i] = p.a[i];
		} 

		if (q.grado > p.grado) {

			ret.grado = q.grado;
			ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
	
			int i;
			for (i = 0; i < p.grado + 1; i++)
					ret.a[i] = (p.a[i] - q.a[i])%ret.mod;

			for (i = p.grado + 1; i < q.grado + 1; i++)
				ret.a[i] = 0 - q.a[i];

		}
	} else {

		printf("\n\nERROR________________ mod != mod\n\n");
	}

	return ret;
}

PolinomioZp multPolinomioZp(PolinomioZp p, PolinomioZp q) {

	PolinomioZp ret = {
		grado : p.grado + q.grado,
		mod : p.mod,
		aux : p.aux,
		a : NULL
	};

	if (p.mod == q.mod) {
		ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int)); 
		
		int i, j;
		for (i = 0; i < ret.grado + 1; i++)
			ret.a[i] = 0;

		PolinomioZp * retPrime = &ret;
		for (i = 0; i < p.grado + 1; i++)
			for (j = 0; j < q.grado + 1; j++) {
				retPrime->a[i + j] += (p.a[i] * q.a[j])%ret.mod; 
			}
	}

	checkNegativesPoli(&ret);
	checkPolinomioZp(&ret);
	return ret;
}

PolinomioZp multSPolinomioZp(int k, PolinomioZp p) {

	PolinomioZp ret = {
		grado : p.grado,
		mod : p.mod,
		a : NULL
	};

	ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
	int i;
	for (i = 0; i < p.grado + 1; i++)
		ret.a[i] = (k * p.a[i])%p.mod;
	return ret;
}

int pot(int p, int n) {

	int po = 1;
	int i;
	if (n == 0) return 1;
	else {
		for (i = 0; i < n; i++)
			po *= p;
		return po;
	}
}

int max(int a, int b) {

	if (a == b) return a;
	else {
		if (a < b) return b;
		else return a;
	}
}

int irreducibleEnZp( PolinomioZp p) {
	
	int ret = 0;
	int root = 0;
	int i;

	while (ret != p.mod) {
		int sum = 0;
		for (i = 0; i < p.grado + 1; i++)
			sum += p.a[i] * pot(ret, i);
		ret += 1;
		if (sum%p.mod == 0) {
			root += 1;
			break;
		}
	}

	return root;
}

int potMod(int n, int m, int mod) {

	int p = 1;
	int i;
	if (m == 0) return p;
	else {
		for (i = 0; i < m; i++) 
			p *= n;
		return p%mod;
	}
}

int inversoZp(int a, int mod) {
	return potMod(a, mod - 2, mod);
}

int divideZp(int num, int den, int mod) {
	return (num * inversoZp(den, mod))%mod;
}

int zero(PolinomioZp p) {

	int sum = 0;
	int i;
	for (i = 0; i < p.grado + 1; i++)
		if (p.a[i] != 0)
			sum += 1;
	if (sum == 0) return 0;
	else return 1;
}

int zeroP(PolinomioZp * p) {

	int sum = 0;
	int i;
	for (i = 0; i < p->grado + 1; i++)
		if (p->a[i] != 0)
			sum += 1;
	if (sum == 0) return 0;
	else return 1;
}

PolinomioZp vecToPolinomioZp2D(Vector p, int mod) {

	int v0 = p.v[0];
	int v1 = p.v[1];

	PolinomioZp ret = {mod : mod, a : NULL};

	if (v1 == 0) {
		ret.grado = 0;

		ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
		ret.a[0] = v0%mod;
	} else {
		ret.grado = 1;

		ret.a = (int *) malloc ((ret.grado + 1) * sizeof(int));
		ret.a[0] = v0%mod;
		ret.a[1] = v1%mod;
	}
	PolinomioZp * rr = &ret;
	checkNegativesPoli(rr);
	checkPolinomioZp(rr);
	return ret;

}

Vector PolinomioZpToVec(PolinomioZp p) {

	double v0 = p.a[0];
	double v1 = p.a[1];
	Vector ret;
	vectorGo(&ret, 2, v0, v1);

	return ret;
}

PolinomioZp auxPoli(int head, int num, int mod) {

	PolinomioZp ret = {
		mod : mod,
		grado : num - 1,
		a : NULL
	};

	ret.a = (int *) malloc (num * sizeof(int));
	int i; 
	for (i = 0; i < num - 1; i++)
		ret.a[i] = 0;
	ret.a[num - 1] = head;

	return ret;
}

void checkNegativesPoli(PolinomioZp * p) {

	int i;
	for (i = 0; i < p->grado + 1; i++)
		p->a[i] %= p->mod; 

	for (i = 0; i < p->grado + 1; i++)
		if (p->a[i] < 0)
			p->a[i] = p->mod + p->a[i]; 
}

PolinomioZp modP(PolinomioZp a, PolinomioZp p) {

	PolinomioZp r = {
		mod : a.mod,
		grado : a.grado,
		aux : a.aux,
		a : a.a
	};
	
	PolinomioZp * rp = &r;
	//printf("First Residuo := "); printPolinomioZpP(rp); printf("\n");
	int i;
	while (zeroP(rp) != 0 && rp->grado >= p.grado) {

		int t = divideZp(rp->a[rp->grado], p.a[p.grado], a.mod);
		//printf("coef = %d/%d = %d\n", rp->a[rp->grado], p.a[p.grado], t);
		PolinomioZp T = auxPoli(t, rp->grado - p.grado + 1, a.mod);
		//printf("T = "); printPolinomioZp(T); printf("\n");
		PolinomioZp TP = multPolinomioZp(T, p);
		//printPolinomioZp(TP);
		subPolinomioZpP(rp, TP);
	}

	checkNegativesPoli(&r);
	return r;
}
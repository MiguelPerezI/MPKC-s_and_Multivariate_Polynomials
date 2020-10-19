#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include "vector.h"
#include "Matrix.h"
#include "Arista.h"

void facet(struct facet * f, Vector a, Vector b, Vector c) {

	f->a = a;
	f->b = b;
	f->c = c;

	f->resta1 = subVectorGo(b, a);
	f->resta2 = subVectorGo(c, a);

	cruzVectorR3(&f->resta1, f->resta2);
	vectorGo(&f->normal, 3, f->resta1.w[0], f->resta1.w[1], f->resta1.w[2]);

	f->aPrime = a;
	f->bPrime = b;
	f->cPrime = c;

	vectorGo(&f->normalPrime, 3, f->resta1.w[0], f->resta1.w[1], f->resta1.w[2]);

}

void updateFacet(struct facet * f, Vector new_a, Vector new_b, Vector new_c) {

	updateVectorR3(&f->a, new_a.v[0], new_a.v[1], new_a.v[2]);
	updateVectorR3(&f->b, new_b.v[0], new_b.v[1], new_b.v[2]);
	updateVectorR3(&f->c, new_c.v[0], new_c.v[1], new_c.v[2]);

	updateVectorR3(&f->resta1, new_b.v[0] - new_a.v[0], new_b.v[1] - new_a.v[1], new_b.v[2] - new_a.v[2]);
	updateVectorR3(&f->resta2, new_c.v[0] - new_a.v[0], new_c.v[1] - new_a.v[1], new_c.v[2] - new_a.v[2]);

	cruzVectorR3(&f->resta1, f->resta2);
	updateVectorR3(&f->normal, f->resta1.w[0], f->resta1.w[1], f->resta1.w[2]);
}

void renderFacet(struct facet sim, struct rotationMats U, int mod) {

	if (mod%8 == 0) glColor3ub(255, 255, 255);
	if (mod%8 == 1) glColor3ub(  0, 255, 255);
	if (mod%8 == 2) glColor3ub(  0,   0, 255);
	if (mod%8 == 3) glColor3ub(255,   0, 255);
	if (mod%8 == 4) glColor3ub(255, 255, 	 0);
	if (mod%8 == 5) glColor3ub(  0, 255, 	 0);
	if (mod%8 == 6) glColor3ub(255, 150, 	 0);
	if (mod%8 == 7) glColor3ub(255,   0, 	 0);

	rot3D(&U, sim.normal);
  	glBegin(GL_TRIANGLES);
	glNormal3f( U.aux.v[0], U.aux.v[1], U.aux.v[2]);
	rot3D(&U, sim.a);
	glVertex3f( U.aux.v[0], U.aux.v[1], U.aux.v[2]);
	rot3D(&U, sim.b);
	glVertex3f( U.aux.v[0], U.aux.v[1], U.aux.v[2]);
	rot3D(&U, sim.c);
	glVertex3f( U.aux.v[0], U.aux.v[1], U.aux.v[2]);
	glEnd();
}

MatrixFacet creaMatrixFacet(int m, int n) {
  MatrixFacet ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (struct facet**) malloc (m * sizeof(struct facet*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (struct facet *) malloc (n * sizeof(struct facet));
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

void aristaGo(struct Arista * arista, Vector a, Vector b, double width) {

	arista->head = a;
	arista->base = b;
	arista->width = width;
	vectorGo(&arista->help, 3, 0.0, 0.0, 0.0);

	subVector(&arista->head, arista->base);
	vectorGo(&arista->D, 3, arista->head.w[0], arista->head.w[1], arista->head.w[2]);

	vectorGo(&arista->h0, 3, arista->D.v[0], arista->D.v[1], 0.0);
	vectorGo(&arista->h1, 3, arista->D.v[0], arista->D.v[1], arista->D.v[2]);
	vectorGo(&arista->h2, 3, 0.0, 0.0, arista->D.v[2]);
	vectorGo(&arista->h3, 3, 
								arista->D.v[0]*0.5 + arista->base.v[0], 
								arista->D.v[1]*0.5 + arista->base.v[1], 
								arista->D.v[2]*0.5 + arista->base.v[2]
								);
	arista->longitud = 0.5 * distanceVector(arista->head, arista->base);
	double ajuste = 0.95;
	
	vectorCapsuleGo(&arista->points, 10);
	vectorGo(&arista->points.A[0], 3, 0.0, 0.0, arista->longitud);
	vectorGo(&arista->points.A[1], 3, width, width, arista->longitud * ajuste);
	vectorGo(&arista->points.A[2], 3,-width, width, arista->longitud * ajuste);
	vectorGo(&arista->points.A[3], 3,-width,-width, arista->longitud * ajuste);
	vectorGo(&arista->points.A[4], 3, width,-width, arista->longitud * ajuste);
	vectorGo(&arista->points.A[5], 3, width, width,-arista->longitud * ajuste);
	vectorGo(&arista->points.A[6], 3,-width, width,-arista->longitud * ajuste);
	vectorGo(&arista->points.A[7], 3,-width,-width,-arista->longitud * ajuste);
	vectorGo(&arista->points.A[8], 3, width,-width,-arista->longitud * ajuste);		
	vectorGo(&arista->points.A[9], 3, 0.0, 0.0,-arista->longitud);

	double P_pro_p_k = arista->h0.v[0];
	double abs_pro_p = arista->h0.norma;
	double phi = acos(P_pro_p_k / abs_pro_p);

	double P_p_k;
	int k;

	if (arista->h1.v[2] > 0.0)
		P_p_k = arista->h1.v[2];
	else
		P_p_k = -arista->h1.v[2];

	double abs_p = arista->h1.norma;
	double teta = acos(P_p_k / abs_p);

	arista->Rz_phi1 = initRotation(phi);
	arista->Rz_phi2 = initRotation(-phi);
	arista->Ry_teta2 = initRotationY(-teta);
	arista->Ry_teta1 = initRotationY(teta);

	if (equalDouble(teta, 0) == 1) {
		for (k = 0; k < 10; k++)
			updateVectorType1(&arista->points.A[k], addVectorGo(arista->points.A[k], arista->h3));}
	else {
		if (arista->D.v[1] > 0.0) {
			for (k = 0; k < 10; k++) {
				rot3DP(&arista->Ry_teta1, &arista->points.A[k]);
				rot3DP(&arista->Rz_phi2, &arista->points.A[k]);
			}
		} else {

			for (k = 0; k < 10; k++) {
				rot3DP(&arista->Ry_teta1, &arista->points.A[k]);
				rot3DP(&arista->Rz_phi1, &arista->points.A[k]);
			}			
		}

		for (k = 0; k < 10; k++)
			updateVectorType1(&arista->points.A[k], addVectorGo(arista->points.A[k], arista->h3));
	}
	arista->mesh = creaMatrixFacet(1, 16);

	facet(&arista->mesh.A[0][0], arista->points.A[0], arista->points.A[1], arista->points.A[2]);
	facet(&arista->mesh.A[0][1], arista->points.A[0], arista->points.A[2], arista->points.A[3]);

	facet(&arista->mesh.A[0][2], arista->points.A[0], arista->points.A[3], arista->points.A[4]);
	facet(&arista->mesh.A[0][3], arista->points.A[0], arista->points.A[4], arista->points.A[1]);

	facet(&arista->mesh.A[0][4], arista->points.A[1], arista->points.A[4], arista->points.A[8]);
	facet(&arista->mesh.A[0][5], arista->points.A[8], arista->points.A[5], arista->points.A[1]);

	facet(&arista->mesh.A[0][6], arista->points.A[2], arista->points.A[6], arista->points.A[7]);
	facet(&arista->mesh.A[0][7], arista->points.A[7], arista->points.A[3], arista->points.A[2]);

	facet(&arista->mesh.A[0][8], arista->points.A[4], arista->points.A[3], arista->points.A[7]);
	facet(&arista->mesh.A[0][9], arista->points.A[7], arista->points.A[8], arista->points.A[4]);

	facet(&arista->mesh.A[0][10], arista->points.A[1], arista->points.A[5], arista->points.A[6]);
	facet(&arista->mesh.A[0][11], arista->points.A[6], arista->points.A[2], arista->points.A[1]);

	facet(&arista->mesh.A[0][12], arista->points.A[9], arista->points.A[6], arista->points.A[5]);
	facet(&arista->mesh.A[0][13], arista->points.A[9], arista->points.A[7], arista->points.A[6]);

	facet(&arista->mesh.A[0][14], arista->points.A[9], arista->points.A[8], arista->points.A[7]);
	facet(&arista->mesh.A[0][15], arista->points.A[9], arista->points.A[5], arista->points.A[8]);
}

void aristaSet(struct Arista * arista, Vector a, Vector b, double width) {

	Vector D = subVectorGo(a, b);
	if (D.v[2] < 0.0) aristaGo(arista, a, b, width);
	else aristaGo(arista, b, a, width);

}

void renderArista(struct Arista arista, struct rotationMats U) {

	int i;
	for (i = 0; i < arista.mesh.n; i++)
		renderFacet(arista.mesh.A[0][i], U, 0);
}

void aristaUpdate(struct Arista * arista, Vector a, Vector b, double width) {

	arista->head = a;
	arista->base = b;
	arista->width = width;

	subVector(&arista->head, arista->base);
	updateVectorR3(&arista->D, arista->head.w[0], arista->head.w[1], arista->head.w[2]);

	updateVectorR3(&arista->h0, arista->D.v[0], arista->D.v[1], 0.0);
	updateVectorR3(&arista->h1, arista->D.v[0], arista->D.v[1], arista->D.v[2]);
	updateVectorR3(&arista->h2, 0.0, 0.0, arista->D.v[2]);
	updateVectorR3(&arista->h3, 
								arista->D.v[0]*0.5 + arista->base.v[0], 
								arista->D.v[1]*0.5 + arista->base.v[1], 
								arista->D.v[2]*0.5 + arista->base.v[2]
								);
	arista->longitud = 0.5 * distanceVector(arista->head, arista->base);
	double ajuste = 1.05;
	
	//vectorCapsuleGo(&arista->points, 10);
	updateVectorR3(&arista->points.A[0], 0.0, 0.0, arista->longitud);
	updateVectorR3(&arista->points.A[1], width, width, arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[2],-width, width, arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[3],-width,-width, arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[4], width,-width, arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[5], width, width,-arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[6],-width, width,-arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[7],-width,-width,-arista->longitud * ajuste);
	updateVectorR3(&arista->points.A[8], width,-width,-arista->longitud * ajuste);		
	updateVectorR3(&arista->points.A[9], 0.0, 0.0,-arista->longitud);

	double P_pro_p_k = arista->h0.v[0];
	double abs_pro_p = arista->h0.norma;
	double phi = acos(P_pro_p_k / abs_pro_p);

	double P_p_k;
	int k;

	if (arista->h1.v[2] > 0.0)
		P_p_k = arista->h1.v[2];
	else
		P_p_k = -arista->h1.v[2];

	double abs_p = arista->h1.norma;
	double teta = acos(P_p_k / abs_p);

	//arista->Rz_phi1 = initRotation(phi);
	//arista->Rz_phi2 = initRotation(-phi);
	//arista->Ry_teta2 = initRotationY(-teta);
	//arista->Ry_teta1 = initRotationY(teta);

	if (equalDouble(teta, 0) == 1) {
		for (k = 0; k < 10; k++) {
			addVector(&arista->points.A[k], arista->h3);
			updateVectorR3(&arista->points.A[k], arista->points.A[k].w[0], arista->points.A[k].w[1], arista->points.A[k].w[2]);}
		}
	else {
		if (arista->D.v[1] > 0.0) {
			for (k = 0; k < 10; k++) {
				rot3DP(&arista->Ry_teta1, &arista->points.A[k]);
				rot3DP(&arista->Rz_phi2, &arista->points.A[k]);
			}
		} else {

			for (k = 0; k < 10; k++) {
				rot3DP(&arista->Ry_teta1, &arista->points.A[k]);
				rot3DP(&arista->Rz_phi1, &arista->points.A[k]);
			}			
		}

		for (k = 0; k < 10; k++) {
			addVector(&arista->points.A[k], arista->h3);
			updateVectorR3(&arista->points.A[k], arista->points.A[k].w[0], arista->points.A[k].w[1], arista->points.A[k].w[2]);
		}
	}
	//printf("\n\n");
	//arista->mesh = creaMatrixFacet(1, 16);

	updateFacet(&arista->mesh.A[0][0], arista->points.A[0], arista->points.A[1], arista->points.A[2]);
	updateFacet(&arista->mesh.A[0][1], arista->points.A[0], arista->points.A[2], arista->points.A[3]);

	updateFacet(&arista->mesh.A[0][2], arista->points.A[0], arista->points.A[3], arista->points.A[4]);
	updateFacet(&arista->mesh.A[0][3], arista->points.A[0], arista->points.A[4], arista->points.A[1]);

	updateFacet(&arista->mesh.A[0][4], arista->points.A[1], arista->points.A[4], arista->points.A[8]);
	updateFacet(&arista->mesh.A[0][5], arista->points.A[8], arista->points.A[5], arista->points.A[1]);

	updateFacet(&arista->mesh.A[0][6], arista->points.A[2], arista->points.A[6], arista->points.A[7]);
	updateFacet(&arista->mesh.A[0][7], arista->points.A[7], arista->points.A[3], arista->points.A[2]);

	updateFacet(&arista->mesh.A[0][8], arista->points.A[4], arista->points.A[3], arista->points.A[7]);
	updateFacet(&arista->mesh.A[0][9], arista->points.A[7], arista->points.A[8], arista->points.A[4]);

	updateFacet(&arista->mesh.A[0][10], arista->points.A[1], arista->points.A[5], arista->points.A[6]);
	updateFacet(&arista->mesh.A[0][11], arista->points.A[6], arista->points.A[2], arista->points.A[1]);

	updateFacet(&arista->mesh.A[0][12], arista->points.A[9], arista->points.A[6], arista->points.A[5]);
	updateFacet(&arista->mesh.A[0][13], arista->points.A[9], arista->points.A[7], arista->points.A[6]);

	updateFacet(&arista->mesh.A[0][14], arista->points.A[9], arista->points.A[8], arista->points.A[7]);
	updateFacet(&arista->mesh.A[0][15], arista->points.A[9], arista->points.A[5], arista->points.A[8]);
}

void updateArista(struct Arista * arista, Vector a, Vector b, double width) {

	updateVectorR3(&arista->help, a.v[0] - b.v[0],  a.v[1] - b.v[1],  a.v[2] - b.v[2]);
	if (arista->help.v[2] < 0.0) aristaUpdate(arista, a, b, width);
	else aristaUpdate(arista, b, a, width);

}

struct Arista dilateArista(struct Arista arista, Vector d, double lambda) {

	Vector a = dilateVector(arista.head, d, lambda);
	Vector b = dilateVector(arista.base, d, lambda);
	struct Arista ret;
	aristaSet(&ret, a, b, arista.width);

	return ret;
}

struct Arista rotateArista(struct Arista arista, struct rotationMats A) {

	struct Arista ret;
	Vector a = rot3DAxe(&A, arista.head);
	Vector b = rot3DAxe(&A, arista.base);
	aristaSet(&ret, a, b, arista.width);

	return ret;
}

MatrixArista creaEspacioMatrixArista(int m, int n) {
  MatrixArista ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (struct Arista**) malloc (m * sizeof(struct Arista*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (struct Arista *) malloc (n * sizeof(struct Arista));
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

MatrixAristaList initMatrixAristaList(int n) {
	MatrixAristaList ret = {
						n : n,
						m : NULL
					};

	ret.m = (MatrixArista *) malloc (n * sizeof(MatrixArista));

	return ret;
}

///////////////

	//CUBIC MESH

///////////////

void initVecindadCubica(struct VecindadCubica * cubo, Vector center, double radius) {

	cubo->center = center;
	cubo->radius = radius;

	cubo->mesh = creaMatrixFacet(1, 12);

	int i0 = center.v[0];
	int j0 = center.v[1];

	if ((i0 * j0 + 1)%8 == 0) cubo->color = 0;
	if ((i0 * j0 + 1)%8 == 1) cubo->color = 1;
	if ((i0 * j0 + 1)%8 == 2) cubo->color = 2;
	if ((i0 * j0 + 1)%8 == 3) cubo->color = 3;
	if ((i0 * j0 + 1)%8 == 4) cubo->color = 4;
	if ((i0 * j0 + 1)%8 == 5) cubo->color = 5;
	if ((i0 * j0 + 1)%8 == 6) cubo->color = 6;
	if ((i0 * j0 + 1)%8 == 7) cubo->color = 7;


	facet(&cubo->mesh.A[0][0], 
								vector3DFast( radius + center.v[0], radius + center.v[1], radius + center.v[2]),
								vector3DFast(-radius + center.v[0], radius + center.v[1], radius + center.v[2]),
								vector3DFast(-radius + center.v[0],-radius + center.v[1], radius + center.v[2]));

	facet(&cubo->mesh.A[0][1], 
								vector3DFast(-radius + center.v[0],-radius + center.v[1], radius + center.v[2]),
								vector3DFast( radius + center.v[0],-radius + center.v[1], radius + center.v[2]),
								vector3DFast( radius + center.v[0], radius + center.v[1], radius + center.v[2]));

	facet(&cubo->mesh.A[0][2], 
								vector3DFast( radius + center.v[0], radius + center.v[1],-radius + center.v[2]),
								vector3DFast( radius + center.v[0],-radius + center.v[1],-radius + center.v[2]),
								vector3DFast(-radius + center.v[0],-radius + center.v[1],-radius + center.v[2]));

	facet(&cubo->mesh.A[0][3], 
								vector3DFast(-radius + center.v[0],-radius + center.v[1],-radius + center.v[2]),
								vector3DFast(-radius + center.v[0], radius + center.v[1],-radius + center.v[2]),
								vector3DFast( radius + center.v[0], radius + center.v[1],-radius + center.v[2]));
}

void updateVecindadCubica(struct VecindadCubica * cubo, Vector newCenter, double newRadius) {

	updateVectorR3(&cubo->center, newCenter.v[0], newCenter.v[1], newCenter.v[2]);
	cubo->radius = newRadius;
	updateFacet(&cubo->mesh.A[0][0], 
								vector3DFast( newRadius + newCenter.v[0], newRadius + newCenter.v[1], newRadius + newCenter.v[2]),
								vector3DFast(-newRadius + newCenter.v[0], newRadius + newCenter.v[1], newRadius + newCenter.v[2]),
								vector3DFast(-newRadius + newCenter.v[0],-newRadius + newCenter.v[1], newRadius + newCenter.v[2]));

	updateFacet(&cubo->mesh.A[0][1], 
								vector3DFast(-newRadius + newCenter.v[0],-newRadius + newCenter.v[1], newRadius + newCenter.v[2]),
								vector3DFast( newRadius + newCenter.v[0],-newRadius + newCenter.v[1], newRadius + newCenter.v[2]),
								vector3DFast( newRadius + newCenter.v[0], newRadius + newCenter.v[1], newRadius + newCenter.v[2]));

	updateFacet(&cubo->mesh.A[0][2], 
								vector3DFast( newRadius + newCenter.v[0], newRadius + newCenter.v[1],-newRadius + newCenter.v[2]),
								vector3DFast( newRadius + newCenter.v[0],-newRadius + newCenter.v[1],-newRadius + newCenter.v[2]),
								vector3DFast(-newRadius + newCenter.v[0],-newRadius + newCenter.v[1],-newRadius + newCenter.v[2]));

	updateFacet(&cubo->mesh.A[0][3], 
								vector3DFast(-newRadius + newCenter.v[0],-newRadius + newCenter.v[1],-newRadius + newCenter.v[2]),
								vector3DFast(-newRadius + newCenter.v[0], newRadius + newCenter.v[1],-newRadius + newCenter.v[2]),
								vector3DFast( newRadius + newCenter.v[0], newRadius + newCenter.v[1],-newRadius + newCenter.v[2]));


}

void renderVecindadCubica (struct VecindadCubica cubo, struct rotationMats U) {

	int i;
	//int color;
	//if ((int)(cubo.center.v[0] + cubo.center.v[1])%3 == 0) color = 0;
	//if ((int)(cubo.center.v[0] + cubo.center.v[1])%3 == 1) color = 1;
	//if ((int)(cubo.center.v[0] + cubo.center.v[1])%3 == 2) color = 2;

	for (i = 0; i < 4; i++) {
		renderFacet(cubo.mesh.A[0][i], U, cubo.color);
	}
}


MatrixVecindadCubica creaEspacioMatrixVecindadCubica(int m, int n) {
  MatrixVecindadCubica ret = {
                  m : m,
                  n : n, 
                  A : NULL
                };
  int i;
  ret.A = (struct VecindadCubica**) malloc (m * sizeof(struct VecindadCubica*));
  if (ret.A != NULL){
    for(i = 0; i < m; i++){
      ret.A[i] = (struct VecindadCubica *) malloc (n * sizeof(struct VecindadCubica));
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
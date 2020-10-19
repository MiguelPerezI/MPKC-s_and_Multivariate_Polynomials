#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "vector.h"
#include "Matrix.h"
#include "Arista.h"
#include "Hilbert.h"
#include "turtle.h"
#include "fractalCurves.h"
#include "Tree.h"
#include "polinomios.h"

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 0.25, 0.0};

/*variables*/ 
int ciclo = 0;
int cicloSegund = 0;
int color = 0;
double count = 0.0;
double rotSpeed = 0.0;
int iter = 5;

Vector center;
Vector I, minusI;
Vector J, minusJ;
Vector K, minusK;
Vector K0;
double gold = 1.618;
double g1 = 1/1.618;
double g2 = (1/1.618) * (1/1.618);

/*Estructuras Matematicas*/
struct rotationMats U;

Vector hil0;
Vector hil1;
Vector hil2;
Vector hil3;

double width;

struct Arista arista21;
struct Arista arista22;
struct Arista arista23;

struct Turtle turtle;

struct KochFractal koch;
struct GosperFractal gosper;
struct HilbertFractal hhilbert;
struct SierspinskiCurve sier;
struct LevyCurve levy;
struct DragonCurve dragon;

struct Leaf leafs;

struct VecindadCubica vecin;

struct AnilloZp anillo;
PolinomioZp p, pp;
PolinomioZp q;
int additionL = 0;
int additionR = 0;

int subtractionL = 0;
int subtractionR = 0;

int multiplicationL = 0;

PolinomioZp p0;
PolinomioZp q0;
PolinomioZp r0;
PolinomioZp s0;
PolinomioZp qq;
PolinomioZp p1;

void display(void);
void init(double theta);
void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void ProcessMenu(int value);

int main(int argc, char **argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1300, 1300);
  glutCreateWindow(" ------- Fractals ------- ");
  ProcessMenu(1);
  init(count);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(20, TimerFunction, 1);

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


///////////////////////////////////////////

void display(void) {
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  if (ciclo == 0) {

    U = initRotation(count);
    vectorGo(&center, 3, 0.0, 0.0, 0.0);
    vectorGo(&I, 3, 1.0, 0.0, 0.0);
    vectorGo(&J, 3, 0.0, 1.0, 0.0);
    vectorGo(&K, 3, 0.0, 0.0, 1.0);
    vectorGo(&K0, 3, 0.0, 0.0, 1.0);
    vectorGo(&minusI, 3,-1.0, 0.0, 0.0);
    vectorGo(&minusJ, 3, 0.0,-1.0, 0.0);
    vectorGo(&minusK, 3, 0.0, 0.0,-1.0);
    double radius = 1;
    
    width = 0.03;
    
    vectorGo(&hil0, 3, 1.0, 1.0, 0.0);
    vectorGo(&hil1, 3,-1.0, 1.0, 0.0);
    vectorGo(&hil2, 3,-1.0,-1.0, 0.0);
    vectorGo(&hil3, 3, 1.0,-1.0, 0.0);

    aristaSet(&arista21, center, I, width);
    aristaSet(&arista22, center, J, width);
    aristaSet(&arista23, center, K, width);

//    initKochFractal(&koch, hil2, hil0, 5);
//    initPath(&koch);
//
//    initGosperFractal(&gosper, vector3DFast(0.5, 0.6, 0.5), hil0, 4);
//    initPathGosper(&gosper);
//
//    initHilbertFractal(&hhilbert, vector3DFast(-1.5, 0.0, 0.0), hil0, 6);
//    initPathHilbert(&hhilbert);

//    initSierspinskiCurve(&sier, vector3DFast(-1.5, 0.0, 0.0), hil0, 6);
//    initPathSierspinskiCurve(&sier);
    //initLevyCurve(&levy, vector3DFast(0, 0.0, 0.0), hil0, 12);
    //initPathLevyCurve(&levy);
    initDragonCurve(&dragon, vector3DFast(0, 0.0, 0.0), hil0, 13);
    initPathDragonCurve(&dragon);

    initTurtle(&turtle, center, vector3DFast(0.0, 0.0, 1.0), 0.5, 0.25 * 3.1415, 9);
    ///////////////////////////////////////////////////
//    /*SR*/saveAxeRotTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 1.0); //1
//    /*RY*/rotYTurtle(&turtle);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 1.0); //2
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 1.0); //3
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 1.0); //4
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 1.0); //5
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*Cycle 1*//////////////////////////////////////
//    /*SR*/saveAxeRotTurtle(&turtle);
//    /*FJ*/jumpForwardTurtleSpace(&turtle);
//    /*RY*/rotYTurtle(&turtle);
//
//    turtle.stepF *= 0.5;
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 0.5); // 6
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 0.5); //3
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 0.5); //4
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);
//
//    /*S*/saveTurtle(&turtle);
//    /*F*/forwardTurtleSpace(&turtle, 0.5); //5
//    /*B*/goBackTurtle(&turtle);
//
//    /*RA*/rot1TTurtle(&turtle, 0.5 * 3.1415);



    initAnilloZp(&anillo, 2, 11);/************************************************/
    printAnilloZp(anillo);

    initPolinomioZp(&p, 11, 2,   1, 0);//(((((())))))
    initPolinomioZp(&pp, 11, 2,   1, 1);//(((((())))))
    
    initPolinomioZp(&q, 11, 2,   0, 1);
    initPolinomioZp(&p0, 4, 5,   2, 0, 2, 0, 0);

    //Given p(x) and q(x) find the residue of p(x)/q(x)
    initPolinomioZp(&q0, 3, 1,   2);
    initPolinomioZp(&s0, 3, 1,   0);

    /*Let qq by irreducible in Z3*/
    printf("<--- Zp Software --->\n");
    initPolinomioZp(&qq, 3, 3,   1, 0, 1);

    printf("\n\n p(x) := ");
    printPolinomioZp(s0); printf("\n p0(x) = ");
    printPolinomioZp(q0);
    
    //Here we multiply s0(x)q0(x)
    r0 = multPolinomioZp(s0, q0);
    printf("\n\n");

    //We calculate the residue of (s0(x)q0(x))/qq(x)
    p1 = modP(r0, qq);

    printf("\nresidue = ");
    printPolinomioZp(p1);
    printf("\n\n\n");


    MatrixV points;
    points = creaEspacioMatrixV(1, 8);

    points.A[0][0] = vector3DFast( 1.0, 1.0, 1.0);
    points.A[0][1] = vector3DFast(-1.0, 1.0, 1.0);
    points.A[0][2] = vector3DFast(-1.0,-1.0, 1.0);
    points.A[0][3] = vector3DFast( 1.0,-1.0, 1.0);

    points.A[0][4] = vector3DFast( 1.0, 1.0,-1.0);
    points.A[0][5] = vector3DFast(-1.0, 1.0,-1.0);
    points.A[0][6] = vector3DFast(-1.0,-1.0,-1.0);
    points.A[0][7] = vector3DFast( 1.0,-1.0,-1.0);

    initLeafsInTree(&leafs, points, 0.1);
    initVecindadCubica(&vecin, J, 0.06);
  }

  if (multiplicationL%2 == 1) {
    printf("* -->(1, 1)\n");
    multiplicationInZp(&anillo, pp);
    printAnilloZp(anillo);
    multiplicationL += 1;
  }

  if (additionL %2 == 1) {
    printf("+ -->(1, 0)\n");
    additionInZp(&anillo, p);
    printAnilloZp(anillo);
    additionL += 1;
  }

  if (additionR%2 == 1) {
    printf("+ -->(0, 1)\n");
    additionInZp(&anillo, q);
    printAnilloZp(anillo);
    additionR += 1;
  }

  if (subtractionL%2 == 1) {
    printf("- -->(1, 0)\n");
    subtractionInZp(&anillo, p);
    printAnilloZp(anillo);
    subtractionL += 1;
  }

  if (subtractionR%2 == 1) {
    printf("- -->(0, 1)\n");
    subtractionInZp(&anillo, q);
    printAnilloZp(anillo);
    subtractionR += 1;
  }

  renderAnilloZp(anillo, U);
  updateVectorR3(&K, 0, 0, cos(count));
  updateRotation(&U, rotSpeed);

  //renderHilbertCurve(hilbertCurve, U);
  //renderArista(arista21, U);
  //renderArista(arista22, U);
  //renderArista(arista23, U);

  //Fractales para entregar
  //renderKochFractal(koch, U);
  //renderGosperFractal(gosper, U);
  //renderHilbertFractal(hhilbert, U, iter);
  //renderSierspinskiCurve(sier, U);
  
  //if (iter > levy.turtle.Max) iter = 1;
  //if (iter < 0) iter = levy.turtle.Max - 1;
  //renderLevyCurve(levy, U, iter);

  //if (iter > dragon.turtle.Max) iter = 1;
  //if (iter < 0) iter = dragon.turtle.Max - 1;
  renderDragonCurve(dragon, U, iter);
  //renderArista(turtle.path.A[0][0], U);
  //renderArista(turtle.path.A[0][1], U);
  //renderArista(turtle.path.A[0][2], U);
  //renderArista(turtle.path.A[0][3], U);
  //renderArista(turtle.path.A[0][4], U);
  //renderArista(turtle.path.A[0][5], U);
  //renderArista(turtle.path.A[0][6], U);
  //renderArista(turtle.path.A[0][7], U);
  //renderArista(turtle.path.A[0][8], U);
  //showTurtleHead(turtle, U);
  //renderVecindadCubica (vecin, U);


  //renderLeafsInTree(leafs, U);

  glutSwapBuffers();
}

///////////////////////////////////////////

void init(double theta)
{
  /* Setup data. */
  GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  //glEnable(GL_CULL_FACE);

  /*Enable color tracking*/
  glEnable(GL_COLOR_MATERIAL);

  /* Set material properties to follow glColor values*/
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  /*All materials have high shine*/
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
                              /* aspect ratio */ 1.0,
                                    /* Z near */ 0.5, 
                                    /* Z far */ 10000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(  10,  3, 21,      /* eye is at (0,0,5) */
          -1.0, 1.0, 0.0,      /* center is at (0,0,0) */
            0.0, 0.0, 1.0);      /* up is in positive Y direction */

  /* Adjust Board position to be asthetic angle. */
  //glTranslatef(0.0, 0.15, -0.0);
  glRotatef(90, 0.0, 0.0, 1.0);

  glEnable(GL_NORMALIZE);
}

void TimerFunction(int value) {

  count += 0.05;
  rotSpeed += 0.00;
  ciclo += 1;

  if (count > 2 * M_PI) count = 0;
  if (ciclo > 100) ciclo = 1;

  glutPostRedisplay();
  glutTimerFunc(20, TimerFunction, 1);
}

void keyboard(unsigned char key, int x, int y) {
  GLint params[2];

  switch (key) {

    case 'a': 
      additionL += 1;
      break;

    case 'd': 
      multiplicationL += 1;
      break;

    case 'A': 
      subtractionL += 1;
      break;

    case 's': 
      additionR += 1;
      break;

    case 'S': 
      subtractionR += 1;
      break;

    case 'w': 
      ciclo += 1;
      break;

    case 'n': 
      cicloSegund += 1;
      break;

    case 'c': 
      color += 1;
      break;

    case 'i': 
      iter += 3;
      break;

    case 'I': 
      iter -= 1;
      break;

    case 'r': 
      rotSpeed += 0.02;
      break;

    case 'R': 
      rotSpeed -= 0.02;
      break;
  }

  glutPostRedisplay();
}

void ProcessMenu(int value) {
  switch(value) {
    case 1:
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_POINT_SMOOTH);
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_LINE_SMOOTH);
      glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_POLYGON_SMOOTH);
      glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
      break;

    case 2:
      glDisable(GL_BLEND);
      glDisable(GL_LINE_SMOOTH);
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_POLYGON_SMOOTH);
      break;
    
    default:
      break;
  }

  glutPostRedisplay();
}

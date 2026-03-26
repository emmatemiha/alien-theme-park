//  ========================================================================
//  COSC363: Computer Graphics (2025);  University of Canterbury.
//
//  FILE NAME: Main.cpp
//  
//  ========================================================================

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>
#include "Models.h"

// add these globals near the top of main.cpp
float camAngle = 0.0f;
float camX = 0.0f, camZ = 8.0f;
bool specialStates[256] = { false };
float camHeight = -2.0f;

float swingAngle = 1.0f;
float swingSpeed = 0.0f;
const float gravity = 9.8f;
const float armLength = 8.0f;

void initialise(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    float lightPos[] = { 10, 20, 10, 1 };
    float white[] = { 1, 1, 1, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

    //glClearColor(0.8, 0.8, 0.8, 1.);
    glClearColor(0.0, 0.075, 0.412, 1.);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60., 1., 10., 1000.);
    gluPerspective(60., 1., 0.5, 1000.);
}

// add these two callback functions
void special(int key, int x, int y) {
    specialStates[key] = true;
}
void specialUp(int key, int x, int y) {
    specialStates[key] = false;
}

// add a timer to update camera each frame
void timer(int value) {

    float acceleration = -(gravity / armLength) * sin(swingAngle);
    swingSpeed += acceleration * 0.016f;
    swingAngle += swingSpeed * 0.016f;

    if (specialStates[GLUT_KEY_LEFT])  camAngle -= 1.0f;
    if (specialStates[GLUT_KEY_RIGHT]) camAngle += 1.0f;
    if (specialStates[GLUT_KEY_UP])    camZ -= 0.1f;
    if (specialStates[GLUT_KEY_DOWN])  camZ += 0.1f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') camHeight += 0.2f;  // look more from above
    if (key == 's') camHeight -= 0.2f;  // look more from below
    if (key == 27)  exit(0);            // ESC to quit
    glutPostRedisplay();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, camHeight, -camZ);
    glRotatef(camAngle, 0, 1, 0);

    drawFloor();
    //drawSpaceship1();
    //drawSpaceship2();
    drawRideStructure(swingAngle);

    glPushMatrix();
        glTranslatef(-5.0, 0.0, 0.0);
        drawAlien();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(5, 5);
    glutCreateWindow("Spaceship");
    initialise();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
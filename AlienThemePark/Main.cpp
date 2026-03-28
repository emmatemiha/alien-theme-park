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
#include "loadBMP.h"

// add these globals near the top of main.cpp
float camAngle = 0.0f;
float camX = 0.0f, camZ = 35.0f;
bool specialStates[256] = { false };
float camHeight = -2.0f;

float swingAngle = 1.0f;
float swingSpeed = 0.0f;
const float gravity = 9.8f;
const float armLength = 8.0f;

GLuint txId[2];
GLUquadric* q;

void loadTexture() {
    glGenTextures(2, txId);
    
    //sky
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadBMP("textures/sky.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //moon
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    loadBMP("textures/2k_mercury.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initialise(void) {
    loadTexture();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //float lightPos[] = { 10, 20, 10, 1 };
    //float white[] = { 1, 1, 1, 1 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glClearColor(0.0, 0.075, 0.412, 1.);

    q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);
    //glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
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

    float lightPos[] = { 10, 20, 10, 1 };
    float white[] = { 1, 1, 1, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

    float ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // skybox
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glDepthMask(GL_FALSE);
    glPushMatrix();
        glRotatef(180.0, 0, 1, 0);
        glScalef(-1.0, 1.0, 1.0);
        gluSphere(q, 200.0, 64, 64);
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    drawFloor(txId[1]);
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
    glutCreateWindow("Alien Theme Park");
    initialise();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
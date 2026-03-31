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

// for the camera movements
float camAngle = 0.0f;
float camX = 0.0f, camZ = 35.0f;
bool specialStates[256] = { false };
float camHeight = -2.0f;
bool keyStates[256] = { false };

// for the ride to swing
float swingAngle = 1.0f;
float swingSpeed = 0.0f;
const float gravity = 9.8f;
const float armLength = 8.0f;

GLuint txId[2];
GLUquadric* q;

// for the aliens to move (arms, antennas and legs)
float alienArmAngle = 0.0f;
float alienAntennaAngle = 0.0f;
float alienFrame = 0.0f;
float alienLegAngle = 0.0f;

// for the pink alien to move around
// states: 0 = walking to seat, 1 = sitting on ground waiting,
//         2 = going up on ride,  3 = riding,
//         4 = coming back down,  5 = walking away
float pinkAlien_x = -8.0f;
float pinkAlien_z = 8.0f;
int   pinkAlien_state = 0;
float pinkAlien_rideTimer = 0.0f;

// for the blue alien to move around
// states: 0 = walking to seat, 1 = sitting on ground waiting,
//         2 = going up on ride,  3 = riding,
//         4 = coming back down,  5 = walking away
float blueAlien_x = 8.0f;
float blueAlien_z = 10.0f;
int   blueAlien_state = 0;
float blueAlien_rideTimer = 0.0f;

// to lower and raise the ride so the aliens can get on it
float rideHeight = 0.0f;
bool rideLiftingUp = false;
bool rideComingDown = false;

void loadTexture() {
    glGenTextures(2, txId);
    
    //sky
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadBMP("textures/daysky.bmp");
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
    glClearColor(0.0, 0.075, 0.412, 1.);

    q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60., 1., 0.5, 1000.);
}

void special(int key, int x, int y) {
    specialStates[key] = true;
}
void specialUp(int key, int x, int y) {
    specialStates[key] = false;
}

void keyboard(unsigned char key, int x, int y) {
    keyStates[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void timer(int value) {

    // for aliens to move
    alienFrame += 0.05f;
    alienArmAngle = 18.0f * sin(alienFrame);
    alienAntennaAngle = -25.0f * sin(alienFrame);
    alienLegAngle = 20.0f * sin(alienFrame);

    // for rides pendulum swing
    float acceleration = -(gravity / armLength) * sin(swingAngle);
    swingSpeed += acceleration * 0.016f;
    swingAngle += swingSpeed * 0.016f;

    // camera movements
    if (specialStates[GLUT_KEY_DOWN])  camHeight += 0.2f;
    if (specialStates[GLUT_KEY_UP])    camHeight -= 0.2f;
    if (specialStates[GLUT_KEY_LEFT])  camX -= 0.2f;
    if (specialStates[GLUT_KEY_RIGHT]) camX += 0.2f;
    if (keyStates['w']) camZ -= 0.2f;
    if (keyStates['s']) camZ += 0.2f;
    if (keyStates['a']) camAngle -= 1.0f;
    if (keyStates['d']) camAngle += 1.0f;







    // FOR THE PINK ALIEN TO GO ON THE LEFT SEAT
    float leftSeatX = -6.0f;
    float leftSeatZ = -3.0f;

    if (pinkAlien_state == 0) {
        float distanceX = leftSeatX - pinkAlien_x;
        float distanceZ = leftSeatZ - pinkAlien_z;
        float totalDistance = sqrt(distanceX * distanceX + distanceZ * distanceZ);
        if (totalDistance < 0.5f) {
            pinkAlien_state = 1;
        }
        else {
            pinkAlien_x += (distanceX / totalDistance) * 0.04f;
            pinkAlien_z += (distanceZ / totalDistance) * 0.04f;
        }
    }
    else if (pinkAlien_state == 1) { }
    else if (pinkAlien_state == 2) { }
    else if (pinkAlien_state == 3) {
        pinkAlien_rideTimer += 0.016f;
        if (pinkAlien_rideTimer > 8.0f && rideHeight >= 8.0f) {
            pinkAlien_state = 4;
            pinkAlien_rideTimer = 0.0f;
            rideComingDown = true;
        }
    }
    else if (pinkAlien_state == 4) {
        if (rideHeight <= 0.0f && fabs(swingAngle) < 0.3f) {
            pinkAlien_state = 5;
            pinkAlien_x = leftSeatX;
            pinkAlien_z = leftSeatZ;
        }
    }
    else if (pinkAlien_state == 5) {
        float distanceX = -8.0f - pinkAlien_x;
        float distanceZ = 8.0f - pinkAlien_z;
        float totalDistance = sqrt(distanceX * distanceX + distanceZ * distanceZ);
        if (totalDistance < 0.5f) {
            pinkAlien_state = 0;
        }
        else {
            pinkAlien_x += (distanceX / totalDistance) * 0.04f;
            pinkAlien_z += (distanceZ / totalDistance) * 0.04f;
        }
    }

    // FOR THE BLUE ALIEN TO GO ON THE LEFT SEAT
    float rightSeatX = 6.0f;
    float rightSeatZ = 3.0f;

    if (blueAlien_state == 0) {
        float distanceX = rightSeatX - blueAlien_x;
        float distanceZ = rightSeatZ - blueAlien_z;
        float totalDistance = sqrt(distanceX * distanceX + distanceZ * distanceZ);
        if (totalDistance < 0.5f) {
            blueAlien_state = 1;
        }
        else {
            blueAlien_x += (distanceX / totalDistance) * 0.04f;
            blueAlien_z += (distanceZ / totalDistance) * 0.04f;
        }
    }
    else if (blueAlien_state == 1) { }
    else if (blueAlien_state == 2) { }
    else if (blueAlien_state == 3) {
        blueAlien_rideTimer += 0.016f;
        if (blueAlien_rideTimer > 8.0f && rideHeight >= 8.0f) {
            blueAlien_state = 4;
            blueAlien_rideTimer = 0.0f;
            rideComingDown = true;
        }
    }
    else if (blueAlien_state == 4) {
        if (rideHeight <= 0.0f && fabs(swingAngle) < 0.3f) {
            blueAlien_state = 5;
            blueAlien_x = rightSeatX;
            blueAlien_z = rightSeatZ;
        }
    }
    else if (blueAlien_state == 5) {
        float distanceX = 8.0f - blueAlien_x;
        float distanceZ = 10.0f - blueAlien_z;
        float totalDistance = sqrt(distanceX * distanceX + distanceZ * distanceZ);
        if (totalDistance < 0.5f) {
            blueAlien_state = 0;
        }
        else {
            blueAlien_x += (distanceX / totalDistance) * 0.04f;
            blueAlien_z += (distanceZ / totalDistance) * 0.04f;
        }
    }

    if (pinkAlien_state == 1 && blueAlien_state == 1 && fabs(swingAngle) < 0.3f) {
        rideLiftingUp = true;
        pinkAlien_state = 2;
        blueAlien_state = 2;
    }

    if (rideLiftingUp) {
        rideHeight += 0.05f;
        if (rideHeight >= 8.0f) {
            rideHeight = 8.0f;
            rideLiftingUp = false;
            pinkAlien_state = 3;
            blueAlien_state = 3;
        }
    }

    if (rideComingDown) {
        rideHeight -= 0.05f;
        if (rideHeight <= 0.0f) {
            rideHeight = 0.0f;
            rideComingDown = false;
        }
    }











    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-camX, camHeight, -camZ);
    glRotatef(camAngle, 0, 1, 0);

    float lightPos[] = { 10, 20, 10, 1 };
    float white[] = { 1, 1, 1, 1 };
    float ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // skybox
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glDepthMask(GL_FALSE);
    glPushMatrix();
        glRotatef(180.0, 0, 1, 0);
        //glRotatef(-150, 1, 0, 0);
        glRotatef(120.0, 0, 1, 0);
        glScalef(-1.0, 1.0, 1.0);
        gluSphere(q, 200.0, 64, 64);
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    drawFloor(txId[1]);
    drawRideStructure(swingAngle, rideHeight, pinkAlien_state, blueAlien_state,
        alienArmAngle, alienAntennaAngle, alienLegAngle);

    // pink alien
    if (pinkAlien_state != 2 && pinkAlien_state != 3 && pinkAlien_state != 4) {
        glPushMatrix();
            glTranslatef(pinkAlien_x, -0.35f, pinkAlien_z);
            drawAlien(alienArmAngle, alienAntennaAngle, alienLegAngle, 1.0f, 0.6f, 0.75f);
        glPopMatrix();
    }

    // blue alien
    if (blueAlien_state != 2 && blueAlien_state != 3 && blueAlien_state != 4) {
        glPushMatrix();
            glTranslatef(blueAlien_x, -0.35f, blueAlien_z);
            drawAlien(alienArmAngle, alienAntennaAngle, alienLegAngle, 0.396f, 0.827f, 1.0f);
        glPopMatrix();
    }

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
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
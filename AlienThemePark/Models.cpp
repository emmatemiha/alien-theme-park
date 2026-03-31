//  ================================================================================
//  COSC363: Computer Graphics (2025);  University of Canterbury.
//
//  Models.cpp
//  A collection of functions for generating the models for an alien themepark scene
//  ================================================================================

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <GL/freeglut.h>
#include "Models.h"

void drawFloor(GLuint moonTex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, moonTex);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(0.8, 0.8, 0.8);

    GLUquadric* qPlanet = gluNewQuadric();
    gluQuadricTexture(qPlanet, GL_TRUE);
    gluQuadricNormals(qPlanet, GLU_SMOOTH);
    gluQuadricDrawStyle(qPlanet, GLU_FILL);

    glPushMatrix();
    glRotatef(-90.0, 1, 0, 0);
    gluDisk(qPlanet, 0.0, 20.0, 64, 8);
    glTranslatef(0.0, 0.0, -5.0);
    gluCylinder(qPlanet, 20.0, 20.0, 5.0, 64, 4);
    glPopMatrix();

    gluDeleteQuadric(qPlanet);

    glDisable(GL_TEXTURE_2D);
}


void drawAlien(float armAngle, float antennaAngle, float legAngle, float r, float g, float b) {
    // body
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.0, 0.8, 0.0);
        glScalef(0.6, 0.8, 0.6);
        glutSolidSphere(0.5, 16, 12);
    glPopMatrix();

    // head
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.0, 1.7, 0.0);
        glutSolidSphere(0.7, 24, 16);
    glPopMatrix();

    // left eye
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.28, 1.75, 0.55);
        glutSolidSphere(0.22, 16, 12);
    glPopMatrix();

    // left pupil
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.15);
        glTranslatef(-0.22, 1.83, 0.72);
        glutSolidSphere(0.1, 8, 6);
    glPopMatrix();

    // right eye
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.28, 1.75, 0.55);
        glutSolidSphere(0.22, 16, 12);
    glPopMatrix();

    // right pupil
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.15);
        glTranslatef(0.34, 1.83, 0.72);
        glutSolidSphere(0.1, 8, 6);
    glPopMatrix();

    // left antenna
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.4, 2.2, 0.0);
        glRotatef(-antennaAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.04, 0.6, 8, 1);
    glPopMatrix();

    // right antenna
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.4, 2.2, 0.0);
        glRotatef(antennaAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.04, 0.6, 8, 1);
    glPopMatrix();

    // left arm
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.25, 0.8, 0.0);
        glRotatef(60.0 + armAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // right arm
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.25, 0.8, 0.0);
        glRotatef(-60.0 - armAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // left leg
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.18, 0.35, 0.0);
        glRotatef(legAngle, 1, 0, 0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();

    // right leg
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.18, 0.35, 0.0);
        glRotatef(-legAngle, 1, 0, 0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();
}

void drawSpaceship1() { // THE PURPLE ONE
    // main saucer body
    glPushMatrix();
        glColor3f(0.427, 0.227, 0.839);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScalef(0.8f, 0.7f, 0.8f);
        glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, -0.18, 0.0);
        glScalef(2.4, 0.8, 2.4);
        glutSolidSphere(0.6, 32, 16);
    glPopMatrix();

    // top antenna pole
    glPushMatrix();
        glColor3f(0.7, 0.7, 0.75);
        glTranslatef(0.0, 1.2, 0.0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.03, 0.5, 12, 1);
    glPopMatrix();

    // ball on antenna
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, 1.7, 0.0);
        glutSolidSphere(0.08, 12, 6);
    glPopMatrix();

    // circles around edge
    glColor3f(1.0, 0.6, 0.1);

    for (int i = 0; i < 12; i++) {
        float angle = (2.0 * M_PI * i) / 12;
        float lx = 2.2 * cos(angle);
        float lz = 2.2 * sin(angle);
        glPushMatrix();
            glTranslatef(lx, 0.08, lz);
            glutSolidSphere(0.15, 12, 6);
        glPopMatrix();
    }

    // left seat base
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

}

void drawSpaceship2() { // THE GREEN ONE
    // main saucer body
    glPushMatrix();
        glColor3f(0.235, 0.58, 0.376);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top
    glPushMatrix();
        glColor3f(0.333, 0.871, 0.553);
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScalef(0.8f, 0.7f, 0.8f);
        glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, -0.18, 0.0);
        glScalef(2.4, 0.8, 2.4);
        glutSolidSphere(0.6, 32, 16);
    glPopMatrix();

    // top antenna polE
    glPushMatrix();
        glColor3f(0.7, 0.7, 0.75);
        glTranslatef(0.0, 1.2, 0.0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.03, 0.5, 12, 1);
    glPopMatrix();

    // ball on antenna
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, 1.7, 0.0);
        glutSolidSphere(0.08, 12, 6);
    glPopMatrix();

    // circles around rim
    glColor3f(1.0, 0.6, 0.1);

    for (int i = 0; i < 12; i++) {
        float angle = (2.0 * M_PI * i) / 12;
        float lx = 2.2 * cos(angle);
        float lz = 2.2 * sin(angle);
        glPushMatrix();
            glTranslatef(lx, 0.08, lz);
            glutSolidSphere(0.15, 12, 6);
        glPopMatrix();
    }

    // left seat base
    glPushMatrix();
        glColor3f(0.333, 0.871, 0.553);
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glColor3f(0.333, 0.871, 0.553);
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glColor3f(0.333, 0.871, 0.553);
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
        glColor3f(0.333, 0.871, 0.553);
        glTranslatef(1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawRideStructure(float swingAngle, float rideHeight, int pinkState, int blueState, float armAngle, float antennaAngle, float legAngle) { // THE POLES!
    float swingDegrees = swingAngle * 180.0 / M_PI;

    float shipY = rideHeight + 1.0f;
    float cableLength = 14.0f - rideHeight;

    // pole in middle
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.55);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.4, 15.0, 16, 1);
    glPopMatrix();

    // top bar (horizontal)
    glPushMatrix();
        glColor3f(0.45, 0.45, 0.5);
        glTranslatef(-8.0, 15.0, 0.0);
        glRotatef(90.0, 0, 1, 0);
        glutSolidCylinder(0.3, 16.0, 16, 1);
    glPopMatrix();

    // left cable and ship
    glPushMatrix();
        glTranslatef(-6.0, 15.0, 0.0);
        glRotatef(swingDegrees, 1, 0, 0);
        glTranslatef(6.0, -15.0, 0.0);

        // left cable
        glPushMatrix();
            glColor3f(0.4, 0.4, 0.45);
            glTranslatef(-6.0, shipY, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, cableLength, 8, 1);
        glPopMatrix();
        // left ship
        glPushMatrix();
            glTranslatef(-6.0, shipY, 0.0);
            glScalef(1.5, 1.5, 1.5);
            //glTranslatef(-4.0, (rideHeight / 1.5) + 0.5, 0.0);
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship1();
        glPopMatrix();

        // pink alien sits in spaceship 1 while on ride
        if (pinkState == 2 || pinkState == 3 || pinkState == 4) {
            glPushMatrix();
                glTranslatef(-6.0, shipY + 0.1, -3.0);
                glRotatef(180.0, 0, 1, 0);
                //glScalef(0.5, 0.5, 0.5);
                drawAlien(armAngle, antennaAngle, 0.0f, 1.0f, 0.6f, 0.75f);
            glPopMatrix();
        }
    glPopMatrix();

    // right cable and ship
    glPushMatrix();
        glTranslatef(6.0, 15.0, 0.0);
        glRotatef(-swingDegrees, 1, 0, 0);
        glTranslatef(-6.0, -15.0, 0.0);

        // right cable
        glPushMatrix();
            glColor3f(0.4, 0.4, 0.45);
            glTranslatef(6.0, shipY, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, cableLength, 8, 1);
        glPopMatrix();
        // right ship
        glPushMatrix();
            glTranslatef(6.0, shipY, 0.0);
            glScalef(1.5, 1.5, 1.5);
            //glTranslatef(4.0, (rideHeight / 1.5) + 0.5, 0.0);
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship2();
        glPopMatrix();

        // blue alien sits in spaceship 2 while on ride
        if (blueState == 2 || blueState == 3 || blueState == 4) {
            glPushMatrix();
                glTranslatef(6.0, shipY + 0.1, 3.0);
                //glScalef(0.5, 0.5, 0.5);
                drawAlien(armAngle, antennaAngle, 0.0f, 0.396f, 0.827f, 1.0f);
            glPopMatrix();
        }
    glPopMatrix();

    // green alien standing near the ride
    glPushMatrix();
        glTranslatef(15.0, -0.35, 4.0);
        drawAlien(armAngle, antennaAngle, 0.0f, 0.396f, 1.0f, 0.557f);
    glPopMatrix();

    // yellow alien standing near the ride
    glPushMatrix();
        glTranslatef(-17.0, -0.35, -3.0);
        drawAlien(armAngle, antennaAngle, 0.0f, 1.0f, 0.804f, 0.396f);
    glPopMatrix();

    // red alien standing near the ride
    glPushMatrix();
        glTranslatef(11.0, -0.35, -2.0);
        drawAlien(armAngle, antennaAngle, 0.0f, 1.0f, 0.396f, 0.396f);
    glPopMatrix();

    // purple alien standing near the ride
    glPushMatrix();
        glTranslatef(-11.0, -0.35, 6.0);
        drawAlien(armAngle, antennaAngle, 0.0f, 0.733f, 0.396f, 1.0f);
    glPopMatrix();
}
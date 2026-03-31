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
    //glColor3f(0.6, 0.6, 0.65);
    //glPushMatrix();
    //    glRotatef(-90.0, 1, 0, 0);
    //    glutSolidCylinder(20.0, 0.3, 64, 1);
    //glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, moonTex);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
        glRotatef(-90.0, 1, 0, 0);
        GLUquadric* qFloor = gluNewQuadric();
        gluQuadricTexture(qFloor, GL_TRUE);
        gluDisk(qFloor, 0.0, 20.0, 64, 8);
        gluDeleteQuadric(qFloor);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
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

    int numLights = 12;
    float radius = 2.2;
    for (int i = 0; i < numLights; i++) {
        float angle = (2.0 * M_PI * i) / numLights;
        float lx = radius * cos(angle);
        float lz = radius * sin(angle);
        glPushMatrix();
        glTranslatef(lx, 0.08, lz);
        glutSolidSphere(0.15, 12, 6);
        glPopMatrix();
    }

    // seats
    glColor3f(0.631, 0.451, 1);

    // left seat base
    glPushMatrix();
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
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

    int numLights = 12;
    float radius = 2.2;
    for (int i = 0; i < numLights; i++) {
        float angle = (2.0 * M_PI * i) / numLights;
        float lx = radius * cos(angle);
        float lz = radius * sin(angle);
        glPushMatrix();
        glTranslatef(lx, 0.08, lz);
        glutSolidSphere(0.15, 12, 6);
        glPopMatrix();
    }

    // seats
    glColor3f(0.333, 0.871, 0.553);

    // left seat base
    glPushMatrix();
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
        glTranslatef(1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawRideStructure(float swingAngle) { // THE POLES!
    float swingDegrees = swingAngle * 180.0 / M_PI;

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
            glTranslatef(-6.0, 7.0, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, 8.0, 8, 1);
        glPopMatrix();
        // left ship
        glPushMatrix();
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(-4.0, 3.0, 0.0);
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship1();
        glPopMatrix();
    glPopMatrix();

    // right cable and ship
    glPushMatrix();
    glTranslatef(6.0, 15.0, 0.0);
        glRotatef(-swingDegrees, 1, 0, 0);
        glTranslatef(-6.0, -15.0, 0.0);

        // right cable
        glPushMatrix();
            glColor3f(0.4, 0.4, 0.45);
            glTranslatef(6.0, 7.0, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, 8.0, 8, 1);
        glPopMatrix();
        // right ship
        glPushMatrix();
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(4.0, 3.0, 0.0);
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship2();
        glPopMatrix();
    glPopMatrix();
}

void drawAlien(float armAngle, float antennaAngle, float r, float g, float b) {
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

    // left antenna ball
    //glPushMatrix();
    //    glColor3f(0.6, 0.9, 1.0);
    //    glTranslatef(-0.7, 2.72, 0.0);
    //    glutSolidSphere(0.1, 12, 8);
    //glPopMatrix();

    // right antenna
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.4, 2.2, 0.0);
        glRotatef(antennaAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.04, 0.6, 8, 1);
    glPopMatrix();

    // right antenna ball
    //glPushMatrix();
    //    glColor3f(0.6, 0.9, 1.0);
    //    glTranslatef(0.7, 2.72, 0.0);
    //    glRotatef(antennaAngle, 0, 0, 1);
    //    glutSolidSphere(0.1, 12, 8);
    //glPopMatrix();

    // left arm
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.25, 0.8, 0.0);
        //glRotatef(armAngle, 0, 0, 1);
        glRotatef(60.0 + armAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // right arm
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.25, 0.8, 0.0);
        //glRotatef(-armAngle, 0, 0, 1);
        glRotatef(-60.0 - armAngle, 0, 0, 1);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // left leg
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(-0.18, 0.35, 0.0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();

    // right leg
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(0.18, 0.35, 0.0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();
}

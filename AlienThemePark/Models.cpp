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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(0.8, 0.8, 0.8);

    GLUquadric* qPlanet = gluNewQuadric();
    gluQuadricTexture(qPlanet, GL_TRUE);
    gluQuadricNormals(qPlanet, GLU_SMOOTH);
    gluQuadricDrawStyle(qPlanet, GLU_FILL);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(12.0, 12.0, 1.0);  // tiles the texture 4x4 times - increase for more detail
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0.0, -0.01, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    gluDisk(qPlanet, 0.0, 70.0, 64, 8);
    glTranslatef(0.0, 0.0, -5.0);
    gluCylinder(qPlanet, 70.0, 70.0, 5.0, 64, 4);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

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
        glColor3f(0.416, 0.251, 0.439);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top
    glPushMatrix();
        glColor3f(0.655, 0.4, 0.69);
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScalef(0.8f, 0.7f, 0.8f);
        glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle
    glPushMatrix();
        glColor3f(0.961, 0.714, 0.467);
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
    glColor3f(0.961, 0.714, 0.467);

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
        glColor3f(0.655, 0.4, 0.69);
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glColor3f(0.655, 0.4, 0.69);
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glColor3f(0.655, 0.4, 0.69);
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
        glColor3f(0.655, 0.4, 0.69);
        glTranslatef(1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

}

void drawSpaceship2() { // THE GREEN ONE
    // main saucer body
    glPushMatrix();
        glColor3f(0.404, 0.451, 0.294);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top
    glPushMatrix();
        glColor3f(0.557, 0.62, 0.412);
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScalef(0.8f, 0.7f, 0.8f);
        glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle
    glPushMatrix();
        glColor3f(0.961, 0.714, 0.467);
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
    glColor3f(0.961, 0.714, 0.467);

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
        glColor3f(0.557, 0.62, 0.412);
        glTranslatef(-1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // left seat back
    glPushMatrix();
        glColor3f(0.557, 0.62, 0.412);
        glTranslatef(-1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat base
    glPushMatrix();
        glColor3f(0.557, 0.62, 0.412);
        glTranslatef(1.85, 0.15, 0.0);
        glScalef(0.8, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // right seat back
    glPushMatrix();
        glColor3f(0.557, 0.62, 0.412);
        glTranslatef(1.5, 0.6, 0.0);
        glRotatef(90.0, 0., 0., 1.);
        glScalef(1.0, 0.3, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawRideStructure(float swingAngle, float rideHeight, int pinkState, int blueState, float armAngle, float antennaAngle, float legAngle, GLuint metalTex) { // THE POLES!
    float swingDegrees = swingAngle * 180.0 / M_PI;
    float shipY = rideHeight + 1.0f;
    float cableLength = 14.0f - rideHeight;

    // pole in middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, metalTex);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glRotatef(-90.0, 1, 0, 0);
        GLUquadric* qPole = gluNewQuadric();
        gluQuadricTexture(qPole, GL_TRUE);
        gluQuadricNormals(qPole, GLU_SMOOTH);
        gluCylinder(qPole, 0.4, 0.4, 15.0, 16, 1);
        gluDeleteQuadric(qPole);
    glPopMatrix();

    // top bar (horizontal)
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-8.0, 15.0, 0.0);
        glRotatef(90.0, 0, 1, 0);
        GLUquadric* qBar = gluNewQuadric();
        gluQuadricTexture(qBar, GL_TRUE);
        gluQuadricNormals(qBar, GLU_SMOOTH);
        gluCylinder(qBar, 0.3, 0.3, 16.0, 16, 1);
        gluDeleteQuadric(qBar);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left cable and ship
    glPushMatrix();
        glTranslatef(-6.0, 15.0, 0.0);
        glRotatef(swingDegrees, 1, 0, 0);
        glTranslatef(6.0, -15.0, 0.0);

        // left cable
        glPushMatrix();
            glColor3f(0.353, 0.357, 0.333);
            glTranslatef(-6.0, shipY, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, cableLength, 8, 1);
        glPopMatrix();
        // left ship
        glPushMatrix();
            glTranslatef(-6.0, shipY, 0.0);
            glScalef(1.5, 1.5, 1.5);
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
            glColor3f(0.353, 0.357, 0.333);
            glTranslatef(6.0, shipY, 0.0);
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, cableLength, 8, 1);
        glPopMatrix();
        // right ship
        glPushMatrix();
            glTranslatef(6.0, shipY, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship2();
        glPopMatrix();
    glPopMatrix();

    // green alien standing near the ride
    glPushMatrix();
    glTranslatef(15.0f, -0.35f, 4.0f);
    drawAlien(armAngle, antennaAngle, legAngle, 0.396f, 1.0f, 0.557f);
    glPopMatrix();

    // yellow alien standing near the ride
    glPushMatrix();
    glTranslatef(-17.0f, -0.35f, -3.0f);
    drawAlien(armAngle, antennaAngle, legAngle, 1.0f, 0.804f, 0.396f);
    glPopMatrix();

    // red alien standing near the ride
    glPushMatrix();
    glTranslatef(11.0f, -0.35f, -2.0f);
    drawAlien(armAngle, antennaAngle, legAngle, 1.0f, 0.396f, 0.396f);
    glPopMatrix();

    // purple alien standing near the ride
    glPushMatrix();
    glTranslatef(-11.0f, -0.35f, 6.0f);
    drawAlien(armAngle, antennaAngle, legAngle, 0.733f, 0.396f, 1.0f);
    glPopMatrix();

    // rocks scattered around
    glPushMatrix();
    glTranslatef(8.0, 0.0, -8.0);
    drawRock(1.2, 0.329, 0.286, 0.227);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.0, 0.0, -5.0);
    drawRock(0.8, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.0, 0.0, 8.0);
    drawRock(1.5, 0.286, 0.314, 0.129);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.0, 0.0, 10.0);
    drawRock(0.6, 0.494, 0.424, 0.353);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0, 0.0, -12.0);
    drawRock(1.0, 0.329, 0.286, 0.227);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0, 0.0, 12.0);
    drawRock(0.8, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22.0, 0.0, 20.0);
    drawRock(1.5, 0.286, 0.314, 0.129);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28.0, 0.0, 10.0);
    drawRock(0.6, 0.494, 0.424, 0.353);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 25.0);
    drawRock(0.6, 0.494, 0.424, 0.353);
    glPopMatrix();

    // alien plants scattered around
    glPushMatrix();
    glTranslatef(10.0, 0.0, 5.0);
    drawAlienPlant(2.0, 0.329, 0.286, 0.227, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.0, 0.0, 8.0);
    drawAlienPlant(1.5, 0.329, 0.286, 0.227, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 0.0, -10.0);
    drawAlienPlant(2.5, 0.494, 0.424, 0.353, 0.286, 0.314, 0.129);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0, 0.0, -12.0);
    drawAlienPlant(1.8, 0.494, 0.424, 0.353, 0.286, 0.314, 0.129);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0, 0.0, 15.0);
    drawAlienPlant(6.0, 0.329, 0.286, 0.227, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22.0, 0.0, 25.0);
    drawAlienPlant(7.0, 0.329, 0.286, 0.227, 0.227, 0.267, 0.106);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.0, 0.0, -25.0);
    drawAlienPlant(4.0, 0.494, 0.424, 0.353, 0.286, 0.314, 0.129);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0, 0.0, -14.0);
    drawAlienPlant(3.0, 0.494, 0.424, 0.353, 0.286, 0.314, 0.129);
    glPopMatrix();
}

void drawRock(float size, float r, float g, float b) {
    glPushMatrix();
        glColor3f(r, g, b);
        glScalef(size, size * 0.6, size * 0.8);
        glutSolidSphere(1.0, 12, 8);
    glPopMatrix();
}

void drawAlienPlant(float height, float stemR, float stemG, float stemB,
    float leafR, float leafG, float leafB) {
    // stem
    glPushMatrix();
    glColor3f(stemR, stemG, stemB);
    glRotatef(-90.0, 1, 0, 0);
    GLUquadric* qStem = gluNewQuadric();
    gluCylinder(qStem, 0.1, 0.08, height, 8, 1);
    gluDeleteQuadric(qStem);
    glPopMatrix();

    // leaf on top
    glPushMatrix();
    glColor3f(leafR, leafG, leafB);
    glTranslatef(0.0, height, 0.0);
    glScalef(1.0, 0.8, 1.0);
    glutSolidSphere(0.4, 12, 8);
    glPopMatrix();

    // two side leaves
    glPushMatrix();
    glColor3f(leafR, leafG, leafB);
    glTranslatef(0.3, height * 0.7, 0.0);
    glutSolidSphere(0.25, 10, 6);
    glPopMatrix();

    glPushMatrix();
    glColor3f(leafR, leafG, leafB);
    glTranslatef(-0.3, height * 0.65, 0.0);
    glutSolidSphere(0.25, 10, 6);
    glPopMatrix();
}
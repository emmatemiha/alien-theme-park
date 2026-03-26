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

void drawFloor() {
    glColor3f(0.6, 0.6, 0.65);  // grey moon surface colour for now
    glPushMatrix();
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(20.0, 0.3, 64, 1);
    glPopMatrix();
}

void drawSpaceship1() {
    // main saucer body (dark purple)
    glPushMatrix();
        glColor3f(0.427, 0.227, 0.839);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top (lighter purple)
    glPushMatrix();
        glColor3f(0.631, 0.451, 1);
        glTranslatef(0.0f, 0.4f, 0.0f);  // sit on top of saucer
        glScalef(0.8f, 0.7f, 0.8f);
        glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle (yellow)
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, -0.18, 0.0);
        glScalef(2.4, 0.8, 2.4);
        glutSolidSphere(0.6, 32, 16);
    glPopMatrix();

    // top antenna pole (grey)
    glPushMatrix();
        glColor3f(0.7, 0.7, 0.75);
        glTranslatef(0.0, 1.2, 0.0);
        glRotatef(-90.0, 1, 0, 0);
        glutSolidCylinder(0.03, 0.5, 12, 1);
    glPopMatrix();

    // ball on antenna (yellow)
    glPushMatrix();
        glColor3f(1.0, 0.6, 0.1);
        glTranslatef(0.0, 1.7, 0.0);
        glutSolidSphere(0.08, 12, 6);
    glPopMatrix();

    // 3 circle lights underneath (light blue) -- LEAVING OUT FOR NOW
    //glColor3f(0.4, 0.9, 1.0);

    //glPushMatrix();
    //    glTranslatef(-0.6, -0.6, 0.0);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    //glPushMatrix();
    //    glTranslatef(0.6, -0.6, 0.0);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    //glPushMatrix();
    //    glTranslatef(0.0, -0.6, 0.6);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    // circles around rim (yellow)
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

    // seats (light purple)
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

void drawSpaceship2() {
    // main saucer body (dark green)
    glPushMatrix();
    glColor3f(0.235, 0.58, 0.376);
    glScalef(3.0, 0.5, 3.0);
    glutSolidSphere(0.8f, 32, 16);
    glPopMatrix();

    // circle part on top (lighter green)
    glPushMatrix();
    glColor3f(0.333, 0.871, 0.553);
    glTranslatef(0.0f, 0.4f, 0.0f);  // sit on top of saucer
    glScalef(0.8f, 0.7f, 0.8f);
    glutSolidSphere(1.4, 24, 12);
    glPopMatrix();

    // bottom circle (yellow)
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.1);
    glTranslatef(0.0, -0.18, 0.0);
    glScalef(2.4, 0.8, 2.4);
    glutSolidSphere(0.6, 32, 16);
    glPopMatrix();

    // top antenna pole (grey)
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.75);
    glTranslatef(0.0, 1.2, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.03, 0.5, 12, 1);
    glPopMatrix();

    // ball on antenna (yellow)
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.1);
    glTranslatef(0.0, 1.7, 0.0);
    glutSolidSphere(0.08, 12, 6);
    glPopMatrix();

    // 3 circle lights underneath (light blue) -- LEAVING OUT FOR NOW
    //glColor3f(0.4, 0.9, 1.0);

    //glPushMatrix();
    //    glTranslatef(-0.6, -0.6, 0.0);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    //glPushMatrix();
    //    glTranslatef(0.6, -0.6, 0.0);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    //glPushMatrix();
    //    glTranslatef(0.0, -0.6, 0.6);
    //    glutSolidSphere(0.12, 16, 8);
    //glPopMatrix();

    // circles around rim (yellow)
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

    // seats (light green)
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

void drawRideStructure(float swingAngle) {
    float swingDegrees = swingAngle * 180.0 / M_PI;

    // --- CENTRAL POLE ---
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.55);
    glRotatef(-90.0, 1, 0, 0);  // point upward
    glutSolidCylinder(0.4, 15.0, 16, 1);
    glPopMatrix();

    // --- CROSSBAR (horizontal T across the top) ---
    glPushMatrix();
    glColor3f(0.45, 0.45, 0.5);
    glTranslatef(-8.0, 15.0, 0.0);  // start left of pole top
    glRotatef(90.0, 0, 1, 0);       // rotate to lie horizontal
    glutSolidCylinder(0.3, 16.0, 16, 1);  // 16 units total width
    glPopMatrix();

    // LEFT CABLE AND SHIP
    glPushMatrix();
        glTranslatef(-6.0, 15.0, 0.0);
        glRotatef(swingDegrees, 1, 0, 0);
        glTranslatef(6.0, -15.0, 0.0);

        // --- LEFT CABLE ---
        glPushMatrix();
            glColor3f(0.4, 0.4, 0.45);
            glTranslatef(-6.0, 7.0, 0.0);   // hang from left end of crossbar
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, 8.0, 8, 1);
        glPopMatrix();
        // --- LEFT SHIP ---
        glPushMatrix();
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(-4.0, 3.0, 0.0);   // position at bottom of left cable
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship1();
        glPopMatrix();
    glPopMatrix();

    // RIGHT CABLE AND SHIP
    glPushMatrix();
    glTranslatef(6.0, 15.0, 0.0);
        glRotatef(-swingDegrees, 1, 0, 0);
        glTranslatef(-6.0, -15.0, 0.0);

        // --- RIGHT CABLE ---
        glPushMatrix();
            glColor3f(0.4, 0.4, 0.45);
            glTranslatef(6.0, 7.0, 0.0);    // hang from right end of crossbar
            glRotatef(-90.0, 1, 0, 0);
            glutSolidCylinder(0.1, 8.0, 8, 1);
        glPopMatrix();
        // --- RIGHT SHIP ---
        glPushMatrix();
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(4.0, 3.0, 0.0);    // position at bottom of right cable
            glRotatef(90.0, 0, 1, 0);
            drawSpaceship2();
        glPopMatrix();
    glPopMatrix();
}

void drawAlien() {
    // --- BODY ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);  // pink
    glTranslatef(0.0, 0.8, 0.0);
    glScalef(0.6, 0.8, 0.6);
    glutSolidSphere(0.5, 16, 12);
    glPopMatrix();

    // --- HEAD (bigger than body) ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);  // same pink
    glTranslatef(0.0, 1.7, 0.0);
    glutSolidSphere(0.7, 24, 16);
    glPopMatrix();

    // --- LEFT EYE (light) ---
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);  // near black
    glTranslatef(-0.28, 1.75, 0.55);
    glutSolidSphere(0.22, 16, 12);
    glPopMatrix();

    // --- LEFT EYE PUPIL ---
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.15);
    glTranslatef(-0.22, 1.83, 0.72);
    glutSolidSphere(0.1, 8, 6);
    glPopMatrix();

    // --- RIGHT EYE (light) ---
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.28, 1.75, 0.55);
    glutSolidSphere(0.22, 16, 12);
    glPopMatrix();

    // --- RIGHT EYE PUPIL ---
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.15);
    glTranslatef(0.34, 1.83, 0.72);
    glutSolidSphere(0.1, 8, 6);
    glPopMatrix();

    // --- LEFT ANTENNA BASE ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(0.4, 2.2, 0.0);
    glRotatef(-30.0, 0, 0, 1);  // angle outward
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.04, 0.6, 8, 1);
    glPopMatrix();

    // --- LEFT ANTENNA BALL ---
    glPushMatrix();
    glColor3f(0.6, 0.9, 1.0);
    glTranslatef(-0.7, 2.72, 0.0);
    glutSolidSphere(0.1, 12, 8);
    glPopMatrix();

    // --- RIGHT ANTENNA BASE ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(-0.4, 2.2, 0.0);
    glRotatef(30.0, 0, 0, 1);  // angle outward other way
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.04, 0.6, 8, 1);
    glPopMatrix();

    // --- RIGHT ANTENNA BALL ---
    glPushMatrix();
    glColor3f(0.6, 0.9, 1.0);  // light blue ball like the image
    glTranslatef(0.7, 2.72, 0.0);
    glutSolidSphere(0.1, 12, 8);
    glPopMatrix();

    // --- LEFT ARM ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(-0.25, 0.8, 0.0);
    glRotatef(40.0, 0, 0, 1);   // angle upward like waving
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // --- RIGHT ARM ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(0.25, 0.8, 0.0);
    glRotatef(-40.0, 0, 0, 1);  // angle other way
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.07, 0.45, 8, 1);
    glPopMatrix();

    // --- LEFT LEG ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(-0.18, 0.35, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();

    // --- RIGHT LEG ---
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.75);
    glTranslatef(0.18, 0.35, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidCylinder(0.1, 0.3, 8, 1);
    glPopMatrix();
}
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
bool wireframeOn = false;

// for the ride to swing
float swingAngle = 1.0f;
float swingSpeed = 0.0f;
const float gravity = 9.8f;
const float armLength = 8.0f;

GLuint txId[3];
GLUquadric* q;

// for the aliens to move (arms, antennas and legs)
float alienArmAngle = 0.0f;
float alienAntennaAngle = 0.0f;
float alienFrame = 0.0f;
float alienLegAngle = 0.0f;

float spotlightAngle = 0.0f;
float spotlightColourPhase = 0.0f;

// for the pink alien to move around
// states: 0 = walking to seat, 1 = sitting on ground waiting,
//         2 = going up on ride,  3 = riding,
//         4 = coming back down,  5 = walking away
float pinkAlien_x = -8.0f;
float pinkAlien_y = -0.35f;
float pinkAlien_z = 8.0f;
int   pinkAlien_state = 0;
float pinkAlien_rideTimer = 0.0f;

// for the blue alien to move around
// states: 0 = walking to seat, 1 = sitting on ground waiting,
//         2 = going up on ride,  3 = riding,
//         4 = coming back down,  5 = walking away
float blueAlien_x = 8.0f;
float blueAlien_y = -0.35f;
float blueAlien_z = 10.0f;
int   blueAlien_state = 0;
float blueAlien_rideTimer = 0.0f;

// to lower and raise the ride so the aliens can get on it
float rideHeight = 0.0f;
bool rideLiftingUp = false;
bool rideComingDown = false;

// other 4 aliens walking around
float greenAlien_x = 15.0f;
float greenAlien_z = 4.0f;
bool  greenAlien_goingToTarget = true;
float greenAlien_angle = 0.0f;

float yellowAlien_x = -17.0f;
float yellowAlien_z = -3.0f;
bool  yellowAlien_goingToTarget = true;
float yellowAlien_angle = 0.0f;

float redAlien_x = 11.0f;
float redAlien_z = -2.0f;
bool  redAlien_goingToTarget = true;
float redAlien_angle = 0.0f;

float purpleAlien_x = -11.0f;
float purpleAlien_z = 6.0f;
bool  purpleAlien_goingToTarget = true;
float purpleAlien_angle = 0.0f;


void loadTexture() {
    glGenTextures(3, txId);
    
    //sky
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadBMP("textures/brightsky.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //moon
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    loadBMP("textures/moss.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //poles
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadBMP("textures/iron.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initialise(void) {
    loadTexture();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0, 0.075, 0.412, 1.0);

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
    if (key == 'q') {
        wireframeOn = !wireframeOn;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

bool moveToward(float& x, float& z, float& angle,
    float targetX, float targetZ, float speed) {

    float dx = targetX - x;
    float dz = targetZ - z;
    float dist = sqrt(dx * dx + dz * dz);

    if (dist < 0.3f) return true;

    float newX = x + (dx / dist) * speed;
    float newZ = z + (dz / dist) * speed;

    // 🚫 STOP them entering ride area (circle radius 10)
    float newRadius = sqrt(newX * newX + newZ * newZ);
    if (newRadius < 10.0f) {
        return false; // just cancel movement
    }

    x = newX;
    z = newZ;

    angle = atan2(dx, dz) * 180.0f / (float)M_PI;

    return false;
}

void timer(int value) {

    // for aliens to move
    alienFrame += 0.05f;
    alienArmAngle = 18.0f * sin(alienFrame);
    alienAntennaAngle = -25.0f * sin(alienFrame);
    alienLegAngle = 20.0f * sin(alienFrame);

    spotlightAngle += 1.0f;
    if (spotlightAngle > 360.0f) {
        spotlightAngle -= 360.0f;
    }
    spotlightColourPhase += 0.05f;

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

    // ---- 4 wandering aliens walk back and forth ----
    if (greenAlien_goingToTarget) {
        if (moveToward(greenAlien_x, greenAlien_z, greenAlien_angle, -20.0f, -15.0f, 0.04f))
            greenAlien_goingToTarget = false;
    }
    else {
        if (moveToward(greenAlien_x, greenAlien_z, greenAlien_angle, 20.0f, 10.0f, 0.04f))
            greenAlien_goingToTarget = true;
    }

    if (yellowAlien_goingToTarget) {
        if (moveToward(yellowAlien_x, yellowAlien_z, yellowAlien_angle, 25.0f, 15.0f, 0.035f))
            yellowAlien_goingToTarget = false;
    }
    else {
        if (moveToward(yellowAlien_x, yellowAlien_z, yellowAlien_angle, - 25.0f, -10.0f, 0.035f))
            yellowAlien_goingToTarget = true;
    }

    if (redAlien_goingToTarget) {
        if (moveToward(redAlien_x, redAlien_z, redAlien_angle, -20.0f, 20.0f, 0.045f))
            redAlien_goingToTarget = false;
    }
    else {
        if (moveToward(redAlien_x, redAlien_z, redAlien_angle, 20.0f, -15.0f, 0.045f))
            redAlien_goingToTarget = true;
    }

    if (purpleAlien_goingToTarget) {
        if (moveToward(purpleAlien_x, purpleAlien_z, purpleAlien_angle, 15.0f, -20.0f, 0.038f))
            purpleAlien_goingToTarget = false;
    }
    else {
        if (moveToward(purpleAlien_x, purpleAlien_z, purpleAlien_angle, -15.0f, 15.0f, 0.038f))
            purpleAlien_goingToTarget = true;
    }

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
    else if (pinkAlien_state == 2) { 
        pinkAlien_y = rideHeight + 0.8f;
    }
    else if (pinkAlien_state == 3) {
        pinkAlien_rideTimer += 0.016f;
        if (pinkAlien_rideTimer > 8.0f && rideHeight >= 8.0f) {
            pinkAlien_state = 4;
            pinkAlien_rideTimer = 0.0f;
            rideComingDown = true;
        }
    }
    else if (pinkAlien_state == 4) {
        pinkAlien_y = rideHeight + 0.8f;
        if (rideHeight <= 0.0f && fabs(swingAngle) < 0.1f) {
            pinkAlien_state = 5;
            pinkAlien_x = leftSeatX;
            pinkAlien_y = -0.35f;
            pinkAlien_z = leftSeatZ;
        }
    }
    else if (pinkAlien_state == 5) {
        float distanceX = -8.0f - pinkAlien_x;
        //float distanceZ = 8.0f - pinkAlien_z;
        float distanceZ = 15.0f - pinkAlien_z;
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
    else if (blueAlien_state == 2) { 
        blueAlien_y = rideHeight + 0.8f;
    }
    else if (blueAlien_state == 3) {
        blueAlien_rideTimer += 0.016f;
        if (blueAlien_rideTimer > 8.0f && rideHeight >= 8.0f) {
            blueAlien_state = 4;
            blueAlien_rideTimer = 0.0f;
            rideComingDown = true;
        }
    }
    else if (blueAlien_state == 4) {
        blueAlien_y = rideHeight + 0.8f;
        if (rideHeight <= 0.0f && fabs(swingAngle) < 0.1f) {
            blueAlien_state = 5;
            blueAlien_x = rightSeatX;
            blueAlien_y = -0.35f;
            blueAlien_z = rightSeatZ + 2.0;
        }
    }
    else if (blueAlien_state == 5) {
        float distanceX = 8.0f - blueAlien_x;
        //float distanceZ = 10.0f - blueAlien_z;
        float distanceZ = -12.0f - blueAlien_z;
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
        pinkAlien_y = -0.35f;
        blueAlien_y = -0.35f;
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

void drawShadow() {
    float shadowMatrix[16] = {
        20, 0,  0,  0,
        -8, 0, -8, -1,
        0,  0,  20,  0,
        0,  0,  0,  20
    };

    // use fog to force everything to one flat grey colour
    float fogColour[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColour);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 0.001f);  // fog so thick everything is the fog colour

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glMultMatrixf(shadowMatrix);
    drawRideStructure(swingAngle, rideHeight, -1, -1, 0, 0, 0, 0,
        greenAlien_x, greenAlien_z, greenAlien_angle,
        yellowAlien_x, yellowAlien_z, yellowAlien_angle,
        redAlien_x, redAlien_z, redAlien_angle,
        purpleAlien_x, purpleAlien_z, purpleAlien_angle);
    if (pinkAlien_state != 2 && pinkAlien_state != 3 && pinkAlien_state != 4) {
        glPushMatrix();
        glTranslatef(pinkAlien_x, -0.35f, pinkAlien_z);
        drawAlien(0, 0, 0, 0.15f, 0.15f, 0.15f);
        glPopMatrix();
    }
    if (blueAlien_state != 2 && blueAlien_state != 3 && blueAlien_state != 4) {
        glPushMatrix();
        glTranslatef(blueAlien_x, -0.35f, blueAlien_z);
        drawAlien(0, 0, 0, 0.15f, 0.15f, 0.15f);
        glPopMatrix();
    }
    glPopMatrix();

    glDisable(GL_FOG);
    glEnable(GL_LIGHTING);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (wireframeOn) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_LIGHTING);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_LIGHTING);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-camX, camHeight, -camZ);
    glRotatef(camAngle, 0, 1, 0);

    // main light
    float lightPos[] = { 10, 20, 10, 1 };
    float white[] = { 1, 1, 1, 1 };
    float ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // spotlight
    // moving in a circle
    float spotX = 12.0f * cos(spotlightAngle * (float)M_PI / 180.0f);
    float spotZ = 12.0f * sin(spotlightAngle * (float)M_PI / 180.0f);
    float spotPos[] = { spotX, 15.0f, spotZ, 1.0f };
    float spotDir[] = { -spotX, -15.0f, -spotZ };

    // animated colour
    float r = 1.0f;
    float g = 0.2f + 0.2f * sin(spotlightColourPhase);
    float b = 0.6f + 0.4f * sin(spotlightColourPhase + 1.5f);
    float spotDiffuse[] = { r, g, b, 1.0f };
    float spotSpecular[] = { r, g, b, 1.0f };

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecular);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0f);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);

    // ================= VISIBLE LIGHT SOURCE =================

    // draw small glowing sphere so you can see it
    glDisable(GL_LIGHTING);
    glColor3f(0.671, 0.38, 0.482);
    glPushMatrix();
    glTranslatef(spotX, 15.0f, spotZ);
    glutSolidSphere(0.5, 16, 16);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // skybox
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glDepthMask(GL_FALSE);
    glPushMatrix();
        glRotatef(180.0, 0, 1, 0);
        //glRotatef(-150, 1, 0, 0);
        glRotatef(200, 0, 1, 0);
        glScalef(-1.0, 1.0, 1.0);
        gluSphere(q, 200.0, 64, 64);
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    drawFloor(txId[1]);
    drawShadow();
    drawRideStructure(swingAngle, rideHeight, pinkAlien_state, blueAlien_state, alienArmAngle, alienAntennaAngle, alienLegAngle, txId[2], greenAlien_x, greenAlien_z, greenAlien_angle, yellowAlien_x, yellowAlien_z, yellowAlien_angle, redAlien_x, redAlien_z, redAlien_angle, purpleAlien_x, purpleAlien_z, purpleAlien_angle);

    // pink alien
    glPushMatrix();

    if (pinkAlien_state == 2 || pinkAlien_state == 3 || pinkAlien_state == 4) {
        // ON RIDE → stick to seat
        glPushMatrix();
            glTranslatef(-6.0, 15.0, 0.0);
            glRotatef(swingAngle * 180.0 / M_PI, 1, 0, 0);
            glTranslatef(6.0, -15.0, 0.0);
            float shipY = rideHeight + 1.0f;
            glTranslatef(-6.0, shipY + 0.1f, -3.0);
            glRotatef(180.0, 0, 1, 0);
            drawAlien(alienArmAngle, alienAntennaAngle, 0.0f, 1.0f, 0.6f, 0.75f);
        glPopMatrix();
    }
    else {
        // NORMAL walking
        glTranslatef(pinkAlien_x, pinkAlien_y, pinkAlien_z);
        drawAlien(alienArmAngle, alienAntennaAngle, alienLegAngle, 1.0f, 0.6f, 0.75f);
    }

    glPopMatrix();

    // blue alien
    glPushMatrix();

    if (blueAlien_state == 2 || blueAlien_state == 3 || blueAlien_state == 4) {
        glPushMatrix();
            glTranslatef(6.0, 15.0, 0.0);
            glRotatef(-swingAngle * 180.0 / M_PI, 1, 0, 0);
            glTranslatef(-6.0, -15.0, 0.0);
            float shipY = rideHeight + 1.0f;
            glTranslatef(6.0, shipY + 0.1f, 3.0);
            drawAlien(alienArmAngle, alienAntennaAngle, 0.0f, 0.396f, 0.827f, 1.0f);
        glPopMatrix();
    }
    else {
        glTranslatef(blueAlien_x, blueAlien_y, blueAlien_z);
        drawAlien(alienArmAngle, alienAntennaAngle, alienLegAngle, 0.396f, 0.827f, 1.0f);
    }

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
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
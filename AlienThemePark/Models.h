//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  Models.h
//  Header file for a collection of models for an alien themepark
//  ========================================================================

void drawFloor(GLuint moonTex);
void drawRideStructure(float swingAngle, float rideHeight, int pinkState, int blueState, float armAngle, float antennaAngle, float legAngle, GLuint metalTex, float greenX, float greenZ, float greenAngle, float yellowX, float yellowZ, float yellowAngle, float redX, float redZ, float redAngle, float purpleX, float purpleZ, float purpleAngle);
void drawAlien(float armAngle, float antennaAngle, float legAngle, float r = 1.0f, float g = 0.6f, float b = 0.75f);
void drawRock(float size, float r, float g, float b);
void drawAlienPlant(float height, float stemR, float stemG, float stemB, float leafR, float leafG, float leafB);
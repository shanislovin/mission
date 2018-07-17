/*
COMP330 - 2018

Assignment 3 Template

Author: Peter Reeves

Date: 27 April 2018

Purpose: To help you get started with Assignment 3. Please see the Assignment 3 description (spec) document for a full
description of the requirements. We strongly recommend that you use this code template as a starting point for your work.
But it is not meant to constrain your efforts in any way, and you do not have to use it if you prefer not to do so.

Textures:
	- Stars:         http://forums.newtek.com/showthread.php?90366-Real-3D-Stars
	- Saturn Planet: https://www.solarsystemscope.com/textures/
	- Saturn Rings:  https://alpha-element.deviantart.com/art/Stock-Image-Saturn-Rings-393767006
	- Iapetus:       https://www.jpl.nasa.gov/spaceimages/details.php?id=PIA18436
	- Titan:         http://planet-texture-maps.wikia.com/wiki/Titan
	- Rhea:          http://libroesoterico.com/biblioteca/Astrologia/-%20SOFTWARE/Celestia%20Portable/App/Celestia/textures/hires/
	- Dione:         https://upload.wikimedia.org/wikipedia/commons/thumb/e/e4/Dione_PIA08413_moon_only.JPG/1024px-Dione_PIA08413_moon_only.JPG
	- Tethys:        https://www.jpl.nasa.gov/spaceimages/details.php?id=PIA14931
	- Enceladus:     http://www.unmannedspaceflight.com/lofiversion/index.php/t5575.html
	- Mimas:         https://saturn.jpl.nasa.gov/resources/7689/mimas-global-map-june-2017/
*/
/*
 * Student: Shanis Lovin
 * Student ID: 44857713
 * Date: 30th May 2018
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include "Soil.h"
#include "shapes.h"
#include "utilities.h"
#include "Math.h"
using namespace std;

const int WINDOW_INITIAL_WIDTH = 1024;
const int WINDOW_INITIAL_HEIGHT = 768;

const float HORIZONTAL_DIVISION = 0.3f;

const float FRAMES_PER_SECOND = 60.0f;
const int FRAME_MILLI_WAIT = (int) (1000.0f / FRAMES_PER_SECOND);

int windowWidth = WINDOW_INITIAL_WIDTH;
int windowHeight = WINDOW_INITIAL_HEIGHT;

// Stars
unsigned int starTexture = -1;
const float STAR_RADIUS = 30.0f;

// Saturn
unsigned int saturnTexture = -1;
const float SATURN_RADIUS = 1.0f;
unsigned int ringTexture = -1;

// Mimas
unsigned int mimasTexture = -1;
float mimasOrbitAngle = 0.0f;
const float MIMAS_RADIUS = 0.1f;
const float MIMAS_ORBIT_RADIUS = 4.0f;

// Enceladus
unsigned int enceladusTexture = -1;
float enceladusOrbitAngle = 0.0f;
const float ENCELADUS_RADIUS = 0.15f;
const float ENCELADUS_ORBIT_RADIUS = 5.0f;

// Tethys
unsigned int tethysTexture = -1;
float tethysOrbitAngle = 0.0f;
const float TETHYS_RADIUS = 0.15f;
const float TETHYS_ORBIT_RADIUS = 6.5f;

// Dione
unsigned int dioneTexture = -1;
float dioneOrbitAngle = 0.0f;
const float DIONE_RADIUS = 0.18f;
const float DIONE_ORBIT_RADIUS = 7.5f;

// Rhea
unsigned int rheaTexture = -1;
float rheaOrbitAngle = 0.0f;
const float RHEA_RADIUS = 0.2f;
const float RHEA_ORBIT_RADIUS = 8.5f;

// Titan
unsigned int titanTexture = -1;
float titanOrbitAngle = 0.0f;
const float TITAN_RADIUS = 0.28f;
const float TITAN_ORBIT_RADIUS = 9.5f;

// Iapetus
unsigned int iapetusTexture = -1;
float iapetusOrbitAngle = 0.0f;
const float IAPETUS_RADIUS = 0.2f;
const float IAPETUS_ORBIT_RADIUS = 10.5f;

// Probe
float probeOrbitAngle = 0.0f;
const float PROBE_RADIUS = 0.02f;
float PROBE_ORBIT_RADIUS = MIMAS_RADIUS + 0.2f;

int probeMoon;		// Var for which moon the probe is orbiting
int views;			// Var for cycling through the 4 viewports

float pointX;		// Var for the current X position of map's scan (left to right red rect)
float pointXMim;	// Current X pos for Mimas
float pointXEnc;	// Current X pos for Enceladus
float pointXTet;	// Current X pos for Tethys
float pointXDio;	// Current X pos for Dione
float pointXRhe;	// Current X pos for Rhea
float pointXTit;	// Current X pos for Titan
float pointXIap;	// Current X pos for Iapetus
unsigned int mapTexture = -1;	// Map texture variable for when probe switches moons

float centreX;		// Var for the current probed moon's x pos
float centreY;		// Var for the current probed moon's y pos
float centreZ;		// Var for the current probed moon's z pos

float speed;		// Var for the speed of map view's scanner
float rotation;		// Var for the speed of moon rotation on their axes

string moonStr;		// String var for probe view's text, cycles through probed moons
string scanLevel;	// String var for map's scan level (Scanning: "..." or "complete!")
string scanLevel2;	// String var for map's scan level (Scanning: "..." or "complete!")

int realisticSwitch = 1;	// Controls the object in focus in realistic view, as I thought both looked nice :)

void initialize () {
	// Saturn
	saturnTexture = loadGLTexture("textures/saturn.jpg");
	ringTexture = loadGLTexture("textures/saturn_rings_shadowed_premultiplied.png");

	starTexture = loadGLTexture("textures/stars.png");

	// Mimas
	mimasTexture = loadGLTexture("textures/mimas.jpg");

	// Enceladus
	enceladusTexture = loadGLTexture("textures/enceladus.jpg");

	// Tethys
	tethysTexture = loadGLTexture("textures/tethys.jpg");

	// Dione
	dioneTexture = loadGLTexture("textures/dione.jpg");

	// Rhea
	rheaTexture = loadGLTexture("textures/rhea.jpg");

	// Titan
	titanTexture = loadGLTexture("textures/titan.jpg");

	// Iapetus
	iapetusTexture = loadGLTexture("textures/iapetus.jpg");

	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_NORMALIZE);

	// Initialising all the variables/original state of Mission Control.
	// Initial moon is the closest one to Saturn (Mimas)
	mapTexture = mimasTexture;
	probeMoon = 1;
	views = 1;
	pointX = 0;
	pointXMim = 0;
	pointXEnc = 0;
	pointXTet = 0;
	pointXDio = 0;
	pointXRhe = 0;
	pointXTit = 0;
	pointXIap = 0;
	moonStr = "Mimas";
	scanLevel = "...";
	scanLevel2 = "...";
}

void setupRealisticView (Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float) viewportWidth / (float) viewportHeight, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (realisticSwitch == 1)
		// The edited parameters, focused on the currently probed moon.
		gluLookAt(centreX + 1, centreY + 0.5, centreZ - 1, centreX, centreY, centreZ, 0.0f, 1.0f, 0.0f);

	if (realisticSwitch == 2)
		// The initial given gluLookAt parameters (far distance, focused on Saturn
		gluLookAt(8.0f, 1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

}

void setupMapView (Rect windowCoordinates) {
	glDisable(GL_DEPTH_TEST);
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, windowWidth, windowHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection is set to 2D for the map scanning
	glMatrixMode(GL_PROJECTION); // Set the projection matrix
	glLoadIdentity();            // Initialise to identity matrix
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight); // Set to orthographic projection of window

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setupSpacecraftView (Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	// Background is set to green to give off a 'radar' effect
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float) viewportWidth / (float) viewportHeight, 0.01f, 100.0f);

	// gluLookAt is set in display as it depends on probePosition
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setupOrbitView (Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float worldWindowHalfWidth = 8.0f;
	const float aspectRatio = (float) viewportHeight / (float) viewportWidth;
	glOrtho(-worldWindowHalfWidth, worldWindowHalfWidth, -worldWindowHalfWidth * aspectRatio, worldWindowHalfWidth * aspectRatio, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setupProbeView (Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float) viewportWidth / (float) viewportHeight, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0f, 1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void setupControlsView (Rect windowCoordinates) {
	glDisable(GL_DEPTH_TEST);
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, windowWidth, windowHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	// Projection is set to 2D for the controls menu/legend
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void update (const float currentTime, const float deltaTime) {
	// Determines the speed of the moons rotating Saturn
	mimasOrbitAngle += 0.15f * deltaTime;
	enceladusOrbitAngle += 0.15f * deltaTime;
	tethysOrbitAngle += 0.13f * deltaTime;
	dioneOrbitAngle += 0.12f * deltaTime;
	rheaOrbitAngle += 0.125f * deltaTime;
	titanOrbitAngle += 0.11f * deltaTime;
	iapetusOrbitAngle += 0.1f * deltaTime;

	// Determines speed of probe rotating the moons
	probeOrbitAngle += 1.0f * deltaTime;

	// Changing the level of scan completion depending on current probed moon:
	// e.g. if probeMoon == Mimas, increase the X position (mimics scan level from left to right)
	if (probeMoon == 1) {
		pointXMim += speed;
	}
	if (probeMoon == 2) {
		pointXEnc += speed;
	}
	if (probeMoon == 3) {
		pointXTet += speed;
	}
	if (probeMoon == 4) {
		pointXDio += speed;
	}
	if (probeMoon == 5) {
		pointXRhe += speed;
	}
	if (probeMoon == 6) {
		pointXTit += speed;
	}
	if (probeMoon == 7) {
		pointXIap += speed;
	}

	// Once a moon has rotated its' axes by 360 degrees, reset
	// else add rotation + 1. Mimicks moon rotation on axes while orbiting
	if (rotation >= 360)
		rotation = 0;
	else
		rotation += 0.25;

	// If scan level has passed windowWidth, display str "complete!"
	// else display "..."
	if (pointX >= windowWidth/3)
		scanLevel = " complete!";
	else
		scanLevel = "...";

	// If current viewport is focused on map, only show complete when it reaches
	// the new window width
	if (pointX >= windowWidth and views == 2)
		scanLevel2 = " complete!";
	else
		scanLevel2 = "...";
}

void animateSceneTimer (int lastTime) {
	int time = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(FRAME_MILLI_WAIT, animateSceneTimer, time);
	const float deltaTime = ((float)(time - lastTime)) / 1000.0f;
	update(time, deltaTime);
	glutPostRedisplay();
}

void drawLegs(){
	// Draws the legs of the probe in probe viewport
	glScalef(0.2,3,0.2);
	glutWireCube(1);
}

void display () {
	const int dividerHeight = windowHeight * HORIZONTAL_DIVISION;
	const int firstThird = (float) windowWidth * (1.0f / 3.0f);
	const int secondThird = (float) windowWidth * (2.0f / 3.0f);

	Rect topViewport;
	topViewport.bottomLeftX = 0;
	topViewport.bottomLeftY = dividerHeight;
	topViewport.topRightX = windowWidth;
	topViewport.topRightY = windowHeight;

	Rect bottomLeftViewport;
	bottomLeftViewport.bottomLeftX = 0;
	bottomLeftViewport.bottomLeftY = 0;
	bottomLeftViewport.topRightX = firstThird;
	bottomLeftViewport.topRightY = dividerHeight;

	Rect bottomMiddleViewport;
	bottomMiddleViewport.bottomLeftX = firstThird;
	bottomMiddleViewport.bottomLeftY = 0;
	bottomMiddleViewport.topRightX = secondThird;
	bottomMiddleViewport.topRightY = dividerHeight;

	Rect bottomRightViewport;
	bottomRightViewport.bottomLeftX = secondThird;
	bottomRightViewport.bottomLeftY = 0;
	bottomRightViewport.topRightX = windowWidth;
	bottomRightViewport.topRightY = dividerHeight;

	Rect probeViewport;
	probeViewport.bottomLeftX = windowWidth/4 * 3;
	probeViewport.bottomLeftY = windowHeight/6 * 3;
	probeViewport.topRightX = windowWidth;
	probeViewport.topRightY = windowHeight/6 * 5;

	Rect controlsViewport;
	controlsViewport.bottomLeftX = 0;
	controlsViewport.bottomLeftY = windowHeight/2;
	controlsViewport.topRightX = windowWidth/2;
	controlsViewport.topRightY = windowHeight;

	// Vector repositioning of the moons
	const Vector3 mimasPosition = {
		MIMAS_ORBIT_RADIUS * cosf(mimasOrbitAngle),
		0.0f,
		MIMAS_ORBIT_RADIUS * sinf(mimasOrbitAngle),
	};

	const Vector3 enceladusPosition = {
		ENCELADUS_ORBIT_RADIUS * cosf(enceladusOrbitAngle),
		0.0f,
		ENCELADUS_ORBIT_RADIUS * sinf(enceladusOrbitAngle),
	};

	const Vector3 tethysPosition = {
		TETHYS_ORBIT_RADIUS * cosf(tethysOrbitAngle),
		0.0f,
		TETHYS_ORBIT_RADIUS * sinf(tethysOrbitAngle),
	};

	const Vector3 dionePosition = {
		DIONE_ORBIT_RADIUS * cosf(dioneOrbitAngle),
		0.0f,
		DIONE_ORBIT_RADIUS * sinf(dioneOrbitAngle),
	};

	const Vector3 rheaPosition = {
		RHEA_ORBIT_RADIUS * cosf(rheaOrbitAngle),
		0.0f,
		RHEA_ORBIT_RADIUS * sinf(rheaOrbitAngle),
	};

	const Vector3 titanPosition = {
		TITAN_ORBIT_RADIUS * cosf(titanOrbitAngle),
		0.0f,
		TITAN_ORBIT_RADIUS * sinf(titanOrbitAngle),
	};

	const Vector3 iapetusPosition = {
		IAPETUS_ORBIT_RADIUS * cosf(iapetusOrbitAngle),
		0.0f,
		IAPETUS_ORBIT_RADIUS * sinf(iapetusOrbitAngle),
	};

	const Vector3 probePosition = {
		PROBE_ORBIT_RADIUS * cosf(probeOrbitAngle),
		0.0f,
		PROBE_ORBIT_RADIUS * sinf(probeOrbitAngle),
	};

	// ********************************** REALISTIC VIEWPORT ********************************** //
	{
		// Statements that manage the cycling of the viewports, changes positiong depending on variables
		if (views == 1) {
			setupRealisticView(topViewport);
		}
		if (views == 2) {
			setupRealisticView(bottomLeftViewport);
		}
		if (views == 3) {
			setupRealisticView(bottomMiddleViewport);
		}
		if (views == 4) {
			setupRealisticView(bottomRightViewport);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		// Sunlight
		glEnable(GL_LIGHT0);
		const float sunPosition [4] = { 15.0f, 5.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
		const float sunAmbient [4] = { -0.2f, -0.2f, -0.2f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
		const float sunDiffuse [4] = { 1.0f, 1.0f, 0.9f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);

		// Disable lighting and change culling to back face for the stars
		glDisable(GL_LIGHTING);
		glCullFace(GL_FRONT);
		// Stars: uses a sphere textured with stars to create a skybox
		glPushMatrix();
			glColor3f(1,1,1);
			glScalef(STAR_RADIUS, STAR_RADIUS, STAR_RADIUS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, starTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();
		glCullFace(GL_BACK);
		glEnable(GL_LIGHTING);

		// Saturn
		glPushMatrix();
			glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
			glRotatef(rotation/3,0.0,1.0,0.0);		// Saturn rotation on axes (slow)
			glBindTexture(GL_TEXTURE_2D, saturnTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Mimas
		glPushMatrix();
			glTranslatef(mimasPosition.x, mimasPosition.y, mimasPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(MIMAS_RADIUS, MIMAS_RADIUS, MIMAS_RADIUS);
			glBindTexture(GL_TEXTURE_2D, mimasTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Enceladus
		glPushMatrix();
			glTranslatef(enceladusPosition.x, enceladusPosition.y, enceladusPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(ENCELADUS_RADIUS, ENCELADUS_RADIUS, ENCELADUS_RADIUS);
			glBindTexture(GL_TEXTURE_2D, enceladusTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Tethys
		glPushMatrix();
			glTranslatef(tethysPosition.x, tethysPosition.y, tethysPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(TETHYS_RADIUS, TETHYS_RADIUS, TETHYS_RADIUS);
			glBindTexture(GL_TEXTURE_2D, tethysTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Dione
		glPushMatrix();
			glTranslatef(dionePosition.x, dionePosition.y, dionePosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(DIONE_RADIUS, DIONE_RADIUS, DIONE_RADIUS);
			glBindTexture(GL_TEXTURE_2D, dioneTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Rhea
		glPushMatrix();
			glTranslatef(rheaPosition.x, rheaPosition.y, rheaPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(RHEA_RADIUS, RHEA_RADIUS, RHEA_RADIUS);
			glBindTexture(GL_TEXTURE_2D, rheaTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Titan
		glPushMatrix();
			glTranslatef(titanPosition.x, titanPosition.y, titanPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(TITAN_RADIUS, TITAN_RADIUS, TITAN_RADIUS);
			glBindTexture(GL_TEXTURE_2D, titanTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Iapetus
		glPushMatrix();
			glTranslatef(iapetusPosition.x, iapetusPosition.y, iapetusPosition.z);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glScalef(IAPETUS_RADIUS, IAPETUS_RADIUS, IAPETUS_RADIUS);
			glBindTexture(GL_TEXTURE_2D, iapetusTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Probe: changes position of probe depending on current probed moon variable
		// if the current probed moon is Mimas, change the translation to it's pos
		glPushMatrix();
		if (probeMoon == 1) {
			glTranslatef(mimasPosition.x, mimasPosition.y, mimasPosition.z);
		}
		if (probeMoon == 2) {
			glTranslatef(enceladusPosition.x, enceladusPosition.y, enceladusPosition.z);
		}
		if (probeMoon == 3) {
			glTranslatef(tethysPosition.x, tethysPosition.y, tethysPosition.z);
		}
		if (probeMoon == 4) {
			glTranslatef(dionePosition.x, dionePosition.y, dionePosition.z);
		}
		if (probeMoon == 5) {
			glTranslatef(rheaPosition.x, rheaPosition.y, rheaPosition.z);
		}
		if (probeMoon == 6) {
			glTranslatef(titanPosition.x, titanPosition.y, titanPosition.z);
		}
		if (probeMoon == 7) {
			glTranslatef(iapetusPosition.x, iapetusPosition.y, iapetusPosition.z);
		}

		// Disabled texture and lighting as to not effect color of probe
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		// Translate again for correct positioning/orbiting of probe
		glTranslatef(probePosition.x, probePosition.y, probePosition.z);
		glScalef(PROBE_RADIUS, PROBE_RADIUS, PROBE_RADIUS);
		glColor3f(0.87,0.38,0);
		drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glColor3f(1,1,1);
		// Saturn ring: used a flattened cube to create the rings of Saturn, disabled lighting
		// as to not effect the texture
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glScalef(SATURN_RADIUS * 5, SATURN_RADIUS * 0.0001, SATURN_RADIUS* 5);
			glBindTexture(GL_TEXTURE_2D, ringTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawCube();
			glEnable(GL_LIGHTING);
		glPopMatrix();

	}

	// ********************************** MAP VIEWPORT ********************************** //
	{
		// Disabled as to not effect the 2D projection
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		// Adjusted the window height and width properties to help manipulate the texture placement
		float thisWindHeight = windowHeight/3.3;
		float thisWindWidth = windowWidth/3;
		if (views == 2) {
			// Changes the variables if the map view is the main view. More fitting to the screen
			setupMapView(topViewport);
			thisWindHeight = windowHeight/1.4;
			thisWindWidth = windowWidth/1;
		} else {
			setupMapView(bottomLeftViewport);
			thisWindHeight = windowHeight/3.3;
			thisWindWidth = windowWidth/3;
		}

		// Speed of scan depends on the current screen's width
		speed = thisWindWidth * 0.002;

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();		// Maps the textures to a quad
			glBindTexture(GL_TEXTURE_2D, mapTexture);	// Texture used depends on variable
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
			glTexCoord2f(0, 1); glVertex3f(0, thisWindHeight, 0);
			glTexCoord2f(1, 1); glVertex3f(thisWindWidth, thisWindHeight, 0);
			glTexCoord2f(1, 0); glVertex3f(thisWindWidth, 0, 0);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);	// As to not effect the scan level colour/grid

		glPushMatrix();		// This creates the grid layer over the map texture
			glColor3f(0.3,1,0.3);
			glLineWidth(1);
			glBegin(GL_LINES);
			for (float i = 0; i < thisWindWidth; i += thisWindWidth/10) {
				glVertex2f(i,0);
				glVertex2f(i,thisWindHeight);
			}
			for (float i = -3; i < thisWindHeight; i += thisWindHeight/10) {
				glVertex2f(0,i);
				glVertex2f(thisWindWidth,i);
			}
			glEnd();
		glPopMatrix();

		glPushMatrix();		// Draw rect, scan level depends on the current probed moon
			glTranslatef(0,0,0);
			if (probeMoon == 1) {
				pointX = pointXMim;
			}
			if (probeMoon == 2) {
				pointX = pointXEnc;
			}
			if (probeMoon == 3) {
				pointX = pointXTet;
			}
			if (probeMoon == 4) {
				pointX = pointXDio;
			}
			if (probeMoon == 5) {
				pointX = pointXRhe;
			}
			if (probeMoon == 6) {
				pointX = pointXTit;
			}
			if (probeMoon == 7) {
				pointX = pointXIap;
			}
			glColor3f(0.50,0,0);
			glRectf(pointX, 0,thisWindWidth,thisWindHeight);
		glPopMatrix();

		// Scanning level bar, blended for transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(0,0,0,0.8);
		glRectf(0, thisWindHeight * 0.89, thisWindWidth,thisWindHeight);

		glColor3f(0.87,0.38,0);
		glTranslatef(3,thisWindHeight * 0.92, 0);

		// Text for the scanning level ("..." or "complete!")
		if (views == 2)
			drawString("Scanning" + scanLevel2);
		else
			drawString("Scanning" + scanLevel);
	}

	// ********************************** SPACECRAFT VIEWPORT ********************************** //
	{
		// Statements that manage the cycling of the viewports, changes positiong depending on variables
		if (views == 3) {
			setupSpacecraftView(topViewport);
		} else
			setupSpacecraftView(bottomMiddleViewport);

		// Changes the current moon to focus on depending on probeMoon variable
		if (probeMoon == 1) {
			centreX = mimasPosition.x;
			centreY = mimasPosition.y;
			centreZ = mimasPosition.z;
		}
		if (probeMoon == 2) {
			centreX = enceladusPosition.x;
			centreY = enceladusPosition.y;
			centreZ = enceladusPosition.z;
		}
		if (probeMoon == 3) {
			centreX = tethysPosition.x;
			centreY = tethysPosition.y;
			centreZ = tethysPosition.z;
		}
		if (probeMoon == 4) {
			centreX = dionePosition.x;
			centreY = dionePosition.y;
			centreZ = dionePosition.z;
		}
		if (probeMoon == 5) {
			centreX = rheaPosition.x;
			centreY = rheaPosition.y;
			centreZ = rheaPosition.z;
		}
		if (probeMoon == 6) {
			centreX = titanPosition.x;
			centreY = titanPosition.y;
			centreZ = titanPosition.z;
		}
		if (probeMoon == 7) {
			centreX = iapetusPosition.x;
			centreY = iapetusPosition.y;
			centreZ = iapetusPosition.z;
		}

		// Sets the gluLookAt parameters depending on the variables above
		gluLookAt(probePosition.x + centreX, probePosition.y + centreY, probePosition.z + centreZ, centreX, centreY, centreZ, 0.0f, 1.0f, 0.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		// Sunlight
		glEnable(GL_LIGHT0);
		const float sunPosition [4] = { 15.0f, 5.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
		const float sunAmbient [4] = { -0.2f, -0.2f, -0.2f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
		const float sunDiffuse [4] = { 1.0f, 1.0f, 0.9f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);

		const float sunDiffuseTint [4] = { 0, 1,0, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuseTint);

		glLineWidth(-0.5);

		// Stars: the star skybox. Overlay colour is set to green for the 'radar' effect
		glCullFace(GL_FRONT);
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(0,1,0);
			glScalef(STAR_RADIUS, STAR_RADIUS, STAR_RADIUS);
			glBindTexture(GL_TEXTURE_2D, starTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();
		glCullFace(GL_BACK);
		glEnable(GL_LIGHTING);

		// Saturn
		glPushMatrix();
			glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
			glRotatef(rotation/3,0.0,1.0,0.0);		// Saturn rotation on axes (slow)
			glBindTexture(GL_TEXTURE_2D, saturnTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
		glPopMatrix();

		// Mimas
		glPushMatrix();
			glTranslatef(mimasPosition.x, mimasPosition.y, mimasPosition.z);
			glScalef(MIMAS_RADIUS, MIMAS_RADIUS, MIMAS_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, mimasTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 1) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(MIMAS_RADIUS + 0.93, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Enceladus
		glPushMatrix();
			glTranslatef(enceladusPosition.x, enceladusPosition.y, enceladusPosition.z);
			glScalef(ENCELADUS_RADIUS, ENCELADUS_RADIUS, ENCELADUS_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, enceladusTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 2) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(ENCELADUS_RADIUS + 0.876, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Tethys
		glPushMatrix();
			glTranslatef(tethysPosition.x, tethysPosition.y, tethysPosition.z);
			glScalef(TETHYS_RADIUS, TETHYS_RADIUS, TETHYS_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, tethysTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 3) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(TETHYS_RADIUS + 0.876, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Dione
		glPushMatrix();
			glTranslatef(dionePosition.x, dionePosition.y, dionePosition.z);
			glScalef(DIONE_RADIUS, DIONE_RADIUS, DIONE_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, dioneTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 4) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(DIONE_RADIUS + 0.846, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Rhea
		glPushMatrix();
			glTranslatef(rheaPosition.x, rheaPosition.y, rheaPosition.z);
			glScalef(RHEA_RADIUS, RHEA_RADIUS, RHEA_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, rheaTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 5) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(RHEA_RADIUS + 0.825, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Titan
		glPushMatrix();
			glTranslatef(titanPosition.x, titanPosition.y, titanPosition.z);
			glScalef(TITAN_RADIUS, TITAN_RADIUS, TITAN_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, titanTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 6) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(TITAN_RADIUS + 0.745, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Iapetus
		glPushMatrix();
			glTranslatef(iapetusPosition.x, iapetusPosition.y, iapetusPosition.z);
			glScalef(IAPETUS_RADIUS, IAPETUS_RADIUS, IAPETUS_RADIUS);
			glRotatef(rotation,0.0,1.0,0.0);		// Moon rotation on axes
			glBindTexture(GL_TEXTURE_2D, iapetusTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawSphere();
			if (probeMoon == 7) {	// If this is the current probed moon, add a lat/long overlay
				glDisable(GL_LIGHTING);		// Disable lighting/texture effects
				glDisable(GL_TEXTURE_2D);
				glColor3f(0,0.7,0);
				glRotatef(90,90,0,0);	// Rotates the grid to look like lat/long
				glutWireSphere(IAPETUS_RADIUS + 0.826, 14, 14);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
			}
		glPopMatrix();

		// Saturn ring
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glScalef(SATURN_RADIUS * 5, SATURN_RADIUS * 0.0001, SATURN_RADIUS* 5);
			// Placed slightly lower so the ring is more visible
			glTranslatef(0,-400,0);
			glBindTexture(GL_TEXTURE_2D, ringTexture);
			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			drawCube();
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	// ********************************** ORBIT VIEWPORT ********************************** //
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		// Statements that manage the cycling of the viewports, changes positioning depending on variables
		if (views == 4) {
			setupOrbitView(topViewport);
		} else
			setupOrbitView(bottomRightViewport);

		glPushMatrix();
			// Vertical flip mapping XZ plane to xy screen coordinates.
			glScalef(1.0f, -1.0f, 1.0f);
			glScalef(0.5,0.5,0.5);
			glColor3f(0.5f, 0.5f, 0.5f);
			glPushMatrix();
				if (probeMoon == 1) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(MIMAS_ORBIT_RADIUS, MIMAS_ORBIT_RADIUS, MIMAS_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(mimasPosition.x, mimasPosition.z, 0.0f);
				}
				if (probeMoon == 2) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(ENCELADUS_ORBIT_RADIUS, ENCELADUS_ORBIT_RADIUS, ENCELADUS_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(enceladusPosition.x, enceladusPosition.z, 0.0f);
				}
				if (probeMoon == 3) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(TETHYS_ORBIT_RADIUS, TETHYS_ORBIT_RADIUS, TETHYS_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(tethysPosition.x, tethysPosition.z, 0.0f);
				}
				if (probeMoon == 4) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(DIONE_ORBIT_RADIUS, DIONE_ORBIT_RADIUS, DIONE_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(dionePosition.x, dionePosition.z, 0.0f);
				}
				if (probeMoon == 5) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(RHEA_ORBIT_RADIUS, RHEA_ORBIT_RADIUS, RHEA_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(rheaPosition.x, rheaPosition.z, 0.0f);
				}
				if (probeMoon == 6) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(TITAN_ORBIT_RADIUS, TITAN_ORBIT_RADIUS, TITAN_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(titanPosition.x, titanPosition.z, 0.0f);
				}
				if (probeMoon == 7) {	// If this is the current probed moon, add orbit path + set translate
					glPushMatrix();
						glTranslatef(0,0,0);
						glScalef(IAPETUS_ORBIT_RADIUS, IAPETUS_ORBIT_RADIUS, IAPETUS_ORBIT_RADIUS);
						drawCircle();
					glPopMatrix();
					glTranslatef(iapetusPosition.x, iapetusPosition.z, 0.0f);
				}

				// Adds another translate for correct positioning, and draw the probe
				glTranslatef(probePosition.x, probePosition.z, 0.0f);
				glColor3f(0.87,0.38,0);
				glScalef(PROBE_RADIUS*8, PROBE_RADIUS*8, PROBE_RADIUS*8);
				drawCube();
			glPopMatrix();

			glColor3f(1.0f, 1.0f, 1.0f);
			// Draws the  planets (2D circles)
			// Saturn Planet
			glPushMatrix();
				glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
				drawCircle();
				drawString("Saturn");
			glPopMatrix();

			// Saturn rings
			glPushMatrix();
				glScalef(SATURN_RADIUS * 2, SATURN_RADIUS * 2, SATURN_RADIUS * 2);
				drawCircle();
			glPopMatrix();

			// Mimas
			glPushMatrix();
				glTranslatef(mimasPosition.x, mimasPosition.z, 0.0f);
				glScalef(MIMAS_RADIUS, MIMAS_RADIUS, MIMAS_RADIUS);
				drawCircle();
				drawString("Mimas");
			glPopMatrix();

			// Enceladus
			glPushMatrix();
				glTranslatef(enceladusPosition.x, enceladusPosition.z, 0.0f);
				glScalef(ENCELADUS_RADIUS, ENCELADUS_RADIUS, ENCELADUS_RADIUS);
				drawCircle();
				drawString("Enceladus");
			glPopMatrix();

			// Tethys
			glPushMatrix();
				glTranslatef(tethysPosition.x, tethysPosition.z, 0.0f);
				glScalef(TETHYS_RADIUS, TETHYS_RADIUS, TETHYS_RADIUS);
				drawCircle();
				drawString("Tethys");
			glPopMatrix();

			// Dione
			glPushMatrix();
				glTranslatef(dionePosition.x, dionePosition.z, 0.0f);
				glScalef(DIONE_RADIUS, DIONE_RADIUS, DIONE_RADIUS);
				drawCircle();
				drawString("Dione");
			glPopMatrix();

			// Rhea
			glPushMatrix();
				glTranslatef(rheaPosition.x, rheaPosition.z, 0.0f);
				glScalef(RHEA_RADIUS, RHEA_RADIUS, RHEA_RADIUS);
				drawCircle();
				drawString("Rhea");
			glPopMatrix();

			// Titan
			glPushMatrix();
				glTranslatef(titanPosition.x, titanPosition.z, 0.0f);
				glScalef(TITAN_RADIUS, TITAN_RADIUS, TITAN_RADIUS);
				drawCircle();
				drawString("Titan");
			glPopMatrix();

			// Iapetus
			glPushMatrix();
				glTranslatef(iapetusPosition.x, iapetusPosition.z, 0.0f);
				glScalef(IAPETUS_RADIUS, IAPETUS_RADIUS, IAPETUS_RADIUS);
				drawCircle();
				drawString("Iapetus");
			glPopMatrix();

		glPopMatrix();
	}

	// ********************************** PROBE VIEWPORT ********************************** //
	{
		// Creates the probe viewport
		glEnable(GL_DEPTH_TEST);
		setupProbeView(probeViewport);

		// Creates the probe
		glPushMatrix();
			glRotatef(rotation,rotation,rotation,0);

			glColor3f(0.87,0.38,0);
			glTranslatef(0,0,0);
			glutWireCube(1);	// Body

			glPushMatrix();
			glTranslatef(0, 1.8, 0);
			drawLegs();			// Legs
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.7, -0.75, 0);
			glRotatef(240, 0,0, 1);
			drawLegs();			// Legs
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-1.7, -0.75, 0);
			glRotatef(120, 0,0, 1);
			drawLegs();			// Legs
			glPopMatrix();
		glPopMatrix();

		// Text for Probe Condition and Current Orbit Target, uses the moonStr variable
		// for the current probed moon. It is not perfect, if i can get feedback on this
		// it would be much appreciated :)
		glTranslatef(probeViewport.bottomLeftX / - 38, probeViewport.topRightY / - 38, 0);
		drawString("Probe Condition: Intact");
		glTranslatef(0,2,0);
		drawString("Current Orbital Target: " + moonStr);

		// Creates the border for the viewport
		// I also had a lot of difficulty doing this, any feed back would be appreciated :)
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);	// Changes projection mode
		glPushMatrix ();
			glLoadIdentity ();
			glLineWidth(3);
			glBegin (GL_LINE_LOOP);
				glVertex3i (-1, -1, -1);
				glVertex3i (1, -1, -1);
				glVertex3i (1, 1, -1);
				glVertex3i (-1 , 1, -1);
			glEnd ();
		glPopMatrix ();
		glMatrixMode (GL_MODELVIEW);	// Back to normal

	}

	// ********************************** CONTROLS VIEWPORT ********************************** //
	{
		// Disabled as to not effect the 2D projection
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		// Keeps the text in one spot, unless in map view (to keep text from being obstructed)
		int initPosY = windowHeight - (windowHeight/1.9);
		int posY2 = windowHeight - (windowHeight/1.9);
		if (views == 2)
			posY2 = initPosY - 45;
		else posY2 = initPosY;

		setupControlsView(controlsViewport);

		// Changes colour depending on current main view (keep text discernible)
		if (views == 2)
			glColor3f(1,1,1);
		else
			glColor3f(0.87,0.38,0);

		// Creates text for controls menu/legend
		glTranslatef(15,posY2,0);
		drawString("Controls");
		glTranslatef(0, -17, 0);
		drawString("1: Mimas");
		glTranslatef(0, -17, 0);
		drawString("2: Enceladus");
		glTranslatef(0, -17, 0);
		drawString("3: Tethys");
		glTranslatef(0, -17, 0);
		drawString("4: Dione");
		glTranslatef(0, -17, 0);
		drawString("5: Rhea");
		glTranslatef(0, -17, 0);
		drawString("6: Titan");
		glTranslatef(0, -17, 0);
		drawString("7: Iapetus");

		glTranslatef(0, -25, 0);
		drawString("F1: Realistic");
		glTranslatef(0, -17, 0);
		drawString("F2: Map");
		glTranslatef(0, -17, 0);
		drawString("F3: Spacecraft");
		glTranslatef(0, -17, 0);
		drawString("F4: Orbit");
		glTranslatef(0, -17, 0);
		drawString("F5: Realistic: Saturn");
		glTranslatef(0, -17, 0);
		drawString("F6: Realistic: " + moonStr);
	}

	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case '1': {											// Sets up viewports for Mimas
			mapTexture = mimasTexture;
			probeMoon = 1;									// 1 = Mimas
			PROBE_ORBIT_RADIUS = MIMAS_RADIUS + 0.2;		// Sets orbit radius for Mimas
			pointX = pointXMim;								// Map scan level for Mimas ++
			moonStr = "Mimas";								// Probe viewport str = Mimas
		} break;

		case '2': {											// Sets up viewports for Enceladus
			mapTexture = enceladusTexture;
			probeMoon = 2;									// 1 = Enceladus
			PROBE_ORBIT_RADIUS = ENCELADUS_RADIUS + 0.2;	// Sets orbit radius for Encaladus
			pointX = pointXEnc;								// Map scan level for Encaladus ++
			moonStr = "Enceladus";							// Probe viewport str = Encaladus
		} break;

		case '3': {											// Sets up viewports for Enceladus
			mapTexture = tethysTexture;
			probeMoon = 3;									// 1 = Tethys
			PROBE_ORBIT_RADIUS = TETHYS_RADIUS + 0.2;		// Sets orbit radius for Tethys
			pointX = pointXTet;								// Map scan level for Tethys ++
			moonStr = "Tethys";								// Probe viewport str = Tethys
		} break;

		case '4': {											// Sets up viewports for Dione
			mapTexture = dioneTexture;
			probeMoon = 4;									// 1 = Dione
			PROBE_ORBIT_RADIUS = DIONE_RADIUS + 0.2;		// Sets orbit radius for Dione
			pointX = pointXDio;								// Map scan level for Dione ++
			moonStr = "Dione";								// Probe viewport str = Dione
		} break;

		case '5': {											// Sets up viewports for Rhea
			mapTexture = rheaTexture;
			probeMoon = 5;									// 1 = Rhea
			PROBE_ORBIT_RADIUS = RHEA_RADIUS + 0.2;			// Sets orbit radius for Rhea
			pointX = pointXRhe;								// Map scan level for Rhea ++
			moonStr = "Rhea";								// Probe viewport str = Rhea
		} break;

		case '6': {											// Sets up viewports for Titan
			mapTexture = titanTexture;
			probeMoon = 6;									// 1 = Titan
			PROBE_ORBIT_RADIUS = TITAN_RADIUS + 0.2;		// Sets orbit radius for Titan
			pointX = pointXTit;								// Map scan level for Titan ++
			moonStr = "Titan";								// Probe viewport str = Titan
		} break;

		case '7': {											// Sets up viewports for Iapetus
			mapTexture = iapetusTexture;
			probeMoon = 7;									// 1 = Iapetus
			PROBE_ORBIT_RADIUS = IAPETUS_RADIUS + 0.2;		// Sets orbit radius for Iapetus
			pointX = pointXIap;								// Map scan level for Iapetus ++
			moonStr = "Iapetus";							// Probe viewport str = Iapetus
		} break;

		case 27: {
			exit(0);
		} break;
	}
}

void special_input (int key, int x, int y) {
	switch (key)	{
		case GLUT_KEY_UP: {

		} break;

		case GLUT_KEY_F1: {			// Realistic as main view
			views = 1;
		} break;

		case GLUT_KEY_F2: {			// Map as main view
			views = 2;
			scanLevel2 = "...";		// Change scan level text
		} break;

		case GLUT_KEY_F3: {			// Spacecraft as main view
			views = 3;
		} break;

		case GLUT_KEY_F4: {			// Orbit as main view
			views = 4;
		} break;

		case GLUT_KEY_F5: {			// Switch realistic focus to Saturn
			realisticSwitch = 2;
		} break;

		case GLUT_KEY_F6: {			// Switch realistic focus to current probed moon
			realisticSwitch = 1;
		} break;
	}
}

void resize (int width, int height) {
	windowWidth = width;
	windowHeight = height;
}

int main (int argc, char** argv) {
	// GLUT setup
	glutInit(&argc, argv);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mission Control");
	glutDisplayFunc(display);
	glutSpecialFunc(special_input);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	initialize();
	animateSceneTimer(FRAME_MILLI_WAIT);
	glutMainLoop();
	return 0;
}

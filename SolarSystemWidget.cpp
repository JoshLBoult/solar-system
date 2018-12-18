#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <QTimer>
#include "SolarSystemWidget.h"

// Author = Josh Boult
// This is NOT a truthful representation of our solar system

// Hardcoded values for radius of orbit
double EARTH_DISTANCE = 4; // x direction
double MOON_DISTANCE = 1; // positive x, negative z
double NEPTUNE_DISTANCE = 1.5; // positive y, negative x * 4
double JUPITER_DISTANCE = 12; // positive x

// constructor
SolarSystemWidget::SolarSystemWidget(QWidget *parent)
	: QGLWidget(parent),
  back_image("./Textures/stars.jpeg"),
  sun_image("./Textures/2k_sun.jpg"),
  earth_image("./Textures/earth.ppm"),
  moon_image("./Textures/2k_moon.jpg"),
  jupiter_image("./Textures/2k_jupiter.jpg"),
  neptune_image("./Textures/2k_neptune.jpg")
	{ // constructor
    // Rotation about axis
    sunAngle = 0;
    axisAngles[0] = 0;
    axisAngles[1] = 0;
    axisAngles[2] = 0;

    // Rotation around central sphere/planets
    sphereAngles[0] = 0;
    sphere1Moon1Angle = 0;
    sphereAngles[1] = -30;
    satelliteAngle = 0;
    sphereAngles[2] = 0;

    // Scene angles (x,y,z)
    sceneAngle[0] = 0;
    sceneAngle[1] = 0;
    sceneAngle[2] = 0;

    // satelliteDistance
    satelliteDistance = 2;

	} // constructor

// called when OpenGL context is set up
void SolarSystemWidget::initializeGL()
	{ // initializeGL()

  // Initialise quadrics
  this->sun = gluNewQuadric();
  this->earth = gluNewQuadric();
  this->moon = gluNewQuadric();
  this->jupiter = gluNewQuadric();
  this->neptune = gluNewQuadric();
  // satellite
  this->satellite = gluNewQuadric();
  this->joint[0] = gluNewQuadric();
  this->joint[1] = gluNewQuadric();
  this->panel[0] = gluNewQuadric();
  this->panel[1] = gluNewQuadric();

  // Textures
  glGenTextures(6, this->textures);

  // Background texture
  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, back_image.Width(), back_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, back_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Sun texture
  glActiveTexture(GL_TEXTURE1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sun_image.Width(), sun_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, sun_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Earth texture
  glActiveTexture(GL_TEXTURE2);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[2]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, earth_image.Width(), earth_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, earth_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Moon texture
  glActiveTexture(GL_TEXTURE3);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[3]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, moon_image.Width(), moon_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, moon_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Jupiter texture
  glActiveTexture(GL_TEXTURE4);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[4]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, jupiter_image.Width(), jupiter_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, jupiter_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Neptune texture
  glActiveTexture(GL_TEXTURE5);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->textures[5]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, neptune_image.Width(), neptune_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, neptune_image.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	} // initializeGL()


// called every time the widget is resized
void SolarSystemWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {0., 0., 0., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-16.0, 16.0, -16.0, 16.0, -16.0, 16.0);
  gluLookAt(1.0,1.0,1.0, 0.0,0.0,0.0, 0.0,1.0,0.0);

	} // resizeGL()

// Objects
void SolarSystemWidget::drawSun() {
  glBindTexture(GL_TEXTURE_2D, this->textures[1]);
  gluQuadricDrawStyle(this->sun, GLU_FILL);
  gluQuadricTexture(this->sun, GL_TRUE);
  gluSphere(this->sun,1.5,20,20);
}

void SolarSystemWidget::drawEarth() {
  glBindTexture(GL_TEXTURE_2D, this->textures[2]);
  gluQuadricDrawStyle(this->earth, GLU_FILL);
  gluQuadricTexture(this->earth, GL_TRUE);
  gluSphere(this->earth,1,20,20);
}

void SolarSystemWidget::drawMoon() {
  glBindTexture(GL_TEXTURE_2D, this->textures[3]);
  gluQuadricDrawStyle(this->moon, GLU_FILL);
  gluQuadricTexture(this->moon, GL_TRUE);
  gluSphere(this->moon,0.2,20,20);
}

void SolarSystemWidget::drawNeptune() {
  glBindTexture(GL_TEXTURE_2D, this->textures[5]);
  gluQuadricDrawStyle(this->neptune, GLU_FILL);
  gluQuadricTexture(this->neptune, GL_TRUE);
  gluSphere(this->neptune,0.7,25,25);
}

void SolarSystemWidget::drawSatelliteBody() {
  // Set material properties, pushing the lighting so as not to effect other objects
  glPushAttrib(GL_LIGHTING_BIT);
  GLfloat ambient[4] = {0.17,0.012,0.012,1.0};
  GLfloat diffuse[4] = {0.61,0.04,0.04,1.0};
  GLfloat specular[4] = {0.73,0.63,0.63,1.0};
  GLfloat shininess = 0.6;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess*128);

  gluQuadricDrawStyle(this->satellite, GLU_FILL);
  gluCylinder(this->satellite,0.2,0.2,0.6,10,10);

  // Close the cylinder with disks
  glPushMatrix();
    glTranslatef(0,0,0.6);
    gluDisk(this->satellite,0,0.2,10,1);
  glPopMatrix();
  glPushMatrix();
    glRotatef(180,1,0,0);
    gluDisk(this->satellite,0,0.2,10,1);
  glPopMatrix();
  // Add the joints
  glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-0.3,0,0.2);
    gluCylinder(this->joint[0],0.05,0.05,0.1,5,5);
    // First solar panel
    glPushMatrix();
    glTranslatef(0,0,0.1);
      this->drawSolarPanel();
    glPopMatrix();

    glTranslatef(0,0,-0.5);
    gluCylinder(this->joint[1],0.05,0.05,0.1,5,5);
    // First solar panel
    glPushMatrix();
    glTranslatef(0,0,-0.5);
      this->drawSolarPanel();
    glPopMatrix();
  glPopMatrix();
  glPopAttrib();
}

void SolarSystemWidget::drawSolarPanel() {
  // Normals
  GLfloat normals[6][3] = { {1., 0. ,0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glVertex3f( 0.1, -0.01,  0.5);
    glVertex3f( 0.1, -0.01, 0);
    glVertex3f( 0.1,  0.01, 0);
    glVertex3f( 0.1,  0.01,  0.5);
  glEnd();

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
    glVertex3f( -0.1, -0.01,  0.5);
    glVertex3f( -0.1, -0.01, 0);
    glVertex3f( -0.1,  0.01, 0);
    glVertex3f( -0.1,  0.01,  0.5);
  glEnd();

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.01, 0.5);
    glVertex3f( 0.1, -0.01, 0.5);
    glVertex3f( 0.1,  0.01, 0.5);
    glVertex3f(-0.1,  0.01, 0.5);
  glEnd();

  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.01, 0);
    glVertex3f( 0.1, -0.01, 0);
    glVertex3f( 0.1,  0.01, 0);
    glVertex3f(-0.1,  0.01, 0);
  glEnd();

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
    glVertex3f(  0.1,  0.01,  0.5);
    glVertex3f(  0.1,  0.01, 0);
    glVertex3f( -0.1,  0.01, 0);
    glVertex3f( -0.1,  0.01,  0.5);
  glEnd();

  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
    glVertex3f(  0.1,  -0.01,  0.5);
    glVertex3f(  0.1,  -0.01, 0);
    glVertex3f( -0.1,  -0.01, 0);
    glVertex3f( -0.1,  -0.01,  0.5);
  glEnd();
}

void SolarSystemWidget::drawJupiter() {
  glBindTexture(GL_TEXTURE_2D, this->textures[4]);
  gluQuadricDrawStyle(this->jupiter, GLU_FILL);
  gluQuadricTexture(this->jupiter, GL_TRUE);
  gluSphere(this->jupiter,1,50,50);
}

// called every time the widget needs painting
void SolarSystemWidget::paintGL()
	{ // paintGL()
	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Background image of distant stars (static) -- texture inside of sphere??
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, this->textures[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glLoadIdentity();
    glOrtho(-16.0, 16.0, -16.0, 16.0, -16.0, 16.0);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex2f(-16,-16);

      glTexCoord2f(1,0);
      glVertex2f(16,-16);

      glTexCoord2f(1,1);
      glVertex2f(16,16);

      glTexCoord2f(0,1);
      glVertex2f(-16,16);
    glEnd();
    glEnable(GL_DEPTH_TEST);
  glPopMatrix();
  glClear(GL_DEPTH_BUFFER_BIT);

	// Prepare for 3D scene
  glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  // Contains whole scene excluding background
  glPushMatrix();
    // ***** Set scene angle *****
    glRotatef(this->sceneAngle[0], 1, 0, 0);
    glRotatef(this->sceneAngle[1], 0, 1, 0);
    glRotatef(this->sceneAngle[2], 0, 0, 1);

    // ***** Central sphere ("sun") *****
    glPushMatrix();
      glRotatef(this->sunAngle, 0, 1, 0);
      this->drawSun();
    glPopMatrix();

    // ***** Sphere 1 ("earth") *****
    glPushMatrix();
      // Rotation about central sphere and distance from central sphere
      glRotatef(this->sphereAngles[0], 0, 1, 0);
      glTranslatef(EARTH_DISTANCE,0,0);
      // Axis rotation
      glRotatef(this->axisAngles[0], 0, 1, 0);
      // Using GL_ADD to make the scene brighter, if somewhat less realistic
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
      this->drawEarth();

      // ***** "Moon" of sphere 1 *****
      glRotatef(this->sphere1Moon1Angle, 0, 1, 0);
      glTranslatef(MOON_DISTANCE,0,-MOON_DISTANCE);
      this->drawMoon();
    glPopMatrix();

    // ***** Sphere 2 *****
    // This object is not in orbit around an axis so the translation needed is
    // not trivial. The rotation is around the vector (1,4), therefore the normal
    // vector is required for the starting point of the object in order that it
    // still orbits around the origin (sun). The cross operator is used.
    glPushMatrix();
      // Rotation about central sphere and distance from central sphere
      glRotatef(this->sphereAngles[1], 1, 4, 0);
      glTranslatef(-4*(NEPTUNE_DISTANCE),NEPTUNE_DISTANCE,0);
      // Axis rotation
      glRotatef(this->axisAngles[1], 0, 1, 0);
      this->drawNeptune();

      // ***** User sends satellite to this sphere *****
      glRotatef(this->satelliteAngle, 0, 1, 0);
      glTranslatef(this->satelliteDistance,0,0);
      this->drawSatelliteBody();
      // glPushMatrix();

    glPopMatrix();

    // ***** Sphere 3 ("Jupiter") *****
    glPushMatrix();
      // Rotation about central sphere and distance from central sphere
      glRotatef(this->sphereAngles[2], 0, 1, 0);
      glTranslatef(JUPITER_DISTANCE,0,0);
      // Axis rotation
      glRotatef(this->axisAngles[2], 0, 1, 0);
      this->drawJupiter();
    glPopMatrix();

  glPopMatrix();

  // Set active texture to default
  glActiveTexture(GL_TEXTURE0);

	// flush to screen
	glFlush();

	} // paintGL()

void SolarSystemWidget::setxAngle(int newAngle)  {
  this->sceneAngle[0] = (float)newAngle;
  this->update();
}

void SolarSystemWidget::setyAngle(int newAngle)  {
  this->sceneAngle[1] = (float)newAngle;
  this->update();
}

void SolarSystemWidget::setzAngle(int newAngle)  {
  this->sceneAngle[2] = (float)newAngle;
  this->update();
}

void SolarSystemWidget::incrementAngle()  {
  // Rotation of spheres on their axis, one in different direction
  this->sunAngle = sunAngle + 0.25;
  this->axisAngles[0] = axisAngles[0] + 0.5;
  this->axisAngles[1] = axisAngles[1] - 0.5;
  this->axisAngles[2] = axisAngles[2] + 0.5;

  // Rotation around central sphere/planet, moon in reverse direction
  this->sphereAngles[0] = sphereAngles[0] + 1;
  this->sphere1Moon1Angle = sphere1Moon1Angle - 2;
  this->sphereAngles[1] = sphereAngles[1] + 2;
  this->sphereAngles[2] = sphereAngles[2] + 3;
  this->update();
}

#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <QTimer>
#include "SolarSystemWidget.h"


// constructor
SolarSystemWidget::SolarSystemWidget(QWidget *parent)
	: QGLWidget(parent),
  back_image("./Textures/stars.jpeg"),
  sun_image("./Textures/2k_sun.jpg"),
  earth_image("./Textures/earth.ppm")
  // moon_image("./Textures/2k_moon.jpg"),
  // jupiter_image("./Textures/2k_jupiter.jpg")
	{ // constructor
    sunAngle = 0;
    sphereAngles[0] = 0;
    sphere1Moon1Angle = 0;
    sphereAngles[1] = -30;
    sphereAngles[2] = 0;

    // Scene angles (x,y,z)
    sceneAngle[0] = 0;
    sceneAngle[1] = 0;
    sceneAngle[2] = 0;

	} // constructor

// called when OpenGL context is set up
void SolarSystemWidget::initializeGL()
	{ // initializeGL()

  // Initialise quadrics
  this->sun = gluNewQuadric();
  this->earth = gluNewQuadric();
  // this->moon = gluNewQuadric();
  // this->jupiter = gluNewQuadric();

  // Textures
  glGenTextures(5, this->textures);

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
  // glActiveTexture(GL_TEXTURE3);
  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, this->textures[3]);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, moon_image.Width(), moon_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, moon_image.imageField());
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //
  // // Jupiter texture
  // glActiveTexture(GL_TEXTURE4);
  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, this->textures[4]);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, jupiter_image.Width(), jupiter_image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, jupiter_image.imageField());
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

      glBindTexture(GL_TEXTURE_2D, this->textures[1]);
      gluQuadricDrawStyle(this->sun, GLU_FILL);
      gluQuadricTexture(this->sun, GL_TRUE);
      gluSphere(this->sun,1.5,20,20);
    glPopMatrix();

    // ***** Sphere 1 ("earth") *****
    glPushMatrix();
      glRotatef(this->sphereAngles[0], 0, 1, 0);
      glTranslatef(3,0,0);

      glBindTexture(GL_TEXTURE_2D, this->textures[2]);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      gluQuadricDrawStyle(this->earth, GLU_FILL);
      gluQuadricTexture(this->earth, GL_TRUE);
      gluSphere(this->earth,1,20,20);

      // ***** "Moon" of sphere 1 *****
      glRotatef(this->sphere1Moon1Angle, 0, 1, 0);
      glTranslatef(1,0,-1);
      glActiveTexture(GL_TEXTURE0);
      // // glBindTexture(GL_TEXTURE_2D, this->textures[3]);
      // gluQuadricDrawStyle(this->moon, GLU_FILL);
      // gluQuadricTexture(this->moon, GL_TRUE);
      // gluSphere(this->moon,0.2,20,20);
    glPopMatrix();

    // ***** Sphere 2 *****
    // This object is not in orbit around an axis so the translation needed is
    // not trivial. The rotation is around the vector (1,4), therefore the normal
    // vector is required for the starting point of the object in order that it
    // still orbits around the origin (sun). The cross operator is used.
    glPushMatrix();

      glRotatef(this->sphereAngles[1], 1, 4, 0);
      glTranslatef(-6,1.5,0);
      glutSolidSphere(0.7, 25, 25);

    glPopMatrix();

    // ***** Sphere 3 ("Jupiter") *****
    glPushMatrix();
      glRotatef(this->sphereAngles[2], 0, 1, 0);
      glTranslatef(10,0,0);

      // // glBindTexture(GL_TEXTURE_2D, this->textures[4]);
      // gluQuadricDrawStyle(this->jupiter, GLU_FILL);
      // gluQuadricTexture(this->jupiter, GL_TRUE);
      // gluSphere(this->jupiter,1,20,20);
    glPopMatrix();

  glPopMatrix();

  // Set active texture to default
  // glActiveTexture(GL_TEXTURE0);

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
  this->sunAngle = sunAngle + 0.25;
  this->sphereAngles[0] = sphereAngles[0] + 1;
  this->sphere1Moon1Angle = sphere1Moon1Angle - 2;
  this->sphereAngles[1] = sphereAngles[1] + 2;
  this->sphereAngles[2] = sphereAngles[2] + 3;
  this->update();
}

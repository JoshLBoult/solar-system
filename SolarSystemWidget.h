#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QObject>
#include <QImage>
#include "Image.h"

class SolarSystemWidget: public QGLWidget
	{ //

	public:
	SolarSystemWidget(QWidget *parent);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:
  Q_OBJECT

  // Object drawing
  void drawSun();
  void drawEarth();
  void drawMoon();
  void drawNeptune();
  void drawJupiter();

  // Angles of rotation about axes and other objects
  float sceneAngle[3];

  float sunAngle;
  float axisAngles[3];
  float sphereAngles[3];
  float sphere1Moon1Angle;
  float satelliteAngle;
  float satelliteDistance;

  // Texture images
  Image back_image;
  Image sun_image;
  Image earth_image;
  Image moon_image;
  Image jupiter_image;
  Image neptune_image;

  // Quadric spheres
  GLUquadric* sun;
  GLUquadric* earth;
  GLUquadric* moon;
  GLUquadric* jupiter;
  GLUquadric* neptune;

  // Quadric cylinders
  GLUquadric* satellite;

  // Texture array
  GLuint textures[6];

  public slots:

  void setxAngle(int newAngle);
  void setyAngle(int newAngle);
  void setzAngle(int newAngle);
  void incrementAngle();

	}; // class GLPolygonWidget

#endif

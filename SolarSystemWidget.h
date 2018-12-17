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
	void fillimage();
  float sceneAngle[3];

  float sunAngle;
  float sphereAngles[3];
  float sphere1Moon1Angle;

  // Texture images
  Image back_image;
  // Image sun_image;
  // Image earth_image;
  // Image moon_image;
  // Image jupiter_image;

  // Quadric spheres
  GLUquadric* sun;
  Image sun_image;
  GLUquadric* earth;
  Image earth_image;
  // GLUquadric* moon;
  // GLUquadric* jupiter;

  // Texture array
  GLuint textures[5];

  public slots:

  void setxAngle(int newAngle);
  void setyAngle(int newAngle);
  void setzAngle(int newAngle);
  void incrementAngle();

	}; // class GLPolygonWidget

#endif

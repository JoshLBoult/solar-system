#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QObject>
#include <QImage>
#include "Image.h"

// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

// Setting up the definition of a planet
typedef struct planetStruct {
  float angle;
  int moons;
  float moonAngles[];
} planetBody;

static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};

static materialStruct emeraldMaterials = {
  { 0.02, 0.17, 0.02, 1.0},
  { 0.08, 0.61, 0.08, 1.0},
  { 0.63, 0.73, 0.63, 1.0},
  76.8
};

static materialStruct pearlMaterials = {
  { 0.25, 0.21, 0.21, 1.0},
  { 1.00, 0.83, 0.83, 1.0},
  { 0.30, 0.30, 0.30, 1.0},
  11.26
};

static materialStruct rubyMaterials = {
  { 0.17, 0.01, 0.01, 1.0},
  { 0.61, 0.04, 0.04, 1.0},
  { 0.73, 0.63, 0.63, 1.0},
  76.8
};

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
  // sets the material
  void setMaterial(materialStruct *p_front);

	private:
  Q_OBJECT
	void fillimage();
  float sceneAngle[3];

  float sunAngle;
  float sphereAngles[3];
  float sphere1Moon1Angle;

  GLUquadric* sun;
  Image sun_image;
  QImage* p_qimage;

  // Earth-like object
  GLUquadric* earth;
  Image earth_image;
  QImage* earth_p_qimage;

  public slots:

  void setxAngle(int newAngle);
  void setyAngle(int newAngle);
  void setzAngle(int newAngle);
  void incrementAngle();

	}; // class GLPolygonWidget

#endif

#include <QGLWidget>
#include <QObject>
#include <QImage>
#include "Image.h"

class SolarSystemWidget: public QGLWidget
	{

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
  void drawSatelliteBody();
  void drawSolarPanel();

  // Angles of rotation about axes and other objects
  float sceneAngle[3];

  float sunAngle;
  float axisAngles[3];
  float sphereAngles[3];
  float sphere1Moon1Angle;
  float satelliteAngle;
  float satelliteDistance;
  float satelliteSpeed;
  float solarPanelAngle[2];


  // Texture images
  Image back_image;
  Image sun_image;
  Image earth_image;
  Image moon_image;
  Image jupiter_image;
  Image neptune_image;
  Image moi_image;

  // Quadric spheres
  GLUquadric* sun;
  GLUquadric* earth;
  GLUquadric* moon;
  GLUquadric* jupiter;
  GLUquadric* neptune;

  // Quadric cylinders
  GLUquadric* satellite;
  GLUquadric* satelliteEnd;
  GLUquadric* joint[2];

  // Texture array
  GLuint textures[7];

  public slots:

  void setxAngle(int newAngle);
  void setyAngle(int newAngle);
  void setzAngle(int newAngle);
  void incrementAngle();
  void setSpeed(int newSpeed);
  void setDistance(int newDistance);

	};

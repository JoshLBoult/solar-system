#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QTimer>
#include "SolarSystemWidget.h"

class SolarSystemWindow: public QWidget
	{
	public:


	// constructor / destructor
	SolarSystemWindow(QWidget *parent);
	~SolarSystemWindow();

	// visual hierarchy

	// window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
	SolarSystemWidget *systemWidget;

  // Add sliders to control viewing angle
  QSlider *x_angleSlider;
  QSlider *y_angleSlider;
  QSlider *z_angleSlider;

  // Add timers
  QTimer *angleTimer;

	// resets all the interface elements
	void ResetInterface();
	};

#endif
#include <QGLWidget>
#include <QSlider>
#include <QSpinBox>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTimer>
#include "SolarSystemWidget.h"

class SolarSystemWindow: public QWidget
	{
	public:


	// constructor / destructor
	SolarSystemWindow(QWidget *parent);
	~SolarSystemWindow();

	// window layout
	QBoxLayout *windowLayout;

  // Satellite layout
  QBoxLayout *satelliteLayout;
  QLabel *speedLabel;
  QSpinBox *speedSpinBox;
  QLabel *orbitLabel;
  QSpinBox *orbitSpinBox;

	// beneath that, the main widget
	SolarSystemWidget *systemWidget;

  // Add sliders to control viewing angle
  QSlider *x_angleSlider;
  QSlider *y_angleSlider;
  QSlider *z_angleSlider;

  // Layout to hold sliders;
  QBoxLayout *xSliderLayout;
  QLabel *xLabel;
  QBoxLayout *ySliderLayout;
  QLabel *yLabel;
  QBoxLayout *zSliderLayout;
  QLabel *zLabel;

  // Add timers
  QTimer *angleTimer;
	};

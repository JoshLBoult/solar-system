#include "SolarSystemWindow.h"

// constructor / destructor
SolarSystemWindow::SolarSystemWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

  // timers
  angleTimer = new QTimer(this);
  angleTimer->start(25);

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	systemWidget = new SolarSystemWidget(this);
	windowLayout->addWidget(systemWidget);

	// create sliders
  x_angleSlider = new QSlider(Qt::Horizontal);
    x_angleSlider->setMinimum(-180);
    x_angleSlider->setMaximum(180);
    x_angleSlider->setValue(0);
  y_angleSlider = new QSlider(Qt::Horizontal);
    y_angleSlider->setMinimum(-180);
    y_angleSlider->setMaximum(180);
    y_angleSlider->setValue(0);
  z_angleSlider = new QSlider(Qt::Horizontal);
    z_angleSlider->setMinimum(-180);
    z_angleSlider->setMaximum(180);
    z_angleSlider->setValue(0);
	windowLayout->addWidget(x_angleSlider);
  windowLayout->addWidget(y_angleSlider);
  windowLayout->addWidget(z_angleSlider);

  // Signals and slots
  connect(x_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setxAngle(int)));
  connect(y_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setyAngle(int)));
  connect(z_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setzAngle(int)));

  connect(angleTimer, SIGNAL(timeout()), systemWidget, SLOT(incrementAngle()));

	} // constructor


SolarSystemWindow::~SolarSystemWindow()
	{ // destructor
  delete x_angleSlider;
  delete y_angleSlider;
  delete z_angleSlider;
	delete systemWidget;
	delete windowLayout;
	} // destructor

// resets all the interface elements
// void SolarSystemWindow::ResetInterface()
// 	{ // ResetInterface()
//
//   y_angleSlider->setMinimum(0);
//   y_angleSlider->setMaximum(360);
//   y_angleSlider->setTickInterval(45);
//   y_angleSlider->setValue(180);
//
//
// 	// now force refresh
// 	systemWidget->update();
// 	update();
// 	} // ResetInterface()

#include "SolarSystemWindow.h"


SolarSystemWindow::SolarSystemWindow(QWidget *parent)
	: QWidget(parent)
	{
  // timers
  angleTimer = new QTimer(this);
  angleTimer->start(25);

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

  // Satellite interaction at the top of window
  satelliteLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  speedLabel = new QLabel("Satellite speed:");
    speedSpinBox = new QSpinBox;
    speedSpinBox->setRange(0,5);
    speedSpinBox->setValue(1);
  orbitLabel = new QLabel("Satellite distance:");
    orbitSpinBox = new QSpinBox;
    orbitSpinBox->setRange(1,5);
    orbitSpinBox->setValue(2);

  satelliteLayout->addWidget(speedLabel);
  satelliteLayout->addWidget(speedSpinBox);
  satelliteLayout->addWidget(orbitLabel);
  satelliteLayout->addWidget(orbitSpinBox);
  windowLayout->addLayout(satelliteLayout);

	// create main widget
	systemWidget = new SolarSystemWidget(this);
	windowLayout->addWidget(systemWidget);

	// create sliders for changing the scene viewing angle
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

  // Create new layouts to hold sliders and labels
  xSliderLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  xLabel = new QLabel("X viewing angle: ");
    xSliderLayout->addWidget(xLabel);
    xSliderLayout->addWidget(x_angleSlider);
  ySliderLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  yLabel = new QLabel("Y viewing angle: ");
    ySliderLayout->addWidget(yLabel);
    ySliderLayout->addWidget(y_angleSlider);

  zSliderLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  zLabel = new QLabel("Z viewing angle: ");
    zSliderLayout->addWidget(zLabel);
    zSliderLayout->addWidget(z_angleSlider);

  // Add sliders and labels
  windowLayout->addLayout(xSliderLayout);
  windowLayout->addLayout(ySliderLayout);
  windowLayout->addLayout(zSliderLayout);

  // Signals and slots
  connect(x_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setxAngle(int)));
  connect(y_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setyAngle(int)));
  connect(z_angleSlider, SIGNAL(valueChanged(int)), systemWidget, SLOT(setzAngle(int)));

  connect(angleTimer, SIGNAL(timeout()), systemWidget, SLOT(incrementAngle()));

  connect(speedSpinBox, SIGNAL(valueChanged(int)), systemWidget, SLOT(setSpeed(int)));
  connect(orbitSpinBox, SIGNAL(valueChanged(int)), systemWidget, SLOT(setDistance(int)));

	}


SolarSystemWindow::~SolarSystemWindow()
	{
  delete x_angleSlider;
  delete y_angleSlider;
  delete z_angleSlider;
  delete speedSpinBox;
  delete orbitSpinBox;
  delete xLabel;
  delete yLabel;
  delete zLabel;
  delete speedLabel;
  delete orbitLabel;
  delete angleTimer;
	delete systemWidget;
  delete xSliderLayout;
  delete ySliderLayout;
  delete zSliderLayout;
  delete satelliteLayout;
	delete windowLayout;
	}

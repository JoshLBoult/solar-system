#include <QApplication>
#include "SolarSystemWindow.h"

int main(int argc, char *argv[])
	{
	// create the application
	QApplication app(argc, argv);

	// create a master widget
  SolarSystemWindow *window = new SolarSystemWindow(NULL);

	// resize the window
	window->resize(712, 812);

	// show the label
	window->show();

	// start it running
	app.exec();

	// clean up
	delete window;

	// return to caller
	return 0;
	}

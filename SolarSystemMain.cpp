#include <QApplication>
#include <QVBoxLayout>
#include <GL/glut.h>
#include "SolarSystemWindow.h"

int main(int argc, char *argv[])
	{ // main()
	// create the application
	QApplication app(argc, argv);
  glutInit(&argc, argv);

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
	} // main()

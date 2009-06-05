#include <QtGui/QApplication>
#include "scenemodeller.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	SceneModeller w;
	w.show();
	w.showDockWindows();
	//w.showFullScreen();
	return a.exec();
}

#include <QtGui/QApplication>
#include "rytracer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Rytracer w;
	w.show();
	return a.exec();
}

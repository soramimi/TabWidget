#include "MainWindow.h"

#include <QApplication>
#include <QImage>
#include <QPainter>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

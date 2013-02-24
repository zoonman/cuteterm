#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("ZM Software");
	QCoreApplication::setOrganizationDomain("www.zoonman.com");
	QCoreApplication::setApplicationName("CuteTerm");
	MainWindow w;
	w.show();
	return a.exec();
}

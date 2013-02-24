#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qextserialport.h"
#include <QMainWindow>
#include <QSettings>
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		QString portName;
		QextSerialPort serialPortInterface;

	private slots:
		void on_pushButtonChahgePortState_clicked();

		void on_pushButtonSendBytes_clicked();

		void on_pushButtonClearSpace_clicked();

	private:
		Ui::MainWindow *ui;
		QSettings settings;
	public slots:
		void onDataAvailable();
};

#endif // MAINWINDOW_H

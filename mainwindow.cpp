#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QList<QString> serialPortsList;// хреновенько, но на первое время пойдет
	serialPortsList <<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"<<"COM7"<<"COM8"<<"COM9";
	serialPortsList <<"/dev/ttyS0"<<"/dev/ttyS1"<<"/dev/ttyS2"<<"/dev/ttyS3"<<"/dev/ttyS4"<<"/dev/ttyS5";
	ui->comboBoxPortList->addItems(serialPortsList);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButtonChahgePortState_clicked()
{
	bool spi_state = false;
	if (serialPortInterface.isOpen()) {
		ui->statusBar->showMessage("Closing port...", 3000);
		serialPortInterface.close();
		ui->pushButtonChahgePortState->setText("Open");
		ui->plainTextEditSend->setEnabled(false);
		ui->pushButtonSendBytes->setEnabled(false);
	}
	else {
		portName = ui->comboBoxPortList->currentText();
		serialPortInterface.setPortName(portName);
		serialPortInterface.setQueryMode(QextSerialPort::EventDriven);
		ui->pushButtonChahgePortState->setEnabled(false);
		ui->statusBar->showMessage("Probing to open " + portName);
		spi_state = serialPortInterface.open(QIODevice::ReadWrite);
		if (spi_state) {
			ui->statusBar->showMessage("Port is open!");
			ui->pushButtonChahgePortState->setText("Close");
			ui->plainTextEditSend->setEnabled(true);
			ui->pushButtonSendBytes->setEnabled(true);
			ui->pushButtonChahgePortState->setEnabled(true);
			QObject::connect(&serialPortInterface, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
		}
		else {
			ui->statusBar->showMessage("Cannot open " + portName);
			ui->pushButtonChahgePortState->setEnabled(true);
		}
	}
}

void MainWindow::on_pushButtonSendBytes_clicked()
{
	serialPortInterface.write(ui->plainTextEditSend->toPlainText().toAscii());
	serialPortInterface.flush();

}

void MainWindow::onDataAvailable()
{
	QByteArray buffer = serialPortInterface.readAll();
	ui->statusBar->showMessage( tr("Recieved %d bytes").arg(buffer.length()) );
	ui->plainTextEditRecieved->setPlainText(buffer);
}

void MainWindow::on_pushButtonClearSpace_clicked()
{
	ui->plainTextEditRecieved->clear();
}

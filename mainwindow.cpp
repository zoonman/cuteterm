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

		switch (ui->comboBox_BaudRate->currentIndex()) {
			case 0:
				serialPortInterface.setBaudRate(BAUD110);
			break;
			case 1:
				serialPortInterface.setBaudRate(BAUD300);
			break;
			case 2:
				serialPortInterface.setBaudRate(BAUD600);
			break;
			case 3:
				serialPortInterface.setBaudRate(BAUD1200);
			break;
			case 4:
				serialPortInterface.setBaudRate(BAUD2400);
			break;
			case 5:
				serialPortInterface.setBaudRate(BAUD4800);
			break;
			case 6:
				serialPortInterface.setBaudRate(BAUD9600);
			break;
			case 7:
				serialPortInterface.setBaudRate(BAUD19200);
			break;
			case 8:
				serialPortInterface.setBaudRate(BAUD38400);
			break;
			case 9:
				serialPortInterface.setBaudRate(BAUD57600);
			break;
			case 10:
				serialPortInterface.setBaudRate(BAUD115200);
			break;
			default:
			break;
		}

		switch (ui->comboBox_DataBits->currentIndex()) {
			case 0:
				serialPortInterface.setDataBits(DATA_5);
			break;
			case 1:
				serialPortInterface.setDataBits(DATA_6);
			break;
			case 2:
				serialPortInterface.setDataBits(DATA_7);
			break;
			case 3:
				serialPortInterface.setDataBits(DATA_8);
			break;
			default:
			break;
		}

		switch (ui->comboBox_FlowControl->currentIndex()) {
			case 0:
				serialPortInterface.setFlowControl(FLOW_OFF);
			break;
			case 1:
				serialPortInterface.setFlowControl(FLOW_HARDWARE);
			break;
			case 2:
				serialPortInterface.setFlowControl(FLOW_XONXOFF);
			break;
			default:
			break;
		}

		switch(ui->comboBox_Parity->currentIndex()) {
			case 0:
				serialPortInterface.setParity(PAR_NONE);
			break;
			case 1:
				serialPortInterface.setParity(PAR_ODD);
			break;
			case 2:
				serialPortInterface.setParity(PAR_EVEN);
			break;
			case 3:
				serialPortInterface.setParity(PAR_MARK);
			break;
			case 4:
				serialPortInterface.setParity(PAR_SPACE);
			break;
		}

		switch (ui->comboBox_StopBits->currentIndex()) {
			case 0:
				serialPortInterface.setStopBits(STOP_1);
			break;
			case 1:
				serialPortInterface.setStopBits(STOP_1_5);
			break;
			case 2:
				serialPortInterface.setStopBits(STOP_2);
			break;
			default:
			break;
		}
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

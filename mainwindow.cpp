#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set_Gsm_OFF();

    rebootCount = 30;

    // create a timer
        timer = new QTimer(this);

        // setup signal and slot
        connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));

        // msec
        timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout(){

    rebootCount--;

    QString count = QStringLiteral("%1 sec").arg(rebootCount);

    ui->counterLabel->setText(count);

    if(rebootCount == 0){

        timer->stop();
        //qDebug("time to reboot");
        system("echo system rebooting..... > /dev/kmsg");
        //QProcess::execute("/home/launchApps/Apps/RebootApp/reboot.sh");
        this->close();
    }

}

void MainWindow::set_Gsm_OFF(){

    system("echo Turing OFF GSM Modem.... > /dev/kmsg");
    system("echo setting gpio value... > /dev/kmsg");
    system("echo 1 > /sys/class/gpio/PD12/value");
    system("sleep 1s");
    system("echo 0 > /sys/class/gpio/PD12/value");
}



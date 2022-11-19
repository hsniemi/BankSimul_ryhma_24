#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    showFullScreen();

    pRfid_dll = new Rfid_dll;


    connect(pRfid_dll , SIGNAL(dataReadDone()),
            this, SLOT(receiveDataReadDone()));

    pRfid_dll->interFaceFunctionOpenSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pRfid_dll ;
    pRfid_dll = nullptr;
    delete pRestApi_dll;
    pRestApi_dll = nullptr;
}

void MainWindow::receiveDataReadDone()
{
    cardNumber = pRfid_dll ->interFaceFunctionReturnCardNumber();
    qDebug()<<"Kortti luettu"<<cardNumber<<Qt::endl;

    pDLLPinCodeComponent = new DLLPinCodeComponent;
    connect(pDLLPinCodeComponent, SIGNAL(pinCodeValueDone()),
            this, SLOT(receivePinCodeValueDone()));
    pDLLPinCodeComponent->interfacePinCodeComponent();
}

void MainWindow::receivePinCodeValueDone()
{
    qDebug()<<"receivePinCodeValueDone";
    pinCode = "";

    pinCode = pDLLPinCodeComponent->pincodedllReturnValue();
    if (pinCode =="")
    {
        delete pDLLPinCodeComponent;
        pDLLPinCodeComponent = nullptr;
        return;
    }
    pRestApi_dll = new RestApi_dll;
    connect(pRestApi_dll, SIGNAL(responseFromRestApiDllAvailable()),
            this, SLOT(getResponseFromRestApiSlot()));
    pRestApi_dll->interfaceFunctionRestApi(cardNumber, pinCode);
}

void MainWindow::getResponseFromRestApiSlot()
{
    QByteArray response_data = pRestApi_dll->returnResponse();
    qDebug()<<"getResponseFromRestApiSlot: "<<response_data;
    if(response_data=="true")
    {
        pinTryCount = 0;
        ui->label->setText("Laita kortti lukijaan");
        qDebug()<<"x";
        pKortinluku = new kortinluku(this, cardNumber);

        pKortinluku->show();

        pKortinluku->exec();

        delete pKortinluku;
        pKortinluku=nullptr;

        delete pDLLPinCodeComponent;
        pDLLPinCodeComponent = nullptr;
    }
    else
    {
        if(pinTryCount<2)
        {
            ui->label->setText("kortti ja pin eivät täsmää");
            qDebug()<<"pin väärin";
            QThread::msleep(3000);
            pinTryCount++;
            qDebug()<<"pinTryCount: "<<pinTryCount;
            pDLLPinCodeComponent->interfacePinCodeComponent();
        }
        else
        {
            ui->label->setText("Kortti on suljettu");

            connect(pRestApi_dll, SIGNAL(deleteCardSignal()),
                    this, SLOT(receiveDeleteCardSignal()));
            pRestApi_dll->deleteCard(cardNumber);
        }
    }
    qDebug()<<"poistutaan getResponse-slotista";
}

void MainWindow::receiveDeleteCardSignal()
{
    qDebug()<<"mainwindow: receiveDeleteCardSignal";
    QThread::msleep(3000);
    ui->label->setText("Laita kortti lukijaan");
    pinTryCount =  0;
    delete pDLLPinCodeComponent;
    pDLLPinCodeComponent = nullptr;
}



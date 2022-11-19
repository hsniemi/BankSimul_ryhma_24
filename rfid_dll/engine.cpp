#include "engine.h"


engine::engine(QObject *parent):QObject(parent)
{
    pQSerialPort = new QSerialPort(this);
    connect(pQSerialPort, SIGNAL(readyRead()),
            this, SLOT(readSerialPort()));
}

engine::~engine()
{
    delete pQSerialPort;
    pQSerialPort = nullptr;
}

void engine::openSerialPort()
{
    pQSerialPort->setPortName("COM5");
    pQSerialPort->setBaudRate(9600);
    pQSerialPort->setDataBits(QSerialPort::Data8);
    pQSerialPort->setParity(QSerialPort::NoParity);
    pQSerialPort->setStopBits(QSerialPort::OneStop);
    pQSerialPort->setFlowControl(QSerialPort::HardwareControl);
    if(!pQSerialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"ei aukea"<<Qt::endl;
    }
    else
    {
        qDebug()<<"portti aukesi"<<Qt::endl;
    }
}

void engine::readSerialPort()
{
     cardNumber="";
     cardNumber = pQSerialPort->readAll();
     emit readySignal();
}

QString engine::returnCardNumber()
{
    cardNumber.remove(0,3);
    cardNumber.chop(3);
    return cardNumber;
}

//void engine::closeSerialPort()
//{
//    qDebug()<<"serialport suljettu"<<Qt::endl;
//    pQSerialPort->close();
//}


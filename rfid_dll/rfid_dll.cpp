#include "rfid_dll.h"

Rfid_dll::Rfid_dll(QObject *parent):QObject(parent)
{
    pEngine = new engine(this);
}

Rfid_dll::~Rfid_dll()
{
    delete pEngine;
    pEngine = nullptr;
}

void Rfid_dll::interFaceFunctionOpenSerialPort()
{
    connect(pEngine, SIGNAL(readySignal()),
            this, SLOT(receiveReadySignalSlot()));
    pEngine->openSerialPort();
}

//void Rfid_dll::interFaceFunctionCloseSerialPort()
//{
//    pEngine->closeSerialPort();
//}

QString Rfid_dll::interFaceFunctionReturnCardNumber()
{
    return pEngine->returnCardNumber();
}

void Rfid_dll::receiveReadySignalSlot()
{
//    cardNumber = pEngine->returnCardNumber();
    emit dataReadDone();
}





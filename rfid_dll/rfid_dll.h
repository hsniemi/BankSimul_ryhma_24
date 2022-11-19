#ifndef RFID_DLL_H
#define RFID_DLL_H

#include "rfid_dll_global.h"
#include "engine.h"
#include <QSerialPort>

class RFID_DLL_EXPORT Rfid_dll:public QObject
{
    Q_OBJECT
public:
    RFID_DLL_EXPORT Rfid_dll(QObject *parent = nullptr);
    ~Rfid_dll();
    void RFID_DLL_EXPORT interFaceFunctionOpenSerialPort();
//    void RFID_DLL_EXPORT interFaceFunctionCloseSerialPort();

    QString RFID_DLL_EXPORT interFaceFunctionReturnCardNumber();

private:
    QString cardNumber;
    engine *pEngine;

private slots:
    void receiveReadySignalSlot();

signals:
    void dataReadDone();
};

#endif // RFID_DLL_H

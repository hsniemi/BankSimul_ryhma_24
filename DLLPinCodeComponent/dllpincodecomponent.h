#ifndef DLLPINCODECOMPONENT_H
#define DLLPINCODECOMPONENT_H

#include "DLLPinCodeComponent_global.h"
#include "pincodedialog.h"
#include <QString>
#include <QDebug>
#include <QObject>

class DLLPINCODECOMPONENT_EXPORT DLLPinCodeComponent:public QObject
{
    Q_OBJECT

public:
    // DLLPinCodeComponent();
    void interfacePinCodeComponent();
    QString pincodedllReturnValue();

private:
    PinCodeDialog *objectPinCodeDialog;
    QString pinCodeValue;
signals:
    void pinCodeValueDone();
};

#endif // DLLPINCODECOMPONENT_H

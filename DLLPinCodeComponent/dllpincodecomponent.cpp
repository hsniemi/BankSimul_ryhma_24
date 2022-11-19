#include "dllpincodecomponent.h"

//DLLPinCodeComponent::DLLPinCodeComponent()
//{

//}

void DLLPinCodeComponent::interfacePinCodeComponent()
{
    qDebug()<<"interfacePinCodeComponent";
    objectPinCodeDialog = new PinCodeDialog;
    objectPinCodeDialog->show();
    objectPinCodeDialog->exec();
// kun on painettu pinkoodi-ikkunassa "OK"
    pinCodeValue = objectPinCodeDialog->returnPincode();

    delete objectPinCodeDialog;
    objectPinCodeDialog = NULL;

    qDebug() << "DLLPinCodeComponent closed";
    emit pinCodeValueDone();
}

QString DLLPinCodeComponent::pincodedllReturnValue()
{
    return pinCodeValue;
}

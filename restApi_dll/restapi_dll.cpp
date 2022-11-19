#include "restapi_dll.h"

RestApi_dll::RestApi_dll(QObject *parent):QObject(parent)
{
    pEngine = new engine;
}

RestApi_dll::~RestApi_dll()
{
    delete pEngine;
    pEngine = nullptr;
}

void RestApi_dll::interfaceFunctionRestApi(QString cardNumber, QString pinCode)
{
    qDebug()<<"interfaceFunctionRestApi";
    connect(pEngine, SIGNAL(responseDone()),
            this, SLOT(receiveResponseDoneFromEngine()));
    pEngine->checkCardNumberAndPin(cardNumber, pinCode);
}

void RestApi_dll::receiveResponseDoneFromEngine()
{
    qDebug()<<"receiveResponseDoneFromEngine";
    emit responseFromRestApiDllAvailable();
}
QByteArray RestApi_dll::returnResponse()
{
    qDebug()<<"restApi: returnResponse";
    QByteArray response_data = pEngine->returnResponse();
    return response_data;
}

void RestApi_dll::getAccountId(QString pCardNumber)
{
    qDebug()<<"restApi: getAccountId";
    connect(pEngine, SIGNAL(AccountNumberDone()),
            this, SLOT(receiveAccountNumberDoneFromEngine()));
    pEngine->getAccountID(pCardNumber);
}

void RestApi_dll::getSaldo(QString tilinumero)
{
    connect(pEngine, SIGNAL(sendSaldoToInterface(double)),
            this, SLOT(receiveSaldoFromEngine(double)));

    pEngine->getSaldo(tilinumero);
}

void RestApi_dll::getTransactions5(QString tilinumero)
{
    connect(pEngine, SIGNAL(sendTransactions5(QString)),
            this, SLOT(receiveTransactions5(QString)));
    pEngine->getTransactions5(tilinumero);
}

void RestApi_dll::getCustomerInfo(QString cardNumber)
{
    qDebug()<<"restApi: getCustomerInfo";
    connect(pEngine, SIGNAL(sendCustomerInfo(QString)),
            this, SLOT(receiveCustomerInfo(QString)));
    connect(pEngine, SIGNAL(sendCustomerName(QString)),
            this, SLOT(receiveCustomerName(QString)));
    connect(pEngine, SIGNAL(sendMoneySignal(QString)),
            this, SLOT(receiveMoneySignal(QString)));
    pEngine->getCustomerInfo(cardNumber);
}

void RestApi_dll::getMoney(QString tilinumero, int summa)
{
    pEngine->getMoney(tilinumero, summa);
}

void RestApi_dll::siirto(QString saajan_tilinro, QString maksajan_tilinro, double summa)
{
    connect(pEngine, SIGNAL(accountNotFound()),
                this, SLOT(receiveAccountNotFound()));
    connect(pEngine, SIGNAL(accountFound(QString)),
                this, SLOT(receiveAccountFound(QString)));
    pEngine->siirto(saajan_tilinro, maksajan_tilinro, summa);
}

void RestApi_dll::receiveAccountNumberDoneFromEngine()
{
    emit sendAccountNumberDoneToExe();
}

void RestApi_dll::receiveSaldoFromEngine(double saldo)
{
    emit sendSaldoToExe(saldo);
}

void RestApi_dll::receiveCustomerInfo(QString asiakas)
{
    qDebug()<<"restApi: receivecustomerInfo";
    emit sendCustomerInfoToExe(asiakas);
}

void RestApi_dll::receiveTilitapahtumatFromEngine(QString tilitapahtumat)
{
    emit sendTilitapahtumatToExe(tilitapahtumat);
}

void RestApi_dll::receiveTransactions5(QString tilitapahtumat)
{
    emit sendTransactions5ToExe(tilitapahtumat);
}

void RestApi_dll::receiveAccountFound(QString response)
{
    emit accountFound(response);
}

void RestApi_dll::receiveCustomerName(QString asiakas_nimi)
{
    qDebug()<<"restApi: receivecustomerName";
    emit sendCustomerNameToExe(asiakas_nimi);
}

void RestApi_dll::receiveMoneySignal(QString response)
{
    qDebug()<<"restApi money: "<<response;
    emit moneySignal(response);
}

void RestApi_dll::receiveAccountNotFound()
{
    emit accountNotFound();
}

QString RestApi_dll::returnAccountNumber()
{
    return pEngine->returnAccountNumber();
}

void RestApi_dll::getTilitapahtumat(QString tilinumero, int offset)
{
    connect(pEngine, SIGNAL(sendTilitapahtumatToInterface(QString)),
            this, SLOT(receiveTilitapahtumatFromEngine(QString)));

    pEngine->getTilitapahtumat(tilinumero, offset);
}

void RestApi_dll::deleteCard(QString cardNumber)
{
    qDebug()<<"restApi: deleteCard";
    connect(pEngine, SIGNAL(deleteCardSignal()),
            this, SLOT(receiveDeleteCard()));
    pEngine->deleteCard(cardNumber);
}

void RestApi_dll::receiveDeleteCard()
{
    qDebug()<<"restApi: receiveDeleteCard";
    emit deleteCardSignal();
}

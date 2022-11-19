#ifndef RESTAPI_DLL_H
#define RESTAPI_DLL_H

#include "restApi_dll_global.h"
#include <QObject>
#include "engine.h"

class RESTAPI_DLL_EXPORT RestApi_dll:public QObject
{
    Q_OBJECT
public:
    RestApi_dll(QObject *parent = nullptr);
    ~RestApi_dll();
    void interfaceFunctionRestApi(QString, QString);
    QByteArray returnResponse();
    QString returnAccountNumber();
    void getAccountId(QString pCardNumber);
    void getSaldo(QString);
    void getTransactions5(QString);
    void getCustomerInfo(QString);
    void getMoney(QString, int);
    void getTilitapahtumat(QString, int);
    void siirto(QString, QString, double);
    void deleteCard(QString);

private:
    engine *pEngine;
    QString cardID;

private slots:
    void receiveResponseDoneFromEngine();
    void receiveAccountNumberDoneFromEngine();
    void receiveSaldoFromEngine(double);
    void receiveCustomerInfo(QString);
    void receiveTilitapahtumatFromEngine(QString);
    void receiveTransactions5(QString);
    void receiveAccountNotFound();
    void receiveAccountFound(QString);
    void receiveCustomerName(QString);
    void receiveMoneySignal(QString);
    void receiveDeleteCard();

signals:
    void responseFromRestApiDllAvailable();
    void sendAccountNumberDoneToExe();
    void sendSaldoToExe(double);
    void sendCustomerInfoToExe(QString);
    void sendTilitapahtumatToExe(QString);
    void sendTransactions5ToExe(QString);
    void accountNotFound();
    void accountFound(QString);
    void sendCustomerNameToExe(QString);
    void moneySignal(QString);
    void deleteCardSignal();
};

#endif // RESTAPI_DLL_H

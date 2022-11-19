#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QString>

class engine:public QObject
{
    Q_OBJECT
public:
    engine(QObject *parent = nullptr);
    void checkCardNumberAndPin(QString, QString);
    QByteArray returnResponse();
    QString returnAccountNumber();
    void getAccountID(QString);
    void getSaldo(QString);
    void getCustomerInfo(QString);
    void getTransactions5(QString);
    void getMoney(QString, int);
    void getTilitapahtumat(QString, int);
    void siirto(QString, QString, double);
    void deleteCard(QString);

private slots:
    void checkCardNumberAndPinSlot(QNetworkReply *reply);
    void accountIdSlot(QNetworkReply *reply);
    void getSaldoSlot(QNetworkReply *reply);
    void customerSlot(QNetworkReply  *reply);
    void getFiveSlot(QNetworkReply *reply);
    void getMoneySlot(QNetworkReply  *reply);
    void getTilitapahtumatSlot(QNetworkReply *reply);
    void siirtoSlot(QNetworkReply *reply);
    void deleteSlot(QNetworkReply *reply);

private:
    QNetworkAccessManager *pQNetworkAccessManager;
    QNetworkReply *pQNetworkReply;
    QNetworkAccessManager *pAccountIdManager;
    QNetworkReply *pAccountIdReply;
    QNetworkAccessManager *pSaldoManager;
    QNetworkReply *pSaldoReply;
    QNetworkAccessManager *pCustomerManager;
    QNetworkReply *pCustomerReply;
    QNetworkAccessManager *pGetFiveManager;
    QNetworkReply *pGetFiveReply;
    QNetworkAccessManager *pMoneyManager;
    QNetworkReply *pMoneyReply;
    QNetworkAccessManager *pSiirtoManager;
    QNetworkReply *pSiirtoReply;
    QNetworkAccessManager *pDeleteManager;
    QNetworkReply *pDeleteReply;
    QByteArray response_data;
    QString tilinumero;
    QString cardNumber;

    QNetworkAccessManager *pTilitapahtumatManager;
    QNetworkReply *pTilitapahtumatReply;

signals:
    void finished(QNetworkReply *reply);
    void responseDone();
    void AccountNumberDone();
    void sendSaldoToInterface(double);
    void sendCustomerInfo(QString);
    void sendTilitapahtumatToInterface(QString);
    void sendTransactions5(QString);
    void accountNotFound();
    void accountFound(QString);
    void sendCustomerName(QString);
    void sendMoneySignal(QString);
    void deleteCardSignal();
};

#endif // ENGINE_H

#ifndef SALDO_H
#define SALDO_H

#include <QDialog>
#include "restapi_dll.h"
#include <QTimer>


namespace Ui {
class saldo;
}

class saldo : public QDialog
{
    Q_OBJECT

public:
    explicit saldo(QWidget *parent = nullptr,QString pCardNumber="");
    ~saldo();

private slots:
    void on_pushButton_sulje_clicked();
    void getAccountNumberFromRestApiSlot();
    void receiveSaldoFromDll(double);
    void receiveCustomerInfoFromDll(QString);
    void receiveTransactions5FromDll(QString);
    void receiveTimeout();

private:
    Ui::saldo *ui;
    RestApi_dll *pRestApi;
    QString cardNumber;
    QString tilinumero;
    QTimer *pTimer;

};

#endif // SALDO_H

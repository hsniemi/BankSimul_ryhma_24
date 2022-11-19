#ifndef KORTINLUKU_H
#define KORTINLUKU_H

//#include <QDialog>
#include "dllpincodecomponent.h"
#include "restapi_dll.h"
#include <QObject>
#include <QDebug>
#include "saldo.h"
#include "nosto.h"
#include "tilitapahtumat.h"
#include "siirto.h"
#include <QTimer>

namespace Ui {
class kortinluku;
}

class kortinluku : public QDialog
{
    Q_OBJECT

public:
    explicit kortinluku(QWidget *parent = nullptr,QString pCardNumber="");
    ~kortinluku();
    void closeCard();

private slots:
    void on_pushButton_saldo_clicked();

    void on_pushButton_nosto_clicked();

    void on_pushButton_tilitapahtumat_clicked();

    void on_pushButton_siirto_clicked();

    void on_pushButton_kirjaudu_ulos_clicked();
    void receiveTimeout();
    void getAccountNumberFromRestApiSlot();
    void receiveCustomerNameFromDll(QString);

private:
    Ui::kortinluku *ui;
    saldo *psaldo;
    nosto *pnosto;
    tilitapahtumat *ptilitapahtumat;
    siirto *psiirto;
    QString cardNumber;
    QString tilinro;
    QTimer *pTimer;
    RestApi_dll *pRestApi;

};

#endif // KORTINLUKU_H

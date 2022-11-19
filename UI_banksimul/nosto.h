#ifndef NOSTO_H
#define NOSTO_H

#include <QDialog>
#include "restapi_dll.h"
#include <QTimer>

namespace Ui {
class nosto;
}

class nosto : public QDialog
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr,QString pCardNumber="");
    ~nosto();
    void updateSaldo();

private slots:
    void on_pushButton_sulje_nosto_clicked();

    void on_pushButton_nosta20_clicked();

    void on_pushButton_nosta40_clicked();

     void on_pushButton_nosta60_clicked();

    void on_pushButton_nosta100_clicked();

    void on_pushButton_nosta200_clicked();

    void on_pushButton_nosta500_clicked();

    void receiveCustomerInfo(QString);
    void receiveSaldo(double);
    void receiveTimerSignal();
    void receiveAccountNumberDone();
    void receiveMoneySignal(QString);

private:
    Ui::nosto *ui;
    RestApi_dll *pRestApiDll;
    QString cardNumber;
    QString tilinumero;
    QTimer *pTimer;
};

#endif // NOSTO_H

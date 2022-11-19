#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QDialog>
#include "restapi_dll.h"
#include <QTimer>

namespace Ui {
class tilitapahtumat;
}

class tilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit tilitapahtumat(QWidget *parent = nullptr, QString pCardNumber="");
    ~tilitapahtumat();

private slots:
    void on_pushButton_suljeTilitapahtumat_clicked();
    void getAccountNumberFromRestApiSlot();
    void receiveCustomerInfoFromDll(QString);
    void receiveSaldoFromDll(double);
    void receiveTilitapahtumat(QString);
    void receiveTimeout();

//    void on_pushButton_2_clicked();

    void on_pushButton_edelliset_clicked();

    void on_pushButton_seuraavat_clicked();

private:
    Ui::tilitapahtumat *ui;
    RestApi_dll *pRestApi;
    QString cardNumber;
    QString tilinumero;
    QTimer *pTimer;
    int offset = 0;
};

#endif // TILITAPAHTUMAT_H

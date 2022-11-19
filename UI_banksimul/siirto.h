#ifndef SIIRTO_H
#define SIIRTO_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include "restapi_dll.h"
#include <QTimer>

namespace Ui {
class siirto;
}

class siirto : public QDialog
{
    Q_OBJECT

public:
    explicit siirto(QWidget *parent = nullptr, QString pCardNumber="");
    ~siirto();

private slots:
    void on_pushButton_suljeSiirto_clicked();

    void getAccountNumberFromRestApiSlot();

    void on_pushButton_maksa_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_enter_clicked();
    void on_pushButton_backSpace_clicked();
    void receiveAccountNotFound();
    void receiveAccountFound(QString);
    void receiveTimeout();

private:
    Ui::siirto *ui;
    RestApi_dll *pRestApi;
    QString cardNumber;
    QString tilinro;
    QString tilinumero = "FI";
    QString label_summa;
    QTimer *pTimer;
};

#endif // SIIRTO_H

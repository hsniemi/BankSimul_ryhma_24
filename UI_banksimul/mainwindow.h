#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QDialog>
//#include "saldo.h"
#include "restapi_dll.h"
//#include "nosto.h"
//#include "tilitapahtumat.h"
//#include "siirto.h"
#include "rfid_dll.h"
#include "dllpincodecomponent.h"
#include "kortinluku.h"
#include <QTimer>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void receiveDataReadDone();
    void receivePinCodeValueDone();
    void getResponseFromRestApiSlot();
    void receiveDeleteCardSignal();

private:
    Ui::MainWindow *ui;
    kortinluku *pKortinluku;
    Rfid_dll *pRfid_dll;
    RestApi_dll *pRestApi_dll;
    DLLPinCodeComponent *pDLLPinCodeComponent;
    QTimer *pTimer;
    QString cardNumber;
    QString responseData;
    QString pinCode;
    int pinTryCount = 0;
};
#endif // MAINWINDOW_H

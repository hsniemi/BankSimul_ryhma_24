#include "saldo.h"
#include "ui_saldo.h"


saldo::saldo(QWidget *parent, QString pCardNumber) :
    QDialog(parent),
    ui(new Ui::saldo)
{
    ui->setupUi(this);
    cardNumber=pCardNumber;
    pRestApi = new RestApi_dll(this);

    connect(pRestApi, SIGNAL(sendAccountNumberDoneToExe()),
            this, SLOT(getAccountNumberFromRestApiSlot()));

    pRestApi->getAccountId(cardNumber);
}

saldo::~saldo()
{
    delete ui;
    delete pRestApi;
    pRestApi = nullptr;
    delete pTimer;
    pTimer = nullptr;
}

void saldo::on_pushButton_sulje_clicked()
{
    this->close();
}

void saldo::getAccountNumberFromRestApiSlot()
{
    tilinumero = pRestApi->returnAccountNumber();
    qDebug()<<"saldo.cpp:"<<tilinumero;
    connect(pRestApi, SIGNAL(sendCustomerInfoToExe(QString)),
            this, SLOT(receiveCustomerInfoFromDll(QString)));
    pRestApi->getCustomerInfo(cardNumber);
}

void saldo::receiveSaldoFromDll(double saldo)
{
    ui->labelSaldo->setNum(saldo);
    connect(pRestApi, SIGNAL(sendTransactions5ToExe(QString)),
            this, SLOT(receiveTransactions5FromDll(QString)));
    pRestApi->getTransactions5(tilinumero);
}

void saldo::receiveCustomerInfoFromDll(QString asiakas)
{
    qDebug()<<"saldo: receiveCustomerInfo";
    ui->labeltiedot->setText(asiakas);
    connect(pRestApi, SIGNAL(sendSaldoToExe(double)),
            this, SLOT(receiveSaldoFromDll(double)));
    pRestApi->getSaldo(tilinumero);
}

void saldo::receiveTransactions5FromDll(QString tilitapahtumat)
{
    ui->labelTilitapahtumat5->setText(tilitapahtumat);
    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &saldo::receiveTimeout);
    pTimer->start(10000);
}

void saldo::receiveTimeout()
{
    this->close();
}


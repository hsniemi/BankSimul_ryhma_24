#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"

tilitapahtumat::tilitapahtumat(QWidget *parent, QString pCardNumber) :
    QDialog(parent),
    ui(new Ui::tilitapahtumat)
{
    ui->setupUi(this);
    cardNumber=pCardNumber;
    pRestApi=new RestApi_dll;
    connect(pRestApi, SIGNAL(sendAccountNumberDoneToExe()),
            this, SLOT(getAccountNumberFromRestApiSlot()));
    pRestApi->getAccountId(cardNumber);

}

tilitapahtumat::~tilitapahtumat()
{
    delete ui;
    delete pRestApi;
    pRestApi = nullptr;
    delete pTimer;
    pTimer = nullptr;
}

void tilitapahtumat::on_pushButton_suljeTilitapahtumat_clicked()
{
    offset = 0;
    this->close();
}

void tilitapahtumat::getAccountNumberFromRestApiSlot()
{
    tilinumero = pRestApi->returnAccountNumber();
    connect(pRestApi, SIGNAL(sendCustomerInfoToExe(QString)),
            this, SLOT(receiveCustomerInfoFromDll(QString)));
    pRestApi->getCustomerInfo(cardNumber);
}

void tilitapahtumat::receiveCustomerInfoFromDll(QString asiakas)
{
    qDebug()<<"tilitapahtumat: receiveCustomerInfo";
    ui->label_tilitapahtumat_omistaja->setText(asiakas);
    connect(pRestApi, SIGNAL(sendSaldoToExe(double)),
            this, SLOT(receiveSaldoFromDll(double)));
    pRestApi->getSaldo(tilinumero);
}

void tilitapahtumat::receiveSaldoFromDll(double saldo)
{
    ui->label_saldoTilitapahtumat->setNum(saldo);
    pTimer = new QTimer(this);
    qDebug()<<pTimer;
    connect(pTimer, &QTimer::timeout, this, &tilitapahtumat::receiveTimeout);
    connect(pRestApi, SIGNAL(sendTilitapahtumatToExe(QString)),
            this, SLOT(receiveTilitapahtumat(QString)));
    pTimer->start(10000);
    pRestApi->getTilitapahtumat(tilinumero, offset);
}

void tilitapahtumat::receiveTilitapahtumat(QString tilitapahtumat)
{   
    ui->label_tilitapahtumat->setText(tilitapahtumat);
}

void tilitapahtumat::receiveTimeout()
{
    offset = 0;
    this->close();
}

void tilitapahtumat::on_pushButton_edelliset_clicked()
{
    pTimer->start();
    offset -= 10;
    pRestApi->getTilitapahtumat(tilinumero, offset);
}

void tilitapahtumat::on_pushButton_seuraavat_clicked()
{
    pTimer->start();
    offset += 10;
    pRestApi->getTilitapahtumat(tilinumero, offset);
}

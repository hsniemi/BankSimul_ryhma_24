#include "nosto.h"
#include "ui_nosto.h"

nosto::nosto(QWidget *parent, QString pCardNumber) :
    QDialog(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
    cardNumber=pCardNumber;
    pRestApiDll = new RestApi_dll;
    connect(pRestApiDll, SIGNAL(sendCustomerInfoToExe(QString)),
            this, SLOT(receiveCustomerInfo(QString)));
    pRestApiDll->getCustomerInfo(cardNumber);

}

nosto::~nosto()
{
    delete ui;
    delete pRestApiDll;
    pRestApiDll = nullptr;
    delete pTimer;
    pTimer = nullptr;
}

void nosto::updateSaldo()
{
    pRestApiDll->getSaldo(tilinumero);
}

void nosto::on_pushButton_sulje_nosto_clicked()
{
    this->close();
}

void nosto::on_pushButton_nosta20_clicked()
{
    pTimer->start();
    int summa = 20;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::on_pushButton_nosta40_clicked()
{
    pTimer->start();
    int summa = 40;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::on_pushButton_nosta60_clicked()
{
    pTimer->start();
    int summa = 60;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::on_pushButton_nosta100_clicked()
{
    pTimer->start();
    int summa = 100;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::on_pushButton_nosta200_clicked()
{
    pTimer->start();
    int summa = 200;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::on_pushButton_nosta500_clicked()
{
    pTimer->start();
    int summa = 500;
    pRestApiDll->getMoney(tilinumero,summa);
}

void nosto::receiveCustomerInfo(QString asiakas)
{
    qDebug()<<"nosto: receiveCustomerInfo";
    ui->label_nosto_omistaja->setText(asiakas);
    connect(pRestApiDll, SIGNAL(sendAccountNumberDoneToExe()),
            this, SLOT(receiveAccountNumberDone()));
    pRestApiDll->getAccountId(cardNumber);
}

void nosto::receiveSaldo(double saldo)
{
    ui->label_nosto_saldo->setNum(saldo);
}

void nosto::receiveTimerSignal()
{
    this->close();
}

void nosto::receiveAccountNumberDone()
{
    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &nosto::receiveTimerSignal);
    pTimer->start(10000);
    tilinumero = pRestApiDll->returnAccountNumber();
    connect(pRestApiDll, SIGNAL(moneySignal(QString)),
            this, SLOT(receiveMoneySignal(QString)));
    connect(pRestApiDll, SIGNAL(sendSaldoToExe(double)),
            this, SLOT(receiveSaldo(double)));
    pRestApiDll->getSaldo(tilinumero);
}

void nosto::receiveMoneySignal(QString response)
{
    updateSaldo();
    qDebug()<<"receiveMoneySignal slot";
    if(response=="\"Ei tarpeeksi rahaa\"")
    {
        qDebug()<<"receive moneySignal: "<<response;
        ui->label_nosto->setText("Tilillä ei ole tarpeeksi rahaa");
    }
    else if(response=="\"Rahaa nostettu\"")
    {
        qDebug()<<"receive moneySignal: "<<response;
        ui->label_nosto->setText("Nosto onnistui");
    }
}








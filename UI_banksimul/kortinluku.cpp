#include "kortinluku.h"
#include "ui_kortinluku.h"

kortinluku::kortinluku(QWidget *parent,QString pCardNumber) :
    QDialog(parent),
    ui(new Ui::kortinluku)
{
    ui->setupUi(this);
    cardNumber = pCardNumber;
    qDebug()<<"paavalikon muodostin, cardNumber: "<<cardNumber;

    pRestApi = new RestApi_dll;
    connect(pRestApi, SIGNAL(sendAccountNumberDoneToExe()),
            this, SLOT(getAccountNumberFromRestApiSlot()));
    pRestApi->getAccountId(cardNumber);
}

kortinluku::~kortinluku()
{
    qDebug()<<"päävalikko tuhoaja";
    delete ui;
    ui = nullptr;
    delete pTimer;
    pTimer=nullptr;
    delete pRestApi;
    pRestApi=nullptr;
}

void kortinluku::getAccountNumberFromRestApiSlot()
{
    QString tilinumero = pRestApi->returnAccountNumber();

    connect(pRestApi, SIGNAL(sendCustomerNameToExe(QString)),
            this, SLOT(receiveCustomerNameFromDll(QString)));
    pRestApi->getCustomerInfo(cardNumber);
}

void kortinluku::receiveCustomerNameFromDll(QString asiakas_nimi)
{
    ui->label->setText(asiakas_nimi);
    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &kortinluku::receiveTimeout);
    pTimer->start(30000);
}

void kortinluku::on_pushButton_saldo_clicked()
{
    pTimer->stop();
    psaldo = new saldo(this,cardNumber);
    psaldo -> setWindowTitle("saldo");
    psaldo -> showFullScreen();
    psaldo -> exec();
    pTimer->start();
    delete psaldo;
    psaldo = nullptr;

}

void kortinluku::on_pushButton_nosto_clicked()
{
    pTimer->stop();
    pnosto = new nosto(this,cardNumber);
    pnosto -> setWindowTitle("Nosta rahaa");
    pnosto -> showFullScreen();
    pnosto -> exec();
    pTimer->start();
    delete pnosto;
    pnosto = nullptr;
}

void kortinluku::on_pushButton_tilitapahtumat_clicked()
{
    pTimer->stop();
    ptilitapahtumat = new tilitapahtumat(this,cardNumber);
    ptilitapahtumat -> setWindowTitle("Tilitapahtumat");
    ptilitapahtumat -> showFullScreen();
    ptilitapahtumat -> exec();
    pTimer->start();
    delete ptilitapahtumat;
    ptilitapahtumat = nullptr;
}

void kortinluku::on_pushButton_siirto_clicked()
{
    pTimer->stop();
    psiirto = new siirto(this,cardNumber);
    psiirto -> setWindowTitle("Siirto");
    psiirto -> showFullScreen();
    psiirto -> exec();
    pTimer->start();
    delete psiirto;
    psiirto = nullptr;
}

void kortinluku::receiveTimeout()
{
    this->close();
}

void kortinluku::on_pushButton_kirjaudu_ulos_clicked()
{
    this->close();
}




#include "siirto.h"
#include "ui_siirto.h"


siirto::siirto(QWidget *parent, QString pCardNumber) :
    QDialog(parent),
    ui(new Ui::siirto)
{
    ui->setupUi(this);
    ui->label_siirto_summa->setHidden(true);
    ui->label_3->setHidden(true);
    ui->label_tilinumero->setText("FI");

    cardNumber=pCardNumber;
    pRestApi = new RestApi_dll(this);

    connect(pRestApi, SIGNAL(sendAccountNumberDoneToExe()),
            this, SLOT(getAccountNumberFromRestApiSlot()));

    pRestApi->getAccountId(cardNumber);

}


siirto::~siirto()
{
    delete ui;
    delete pRestApi;
    pRestApi = nullptr;
    delete pTimer;
    pTimer = nullptr;
}

void siirto::on_pushButton_suljeSiirto_clicked()
{
    this->close();
}


void siirto::getAccountNumberFromRestApiSlot()
{
    tilinro = pRestApi->returnAccountNumber();
    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &siirto::receiveTimeout);
    pTimer->start(10000);
}

void siirto::on_pushButton_maksa_clicked()
{
    pTimer->start();
    connect(pRestApi, SIGNAL(accountNotFound()),
            this, SLOT(receiveAccountNotFound()));
    connect(pRestApi, SIGNAL(accountFound(QString)),
            this, SLOT(receiveAccountFound(QString)));
    double summa = label_summa.toDouble();
    tilinro = pRestApi->returnAccountNumber();
    pRestApi->siirto(tilinumero, tilinro, summa);

}

void siirto::on_pushButton_1_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "1";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "1";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_2_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "2";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "2";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_3_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "3";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "3";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_4_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "4";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "4";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_5_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "5";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "5";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_6_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "6";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "6";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_7_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "7";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "7";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_8_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "8";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "8";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_9_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "9";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "9";
        ui->label_siirto_summa->setText(label_summa);
    }
}

void siirto::on_pushButton_0_clicked()
{
    pTimer->start();
    if(ui->label_tilinumero->isEnabled())
    {
        tilinumero = tilinumero + "0";
        ui->label_tilinumero->setText(tilinumero);
    }
    else
    {
        label_summa = label_summa + "0";
        ui->label_siirto_summa->setText(label_summa);
    }

}

void siirto::on_pushButton_enter_clicked()
{
    pTimer->start();
    ui->label_siirto_summa->setHidden(false);
    ui->label_3->setHidden(false);
    ui->label_tilinumero->setEnabled(false);
}

void siirto::on_pushButton_backSpace_clicked()
{
    pTimer->start();
    ui->label_siirto_summa->setHidden(true);
    ui->label_3->setHidden(true);
    ui->label_tilinumero->setEnabled(true);
    ui->label_tilinumero->clear();
    ui->label_siirto_summa->clear();
    label_summa = "";
    tilinumero = "FI";
    ui->label_tilinumero->setText("FI");
}

void siirto::receiveAccountFound(QString response)
{
    if (response=="\"Rahaa siirretty\"")
    {
        ui->label_tilinumero->setText("Siirto onnistui");
    }
    else if(response=="\"ei tarpeeksi rahaa\"")
    {
        ui->label_tilinumero->setText("Siirto ei onnistu");
    }
}

void siirto::receiveTimeout()
{
    this->close();
}

void siirto::receiveAccountNotFound()
{
    ui->label_tilinumero->setText("Tarkista tilinumero");
}

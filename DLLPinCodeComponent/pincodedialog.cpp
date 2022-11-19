#include "pincodedialog.h"
#include "ui_pincodedialog.h"

PinCodeDialog::PinCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinCodeDialog)
{
    ui->setupUi(this);
//    showFullScreen();

    pTimer = new QTimer;
    connect(pTimer, &QTimer::timeout, this, &PinCodeDialog::receiveTimerSignal);
    pTimer->start(10000);
}

PinCodeDialog::~PinCodeDialog()
{
    delete ui;
    delete pTimer;
    pTimer = nullptr;
}

void PinCodeDialog::on_pushButton_1_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "1";
    ui->label_code->setText(valuePinCode);
}
void PinCodeDialog::on_pushButton_2_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "2";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_3_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "3";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_4_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "4";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_5_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "5";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_6_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "6";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_7_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "7";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_8_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "8";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_9_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "9";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::on_pushButton_0_clicked()
{
    pTimer->start();
    valuePinCode = valuePinCode + "0";
    ui->label_code->setText(valuePinCode);
}

void PinCodeDialog::receiveTimerSignal()
{
    this->close();
}

QString PinCodeDialog::returnPincode()
{
   return valuePinCode;
}

void PinCodeDialog::on_pushButton_ok_clicked()
{
    this->close();
}

void PinCodeDialog::on_pushButton_back_clicked()
{
    pTimer->start();
    if(ui->label_code->text()!=""){
       valuePinCode = ui->label_code->text().chopped(1);
       ui->label_code->setText(valuePinCode);
    }

}



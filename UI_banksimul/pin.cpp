#include "pin.h"
#include "ui_pin.h"

pin::pin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pin)
{
    ui->setupUi(this);
}

pin::~pin()
{
    delete ui;
}

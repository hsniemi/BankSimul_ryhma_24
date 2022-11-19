#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_saldo_clicked()
{
    psaldo = new saldo(this);
    psaldo -> setWindowTitle("saldo");
    psaldo ->show();
    psaldo->exec();

}

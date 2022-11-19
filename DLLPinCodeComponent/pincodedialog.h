#ifndef PINCODEDIALOG_H
#define PINCODEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QObject>
#include <QTimer>

namespace Ui {
class PinCodeDialog;
}

class PinCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PinCodeDialog(QWidget *parent = nullptr);
    ~PinCodeDialog();
    QString returnPincode();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();
    void receiveTimerSignal();

private:
    Ui::PinCodeDialog *ui;
    QString valuePinCode;
    QTimer *pTimer;
};

#endif // PINCODEDIALOG_H

#ifndef ENGINE_H
#define ENGINE_H
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QList>
#include <QObject>

class engine:public QObject
{
    Q_OBJECT
public:
    engine(QObject *parent = nullptr);
    ~engine();
    void openSerialPort();
//    void closeSerialPort();

    QString returnCardNumber();

signals:
    void readySignal();

private slots:
    void readSerialPort();

private:
    QSerialPort *pQSerialPort;
    QString cardNumber;
};

#endif // ENGINE_H

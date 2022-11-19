#include "engine.h"

engine::engine(QObject *parent):QObject(parent)
{

}

void engine::checkCardNumberAndPin(QString cardNumber, QString pinCode)
{
    qDebug()<<"Engine: checkCardAndPin";
    QString id = cardNumber;
    QString pinkoodi = pinCode;
    QJsonObject json_obj;
    json_obj.insert("id", id);
    json_obj.insert("pinkoodi", pinkoodi);
    QString site_url = "http://localhost:3000/kirjautuminen";
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pQNetworkAccessManager = new QNetworkAccessManager(this);

    connect(pQNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(checkCardNumberAndPinSlot(QNetworkReply*)));
    pQNetworkReply = pQNetworkAccessManager->post
            (request,QJsonDocument(json_obj).toJson());
}

void engine::checkCardNumberAndPinSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"checkCardAndPinSlot"<<response_data;
    pQNetworkAccessManager->deleteLater();
    reply->deleteLater();
    pQNetworkReply->deleteLater();
    emit responseDone();
}

QByteArray engine::returnResponse()
{
    qDebug()<<"Engine returnResponse";
    return response_data;
}

void engine::getCustomerInfo(QString cardNumber)
{
    qDebug()<<"Engine: getCustomerInfo";
    QJsonObject json_obj;
    json_obj.insert("korttiID", cardNumber);
    QString site_url = "http://localhost:3000/kortti/asiakasTiedot";
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pCustomerManager = new QNetworkAccessManager(this);

    connect(pCustomerManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(customerSlot(QNetworkReply*)));
    pCustomerReply = pCustomerManager->post
            (request,QJsonDocument(json_obj).toJson());
}

void engine::customerSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"customerSlot: "<<response<<Qt::endl;

    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonArray json_array = json_doc.array();
    QString asiakas;
    QString asiakas_nimi;
    foreach (const QJsonValue &value, json_array)
    {
    QJsonObject json_obj = value.toObject();
    asiakas+=json_obj["enimi"].toString()+" "+json_obj["snimi"].toString()+", "+json_obj["puhelinnumero"].toString()+", "+json_obj["osoite"].toString();
    asiakas_nimi+=json_obj["enimi"].toString()+" "+json_obj["snimi"].toString();
    }
    pCustomerManager->deleteLater();
    reply->deleteLater();
    pCustomerReply->deleteLater();
    emit sendCustomerInfo(asiakas);
    emit sendCustomerName(asiakas_nimi);
}

void engine::getAccountID(QString cardID)
{
    qDebug() << "In: engine::getAccountId()";
    QString site_url="http://localhost:3000/kortti/tilinumero/"+cardID;
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pAccountIdManager = new QNetworkAccessManager(this);

    connect(pAccountIdManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(accountIdSlot(QNetworkReply*)));

    pAccountIdReply = pAccountIdManager->get(request);
}

void engine::accountIdSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"tilinumero: "<<response<<Qt::endl;
    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonObject json_obj = json_doc.object();
    tilinumero=json_obj["tilinumero"].toString();
    pAccountIdManager->deleteLater();
    reply->deleteLater();
    pAccountIdReply->deleteLater();
    emit AccountNumberDone();
}

QString engine::returnAccountNumber()
{
    return tilinumero;
}

void engine::getSaldo(QString tilinumero)
{
    qDebug() << "In: engine::getSaldo()";
    QString site_url="http://localhost:3000/tili/"+tilinumero;
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pSaldoManager = new QNetworkAccessManager(this);

    connect(pSaldoManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getSaldoSlot(QNetworkReply*)));

    pSaldoReply = pSaldoManager->get(request);
}

void engine::getSaldoSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"saldo: "<<response<<Qt::endl;
    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonObject json_obj = json_doc.object();
    double saldo = json_obj["saldo"].toDouble();
    pSaldoManager->deleteLater();
    reply->deleteLater();
    pSaldoReply->deleteLater();
    emit sendSaldoToInterface(saldo);
}

void engine::getTransactions5(QString tilinumero)
{
    qDebug() << "In: engine::getTransactions5()";
    QString site_url="http://localhost:3000/tilitapahtumat/getFive/"+tilinumero;
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pGetFiveManager = new QNetworkAccessManager(this);

    connect(pGetFiveManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getFiveSlot(QNetworkReply*)));

    pGetFiveReply = pGetFiveManager->get(request);
}

void engine::getFiveSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumat5;
    foreach (const QJsonValue &value, json_array)
    {
    QJsonObject json_obj = value.toObject();
    tilitapahtumat5 += json_obj["pvm"].toString()+", "+json_obj["tapahtuma_tyyppi"].toString()+", "+QString::number(json_obj["summa"].toDouble())+" euroa"+"\r\n";
    }
    qDebug()<<"Tilitapahtumat5: "<<tilitapahtumat5;
    pGetFiveManager->deleteLater();
    reply->deleteLater();
    pGetFiveReply->deleteLater();
    emit sendTransactions5(tilitapahtumat5);
}

void engine::getMoney(QString tilinumero, int summa)
{
    qDebug()<<"summa: "<<summa;
    QJsonObject json_obj;
    json_obj.insert("tili",tilinumero);
    json_obj.insert("summa", -summa);
    QString site_url = "http://localhost:3000/tilitapahtumat/RahanNosto/";
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pMoneyManager = new QNetworkAccessManager(this);

    connect(pMoneyManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getMoneySlot(QNetworkReply*)));

    pMoneyReply = pMoneyManager->post
            (request,QJsonDocument(json_obj).toJson());
}

void engine::getMoneySlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"Money: "<<response<<Qt::endl;
    emit sendMoneySignal(response);

    pMoneyManager->deleteLater();
    reply->deleteLater();
    pMoneyReply->deleteLater();
}

void engine::getTilitapahtumat(QString tilinumero, int offset)
{
    qDebug() << "getTilitapahtumat: "<<tilinumero<<offset;
    QJsonObject json_obj;
    json_obj.insert("tilino", tilinumero);
    json_obj.insert("offset_row_count", offset);
    QString site_url="http://localhost:3000/tilitapahtumat/getTen";
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pTilitapahtumatManager = new QNetworkAccessManager(this);

    connect(pTilitapahtumatManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getTilitapahtumatSlot(QNetworkReply*)));

    pTilitapahtumatReply = pTilitapahtumatManager->post
            (request,QJsonDocument(json_obj).toJson());
}

void engine::getTilitapahtumatSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumat;
    foreach (const QJsonValue &value, json_array)
    {
    QJsonObject json_obj = value.toObject();
    tilitapahtumat += json_obj["pvm"].toString()+", "+json_obj["enimi"].toString()+" "+json_obj["snimi"].toString()+", "+json_obj["tapahtuma_tyyppi"].toString()+", "+QString::number(json_obj["summa"].toDouble())+" euroa"+"\r\n";
    }
    qDebug()<<"getTilitapahtumat: "<<tilitapahtumat;
    pTilitapahtumatManager->deleteLater();
    reply->deleteLater();
    pTilitapahtumatReply->deleteLater();
    emit sendTilitapahtumatToInterface(tilitapahtumat);
}
void engine::siirto(QString saajan_tilinro, QString maksajan_tilinro, double summa)
{
    QJsonObject json_obj;
    json_obj.insert("tili_saaja", saajan_tilinro);
    json_obj.insert("tili_maksaja", maksajan_tilinro);
    json_obj.insert("summa", summa);
    QString site_url = "http://localhost:3000/tilitapahtumat/rahanSiirto";
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pSiirtoManager = new QNetworkAccessManager(this);

    connect(pSiirtoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(siirtoSlot(QNetworkReply*)));
    pSiirtoReply = pSiirtoManager->post
            (request,QJsonDocument(json_obj).toJson());
}

void engine::siirtoSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"siirtoSlot:"<<response;
    if(response=="\"Rahaa siirretty\"")
    {
        emit accountFound(response);
    }
    else if(response=="\"ei tarpeeksi rahaa\"")
    {
        emit accountFound(response);
    }
    pSiirtoManager->deleteLater();
    reply->deleteLater();
    pSiirtoReply->deleteLater();
}

void engine::deleteCard(QString cardNumber)
{
    qDebug() << "In: engine::deleteCard()";
    QString site_url="http://localhost:3000/kortti/"+cardNumber;
    QString credentials="";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pDeleteManager = new QNetworkAccessManager(this);

    connect(pDeleteManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(deleteSlot(QNetworkReply*)));

    pDeleteReply = pDeleteManager->deleteResource(request);
}

void engine::deleteSlot(QNetworkReply *reply)
{
    QByteArray response=reply->readAll();
    qDebug()<<"deleteSlot: "<<response<<Qt::endl;

    pDeleteManager->deleteLater();
    reply->deleteLater();
    pDeleteReply->deleteLater();
    emit deleteCardSignal();
}






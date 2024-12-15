#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::connect_Server(){

    soket = new QTcpSocket(this);

    connect(soket, &QTcpSocket::connected, this,  &Client::on_Soket_Connected);

    connect(soket, &QTcpSocket::readyRead, this, &Client::read_Socket);

    connect(soket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    soket->connectToHost(QHostAddress::LocalHost, 1883);

}

void Client::add_New_Task(int num_Task){

    qDebug() << "составляем новое задание! " + QString::number(num_Task);

    QJsonObject jsonObject;

    jsonObject.insert("num_Task", num_Task);


    QJsonDocument doc(jsonObject);

    //QString formatted = doc.toJson(QJsonDocument::Indented);


   // qWarning().noquote() << formatted;

    QByteArray data = doc.toJson();


    soket->waitForBytesWritten();

    soket->write(data);

}


void Client::read_Socket()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QJsonDocument doc = QJsonDocument::fromJson(clientSocket->readAll());


    QString formatted = doc.toJson(QJsonDocument::Indented);

    qDebug() << "Пришло новое сообщение! App 1";

    qWarning().noquote() << formatted;



    QJsonObject jsonObject = doc.object();

    qDebug() << "Обновим прогресс у задания номер " + QString::number(jsonObject.value("num_Task").toInt()) + " Прогресс = " + QString::number(jsonObject.value("progress").toDouble());

    emit new_Task_Progress_Signal(jsonObject.value("num_Task").toInt(),
                                  jsonObject.value("progress").toDouble());


}

void Client::on_Soket_Connected(){

    emit new_Connect_Signal();

}

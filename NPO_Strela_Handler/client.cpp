#include "client.h"

Client::Client()
{
    soket = new QTcpSocket(this);

    connect(soket, &QTcpSocket::connected, this,  &Client::on_Soket_Connected);

    connect(soket, &QTcpSocket::readyRead, this, &Client::read_Socket);

    connect(soket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    soket->connectToHost(QHostAddress::LocalHost, 1883);

    connect(&m_timer, &QTimer::timeout, this, &Client::add_Progress);

}

// Отправляем прогрессс выполнения задания на сервер
void Client::add_Progress(){

    if(step < coun_Seconds){

        float progress_Percent = (float) ((step + 1) * 100) / coun_Seconds;


        QJsonObject jsonObject;

        jsonObject.insert("num_Task", this->num_Task);

        jsonObject.insert("progress", progress_Percent);


        QJsonDocument doc(jsonObject);

        QByteArray data = doc.toJson();


        soket->waitForBytesWritten();

        soket->write(data);


        step++;

    }
    else{

        step = 0;

        m_timer.stop();
    }

}

// Принимаем задание от сервера
void Client::read_Socket(){

    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QJsonDocument doc = QJsonDocument::fromJson(clientSocket->readAll());


    QJsonObject jsonObject = doc.object();

    this->num_Task = jsonObject.value("num_Task").toInt();

    this->coun_Seconds = jsonObject.value("seconds").toInt();

    m_timer.start(1000);

}


// Когда мы подключились к серверу сообщим ему об этом
void Client::on_Soket_Connected(){

    QJsonObject jsonObject;

    jsonObject.insert("connect", true);


    QJsonDocument doc(jsonObject);

    QByteArray data = doc.toJson();


    soket->waitForBytesWritten();

    soket->write(data);

}

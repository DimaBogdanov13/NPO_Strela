#include "server.h"

Server::Server()
{
    if(!this->listen(QHostAddress::Any, 1883)) {

        qDebug() << "Ошибка при запуске сервера " + this->errorString();

    }
    else {

        qDebug() << "Сервер запущен!";
    }

}

void Server::incomingConnection(qintptr soketDescriptor){

    QTcpSocket *soket = new QTcpSocket;

    soket->setSocketDescriptor(soketDescriptor);

    if(!connect_App){

        this->soket_Interface = soket;

        connect(soket, &QTcpSocket::readyRead, this, &Server::read_Interface_Socket);

    }
    else{

        connect(soket, &QTcpSocket::readyRead, this, &Server::read_Handler_Socket);

        sokets_Handler_List.append(soket_Handler_Values(soket, true));

    }

    qDebug() << "client connected soketDescriptor = " + QVariant(soketDescriptor).toString();
}

void Server::read_Interface_Socket() {

    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QJsonDocument doc = QJsonDocument::fromJson(clientSocket->readAll());



    QString formatted = doc.toJson(QJsonDocument::Indented);

    qDebug() << "Пришло новое задание!";

    qWarning().noquote() << formatted;


    QJsonObject jsonObject = doc.object();

    this->num_Task = jsonObject.value("num_Task").toInt();

    this->connect_App = true;


    QProcess process;

    // ВОТ ЗДЕСЬ НЕОБХОДИМОМ ОБНОВИТЬ КОМАНДУ SH ПОД ОПЕРАЦИОННУЮ СИСТЕМУ !
    process.startDetached("/bin/sh", QStringList()<< "/Users/dimabogdanov/QtProjects/NPO_Strela_Server/start_Handler.sh");


}

void Server::read_Handler_Socket(){

    qDebug() << "Пришло сообщение от обработчика!";


    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QJsonDocument doc = QJsonDocument::fromJson(clientSocket->readAll());


    QString formatted = doc.toJson(QJsonDocument::Indented);

    qWarning().noquote() << formatted;


    QJsonObject jsonObject = doc.object();


    // Это сообщение может прийти только когда сокет обработчика готов к работе!
    if(jsonObject.value("connect").toBool()){

        add_New_Task_To_Handler(this->num_Task);

    }
    else{

        QByteArray data = doc.toJson();



        soket_Interface->waitForBytesWritten();

        soket_Interface->write(data);

        QThread::msleep(30);


    }


}


void Server::add_New_Task_To_Handler(int num_Task){

    QString file_Path = ":/tasks/task_" + QString::number(num_Task + 1) + ".txt";

    QFile file(file_Path);


    if(file.open(QIODevice::ReadOnly)) {

        QString seconds = QTextStream(&file).readLine();

        qDebug() << "seconds = " + seconds;


        QJsonObject jsonObject;

        jsonObject.insert("num_Task", num_Task);

        jsonObject.insert("seconds", seconds.toInt());


        QJsonDocument doc(jsonObject);

        QString formatted = doc.toJson(QJsonDocument::Indented);


        qWarning().noquote() << formatted;

        QByteArray data = doc.toJson();



        sokets_Handler_List.last().num_Task = num_Task;

        sokets_Handler_List.last().soket->write(data);

    }

}



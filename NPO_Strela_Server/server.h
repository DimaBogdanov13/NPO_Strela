#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QProcess>

#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

#include <QJsonObject>
#include <QJsonDocument>

class soket_Handler_Values{

public:

    soket_Handler_Values(QTcpSocket *soket, bool is_Active){

        this->soket = soket;

        this->is_Active = is_Active;

    }

    QTcpSocket *soket;

    int num_Task = 0;

    bool is_Active;
};

class Server : public QTcpServer
{
public:
    Server();

    QTcpSocket *soket_Interface;

public slots:

    void incomingConnection(qintptr soketDescriptor);

    void read_Interface_Socket();

    void read_Handler_Socket();

private:

    QList<soket_Handler_Values> sokets_Handler_List;

    bool connect_App;


    int num_Task = 0;

    void add_New_Task_To_Handler(int num_Task);


};

#endif // SERVER_H

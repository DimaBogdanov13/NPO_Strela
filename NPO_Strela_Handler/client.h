#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#include <QTcpSocket>
#include <QHostAddress>

#include <QJsonObject>
#include <QJsonDocument>

class Client : public QObject
{
public:
    Client();

private:

    QTcpSocket *soket;

    QTimer m_timer;

    int num_Task, coun_Seconds = 0, step = 0;


    void read_Socket();

    void on_Soket_Connected();

    void add_Progress();

};

#endif // CLIENT_H

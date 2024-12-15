#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <QTcpSocket>
#include <QHostAddress>

#include <QJsonObject>
#include <QJsonDocument>

class Client : public QObject
{
    Q_OBJECT

public:

    explicit Client(QObject *parent = nullptr);

    void connect_Server();

    void add_New_Task(int num_Task);

private:

    QTcpSocket *soket;

    void read_Socket();

    void on_Soket_Connected();

signals:

    void new_Connect_Signal();

    void new_Task_Progress_Signal(const int num_Task, const float progress);

};

#endif // CLIENT_H

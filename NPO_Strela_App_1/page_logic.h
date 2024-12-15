#ifndef PAGE_LOGIC_H
#define PAGE_LOGIC_H

#include <QObject>
#include <QDebug>

#include "client.h"
#include "models/my_model.h"

class Page_Logic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(My_Model* progress_Model MEMBER progress_Model NOTIFY my_Model_Changed)

public:

    explicit Page_Logic(QObject *parent = nullptr);

public slots:

    void connect_Server();

    void add_All_Tasks();

    void add_New_Task(int num_Task);

private:

    My_Model *progress_Model = new My_Model;

    Client *client = new Client;

    void new_Task_Progress(int num_Task, float progress);

signals:

    void new_Connect_Signal();

    void my_Model_Changed(const My_Model *value);
};

#endif // PAGE_LOGIC_H

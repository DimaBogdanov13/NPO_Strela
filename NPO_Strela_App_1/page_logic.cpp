#include "page_logic.h"

Page_Logic::Page_Logic(QObject *parent) : QObject(parent)
{

   connect(client, &Client::new_Task_Progress_Signal, this,  &Page_Logic::new_Task_Progress);

   connect(client, &Client::new_Connect_Signal, this,  &Page_Logic::new_Connect_Signal);

}

void Page_Logic::connect_Server(){

    client->connect_Server();

}

void Page_Logic::add_All_Tasks(){

    add_New_Task(0);

    add_New_Task(1);

    add_New_Task(2);

}



void Page_Logic::add_New_Task(int num_Task){

    progress_Model->add_Item({num_Task + 1, 0});

    client->add_New_Task(num_Task);

    QThread::msleep(100);
}

void Page_Logic::new_Task_Progress(int num_Task, float progress){

    if(num_Task < progress_Model->rowCount()){

        progress_Model->update_Progress(num_Task, progress);

    }
}

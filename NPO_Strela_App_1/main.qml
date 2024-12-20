import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Page_Logic 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Приложение интерфейса")

    Page_Logic{
        id: page_Logic

        onNew_Connect_Signal: {

            connect_Label.text = "Подключены к серверу!"

            content_Column.enabled = true
        }
    }

    Column{
        id: content_Column
        width: parent.width
        height: parent.height
        enabled: false

        Row{
            width: parent.width
            height: 40
            spacing: 16

            Button{
               id: b1
               text: "Начать задание 1"

               onClicked: {

                   page_Logic.add_New_Task(0)

                   b1.enabled = false

                   b2.enabled = true

                   b4.enabled = false

               }
            }

            Button{
               id: b2
               text: "Начать задание 2"
               enabled: false

               onClicked: {

                   page_Logic.add_New_Task(1)

                   b2.enabled = false

                   b3.enabled = true

                   b4.enabled = false

               }
            }

            Button{
               id: b3
               text: "Начать задание 3"
               enabled: false

               onClicked: {

                   page_Logic.add_New_Task(2)

                   b3.enabled = false

                   b4.enabled = false

               }
            }

            Button{
                id: b4
               text: "Выполнить все задния"

               onClicked: {

                   page_Logic.add_All_Tasks()

               }
            }

        }


        ListView{
            width: parent.width
            height: parent.height
            model: page_Logic.progress_Model

            delegate: Text {
                    text: "Задание " + name + " прогресс = " + progress + " %"
                }
        }
    }


    Row{
        width: parent.width
        height: 40
        anchors.bottom: parent.bottom
        spacing: 16

        Button{
           text: "Подключиться к серверу"

           onClicked: {

               page_Logic.connect_Server()

               enabled = false
           }
        }

        Label{
            id: connect_Label
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "Нет подключения к серверу"
        }
    }





}

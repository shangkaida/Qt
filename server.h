
#ifndef SERVER_H
#define SERVER_H


#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>
#include <QTimer>
#include "mythread.h"
/*typedef struct Node{
    QByteArray data;
    struct Node *Next;
}Node;*/

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void listen_connect(unsigned short port);
private:
    void saveData(QTcpSocket* , Node* p);
    void sendData2ui();//将服务器的数据发送到ui界面
    void delet_thread();//销毁为已经断开的客户端开启的线程
    //int dug_count = 0;//调试计数
    QTcpServer* m_s;
    QTimer* timer_send_ui;
    QTimer* timer_delete;
//public:
    QList<QTcpSocket*> ls_tcp;//存放不同客户端
    QList<MyThread*> ls_thread;//存不同客户端的线程
    QList<Node*> ls_data_tree;//存放不同客户端那发来的数据链表首地址
signals:
    void data_send(QByteArray data, int num);
    //void data_send(QByteArray data);
};

#endif // SERVER_H

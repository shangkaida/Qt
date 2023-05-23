
#include "mythread.h"
#include <QTcpSocket>
#include <QList>

//typedef struct Node *mList;

MyThread::MyThread(QTcpSocket* tcp, QObject *parent)
    : QThread{parent}
{
    m_tcp = tcp;
    P = new(Node);
    if(NULL == P)
    {
        printf("new error");
    }
    else{
        P->Next = NULL;
        //这里进不去  不知道为啥
       // emit getData(m_tcp, P);//去发信号让服务器的数据链表把这条的首地址加上
    }
}

void MyThread::run()
{
    emit getData(m_tcp, P);//去发信号让服务器的数据链表把这条链表的首地址加上
        connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        QByteArray data;       
        data.resize(5);
            data = m_tcp->readAll();
        QByteArray a = data.toHex();
        P->data = data;
            P->Next = new(Node);
 // emit getData(m_tcp, P);
        P = P->Next;
        P->Next = NULL;
            //m_tcp->close();//不主动断开，一直在等消息
            //m_tcp->deleteLater();
        });
}


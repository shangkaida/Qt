
#include "server.h"
#include "mythread.h"
#include <QTcpServer>
//#include <QTimer>
Server::Server(QObject *parent)
    : QObject{parent}
{
    m_s = new QTcpServer;
    timer_send_ui = new QTimer(this);
    timer_delete = new QTimer(this);//这个没用上，有问题待解决，执行delet_thread()时会异常退出
}

void Server::listen_connect(unsigned short port)
{
      //  unsigned short port = ui->port->text().toUShort();
        m_s->listen(QHostAddress::Any, port);
        timer_send_ui->start(100);//间隔100ms向uig更新一次
            connect(timer_send_ui, &QTimer::timeout, this, &Server::sendData2ui);
        //timer_delete->start(5000);//间隔5秒检测一下是不是有断开的连接
        //   connect(timer_delete, &QTimer::timeout, this, &Server::delet_thread);

        //监测一旦有客户端即触发
        //int c = 10;
        //不要循环！！！！！！！！！人家本来就是在等待
       // while(c--)//为了做到接收多个客户端，改成1错了容易崩，而且本来客户端接入应该有个限制(这样想不对，就不用循环，新的客户端来自动会触发)
        {
            connect(m_s, &QTcpServer::newConnection, this, [=](){
              //  dug_count++;
                QTcpSocket* m_tcp = m_s->nextPendingConnection();
                ls_tcp.push_back(m_tcp);//
               // QByteArray empty_data = 0;
                Node* empty_ls_data;
                //empty_ls_data->Next = NULL;
                ls_data_tree.push_back(empty_ls_data);//把存不同客户端数据链表首地址的数据链表也延长一个
                MyThread* subThread = new MyThread(m_tcp);
                ls_thread.push_back(subThread);
                subThread->start();
                //处理子线程发来的数据
                connect(subThread, &MyThread::getData, this, &saveData);
               // connect(subThread, &MyThread::getData, this, &data_send);
            });
        }
}

void Server::saveData(QTcpSocket* cline, Node* p)
{
       /* if(p->Next != NULL)
        {
        QByteArray data = p->data;
        emit data_send(data, 1);        Node* p1 = p;
        }*/

        QList<QTcpSocket*>::iterator it = ls_tcp.begin();
        int num = ls_tcp.size();//接入客户端数量
        for(int i = 0; i < num; i++)
        {
            //it += i;//瓜皮做法，人家到了2可就是加2了
           // QList<QList<QByteArray>>::iterator ls_it = ls_data_tree.begin();
            if(*it == cline)
            {
                ls_data_tree[i] = p;
            }
            else if(i == num-1)
               printf("数据没有匹配上的套接字");
            it++;
        }

}

void Server::sendData2ui()
{
        int num = ls_data_tree.size();
        for(int i = 0; i < num; i++)
        {
            Node* p = ls_data_tree[i];
            //不为空就把数据发到ui去显示
            if(p->Next != NULL){
                emit data_send(p->data, i);
                Node* p1 = p;
                p = p->Next;
                ls_data_tree[i] = p;
                delete p1;
            }
        }
}

void Server::delet_thread()
{
        int num = ls_thread.size();
        for(int i = 0; i < num; i++)
        {
            QTcpSocket* m_tcp = ls_tcp[i];
            MyThread* sub = ls_thread[i];
            connect(m_tcp,&QTcpSocket::disconnected, this, [=](){
                ls_tcp.removeAt(i);
                ls_data_tree.removeAt(i);
                ls_thread.remove(i);
                //m_tcp->close();
                //m_tcp->deleteLater();
                //sub->deleteLater();
            });

        }
}



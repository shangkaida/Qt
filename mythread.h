
#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include <QTcpSocket>
typedef struct Node{
    QByteArray data;
    struct Node *Next = NULL;
}Node;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QTcpSocket* tcp, QObject *parent = nullptr);
protected:
    void run() override;
protected:
    QTcpSocket* m_tcp;
    Node* P;
signals:
    void getData(QTcpSocket* cline, Node* p);

};

#endif // MYTHREAD_H


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QList>
#include <QString>
#include "server.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化界面
    ui->port->setText("8888");//端口号
    //准备数据表格模型
    data_model = new QStandardItemModel(this);
    data_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("编号")));
    data_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("角度1")));
    data_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("角度2")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->table->setModel(data_model);
    //设置每列的宽度
    ui->table->setColumnWidth(0,50);
    ui->table->setColumnWidth(1,100);
    ui->table->setColumnWidth(2,100);

    ui->table->verticalHeader()->hide();//隐藏行头的编号
//数据接收处理_________________________________________________________________________-
    //创建服务器子线程
    QThread* sub_server = new QThread;
    Server* worker_server = new Server;
    worker_server->moveToThread(sub_server);

    //给服务器子线程传递信号
    connect(this, &MainWindow::listen_stare, worker_server, &Server::listen_connect);
    //接收服务器的信号
    connect(worker_server, &Server::data_send, this, &MainWindow::showData);
    sub_server->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showData(QByteArray data, int num)
{

    QByteArray a = data.toHex();
    //num = 1;
    data_model->setItem(num,0, new QStandardItem(QString::number(num)));
    data_model->item(num,0)->setTextAlignment(Qt::AlignCenter);//居中
    data_model->setItem(num,1, new QStandardItem(data));
    data_model->item(num,1)->setTextAlignment(Qt::AlignCenter);
    data_model->setItem(num,2, new QStandardItem(a));
    data_model->item(num,2)->setTextAlignment(Qt::AlignCenter);
    //QLine* pic = new QLine;
    //QLabel* pic = new QLabel;
    //pic->setLine(10,10,20,20);
    //ui->message->append(QString::number(num) + ": " + data);
}

void MainWindow::on_listen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    ui->listen->setDisabled(true);
    emit listen_stare(port);//给server线程的开始信号
}


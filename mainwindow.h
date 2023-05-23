
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void listen_stare(unsigned short);

private slots:
    void on_listen_clicked();
    void showData(QByteArray data, int num);//显示子线程发来的数据
private:
    Ui::MainWindow *ui;
    QStandardItemModel *data_model;
};

#endif // MAINWINDOW_H

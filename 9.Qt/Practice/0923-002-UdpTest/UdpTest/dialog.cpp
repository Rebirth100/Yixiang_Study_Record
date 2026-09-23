#include "dialog.h"
#include "ui_dialog.h"
#include <QUdpSocket>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    socket_=new QUdpSocket;
    connect(socket_,&QUdpSocket::errorOccurred,
            [this](QAbstractSocket::SocketError err)
            {
                qDebug()<<"error="<<err;
                QMessageBox::question(this,"title","errot");
            });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_send_clicked()
{
    QByteArray msg="我是客户端";
    socket_->writeDatagram(msg,QHostAddress("192.168.1.78"),8080);
}


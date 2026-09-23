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
    connect(socket_,&QUdpSocket::readyRead,
            [this]
            {
                char buf[128]={0};
                QHostAddress addr;
                quint16 port=0;
                socket_->readDatagram(buf,128,&addr,&port);
                qDebug()<<"address="<<addr<<",port="<<port
                            <<",msg="<<buf;
                //socket_->writeDatagram(buf,size,addr,port);
            });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_start_clicked()
{
    if(socket_->bind(QHostAddress("192.168.1.78"),8080))
    {
        QMessageBox::information(this,"title","开启成功！");
    }
    else {
        QMessageBox::question(this,"title","开启失败！");
    }
}


#include "dialog.h"
#include "ui_dialog.h"
#include <QHttpServer>
#include <QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    tcp_server_ =new QTcpServer;
    http_server_=new QHttpServer;
    //QHttpServer* http_server_=new QHttpServer;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_open_clicked()
{
    if(tcp_server_==nullptr)
    {
        QMessageBox::question(this,"标题","TCP server空");
        return;
    }

    if (http_server_ == nullptr)
    {
        QMessageBox::question(this, "标题", "Http server空！");
        return;
    }

    if(!tcp_server_->listen(QHostAddress::Any,8000))
    {
        QMessageBox::question(this,"标题","TCP server开启失败");
        return;
    }
    if(http_server_->bind(tcp_server_))
    {
        QMessageBox::information(this,"标题","开启http服务成功");
    }
    else
    {
        QMessageBox::question(this,"标题","开启http服务失败");
        return;
    }

    http_server_->route("/test",
                        [](const QHttpServerRequest &request,
                           QHttpServerResponder &responder)
                        {
                            qDebug()<<"msg="<<request.body().toStdString().c_str();
                            QByteArray data;
                            static int count=0;
                            data = "我是服务端";
                            data.append(QString::number(count++).toStdString().c_str());
                            QHttpHeaders headers;
                            responder.write(data,headers);
                        });

}


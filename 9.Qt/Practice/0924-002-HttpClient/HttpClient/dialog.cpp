#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    access_=new QNetworkAccessManager;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_send_clicked()
{
    //QNetworkRequest request(QUrl("http://127.0.0.1:8000/test"));
    QNetworkRequest request(QUrl("http://baidu.com/"));
    QNetworkReply* reply=access_->get(request,"我是客户端");
    connect(reply,&QNetworkReply::readyRead,
            [reply]
            {
                QFile file("page.html");
                file.open(QFile::WriteOnly);
                file.write(reply->readAll());
                file.close();
                qDebug()<<"msg="<<reply->readAll().toStdString().c_str();
            });
}


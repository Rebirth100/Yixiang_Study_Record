#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QThread>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    qDebug()<<"ideal thread count="<<QThread::idealThreadCount();
}

Dialog::~Dialog()
{
    delete ui;
}

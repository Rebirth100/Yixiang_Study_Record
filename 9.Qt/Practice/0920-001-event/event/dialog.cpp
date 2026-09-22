#include "dialog.h"
#include "ui_dialog.h"

#include <QTimer>
#include <QMouseEvent>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timer_=new QTimer;
    connect(timer_,&QTimer::timeout,
            []
            {
                static int count=0;
               qDebug()<<"Qtimer count="<<count++;
             });
    ui->lineEdit->installEventFilter(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::mousePressEvent(QMouseEvent* event)
{
    QRect lineEdit_rect=ui->lineEdit->geometry();
    //qDebug()<<"mousePressEvent";
}

void Dialog::mouseMoveEvent(QMouseEvent* event)
{
    //qDebug()<<"mouseMoveEvent";
}

void Dialog::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug()<<"mouseMoveEvent";
}

bool Dialog::eventFilter(QObject *watched,QEvent* event)
{
    qDebug()<<"eventFilter";

    return true;
}


void Dialog::on_pushButton_stop_timer_clicked()
{
    //lineEdit_time_id_=ui->lineEdit->startTimer(1000);
}

void Dialog::on_pushButton_stop_timer_2_clicked()
{
    //ui->lineEdit->killTimer(lineEdit_time_id_);
}




#include "dialog.h"
#include "ui_dialog.h"

#include <QTimer>
#include <QMouseEvent>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timer_ = new QTimer;
    connect(timer_, &QTimer::timeout,
            []
            {
                static int count = 0;
                qDebug() << "QTimer count=" << count++;
            });

    //installEventFilter(ui->lineEdit);
    ui->lineEdit->installEventFilter(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mousePressEvent(QMouseEvent* event)
{
    //qDebug() << "mousePressEvent";
    /*
    qDebug() << "pos=" << event->pos();
    qDebug() << "globalPos=" << event->globalPos();
    qDebug() << "localPos=" << event->localPos();
    qDebug() << "windowPos=" << event->windowPos();
    qDebug() << "screenPos=" << event->screenPos();*/

    QRect lineEdit_rect = ui->lineEdit->geometry();
    //qDebug() << "lineEdit rect=" << lineEdit_rect;
}

void Dialog::mouseMoveEvent(QMouseEvent* event)
{
    //qDebug() << "mouseMoveEvent";
}

void Dialog::mouseReleaseEvent(QMouseEvent* event)
{
    //qDebug() << "mouseReleaseEvent";
}

bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() << "eventFilter";

    return true;
}

void Dialog::on_pushButton_stop_timer_clicked()
{
    //lineEdit_timer_id_ = ui->lineEdit->startTimer(1000);
    //timer_->start(1000);
}

void Dialog::on_pushButton_stop_timer_2_clicked()
{
    //ui->lineEdit->killTimer(lineEdit_timer_id_);
    //timer_->stop();
}

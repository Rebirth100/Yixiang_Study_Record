#include "dialog.h"
#include "ui_dialog.h"

#include <QCursor>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //QPainter* painter = new QPainter(this);
    //painter->drawLine(100, 100, 500, 500);

    color_dialog_ = new QColorDialog(this);
    connect(color_dialog_, &QColorDialog::colorSelected,
            [this](const QColor& color)
            {
                pen_color_ = color;
            });

    //setCursor(QCursor(Qt::CrossCursor));
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::event(QEvent* event)
{
    //if (event->type() == QEvent::MouseMove)
    {
        //static int count = 0;
        //qDebug() << "event count=" << count++;
        //qDebug() << event->type();
    }

    return QDialog::event(event);
}

void Dialog::paintEvent(QPaintEvent* event)
{
    /*
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    QColor color;
    color.setRed(100);
    color.setGreen(200);
    color.setBlue(169);
    //pen.setColor(color);
    pen.setColor(pen_color_);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    //painter.drawLine(100, 100, 500, 500);
    //painter.drawLine(begin_pos_, end_pos_);

    painter.drawRect(QRect(begin_pos_, end_pos_));
    //painter.drawEllipse(QRect(begin_pos_, end_pos_));*/


    QRect rect{begin_pos_, end_pos_};
    QPainter painter(this);
    QColor color{53, 235, 255};
    QPen pen(color);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawRect(rect);

    QColor color_draw{0, 0, 0};
    QPen pen_draw(color_draw);
    pen_draw.setWidth(2);
    painter.setPen(pen_draw);
    painter.drawEllipse(rect);

    const int Size = 4;
    QRect rect_1{begin_pos_.x() - Size/2,
                 begin_pos_.y() - Size/2,
                 Size, Size};
    rect_1_check_ = {begin_pos_.x() - CSize/2,
                 begin_pos_.y() - CSize/2,
                 CSize, CSize};
    painter.drawRect(rect_1);

    QBrush brush(QColor{255, 255, 255});
    painter.fillRect(rect_1, brush);

    //qDebug() << "cursor pos=" << QCursor::pos();
    //qDebug() << "Dialog pos=" << pos();
    //qDebug() << "pos=" << QCursor::pos() - pos();
    //qDebug() << "childrenRect=" << childrenRect();

    int x = QCursor::pos().x() - pos().x();
    int y = QCursor::pos().y() - pos().y() - childrenRect().height();
    qDebug() << "x=" << x << ", y=" << y;

    if (rect_1_check_.contains(x, y))
    {
        setCursor(QCursor(Qt::CrossCursor));
    }
    else
    {
        setCursor(QCursor(Qt::ArrowCursor));
    }

    return QDialog::paintEvent(event);
}

void Dialog::mousePressEvent(QMouseEvent* event)
{
    //qDebug() << "pos=" << event->pos();
    begin_pos_ = event->pos();
    is_drawing_ = true;
}

void Dialog::mouseReleaseEvent(QMouseEvent* event)
{
    is_drawing_ = false;
}

void Dialog::mouseMoveEvent(QMouseEvent* event)
{
    end_pos_ = event->pos();

    /*
    if (is_drawing_ == false)
    {
        if (rect_1_check_.contains(end_pos_))
        {
            setCursor(QCursor(Qt::CrossCursor));
        }
        else
        {
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }*/

    update();

    static int count = 0;
    qDebug() << "mouseMoveEvent count=" << count++;
}

/*
void Dialog::moveEvent(QMoveEvent* event)
{
    static int count = 0;
    qDebug() << "moveEvent count=" << count++;
}*/

void Dialog::on_pushButton_color_clicked()
{
    color_dialog_->setModal(true);
    color_dialog_->show();
}

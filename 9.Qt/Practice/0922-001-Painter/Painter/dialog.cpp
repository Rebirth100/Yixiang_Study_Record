#include "dialog.h"
#include "ui_dialog.h"
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // QPainter* painter=new QPainter;
    // painter->drawLine(100,100,500,500);


    color_dialog_=new QColorDialog(this);
    connect(color_dialog_,&QColorDialog::colorSelected,
            [this](const QColor& color)
            {
                pen_color_=color;
            });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent* event)
{
    // QPainter painter(this);
    // QPen pen;
    // pen.setWidth(3);
    // QColor color;
    // color.setRed(100);
    // color.setGreen(200);
    // color.setBlue(169);
    //pen.setColor(color);
    // pen.setColor(pen_color_);
    // pen.setStyle(Qt::DashLine);
    // painter.setPen(pen);
    //painter.drawLine(100,100,500,500);
    //painter.drawLine(begin_pos_,end_pos_);
    //painter.drawRect(QRect(begin_pos_,end_pos_));
    //painter.drawEllipse(QRect(begin_pos_,end_pos_));


    QPainter painter(this);
    QRect rect = QRect(begin_pos_, end_pos_).normalized();
    QColor color{53,235,255};
    QPen pen(color);
    painter.setPen(pen);
    pen.setStyle(Qt::DotLine);
    painter.drawRect(rect);

    QColor color_draw{0,0,0};
    QPen pen_draw(color_draw);
    painter.setPen(pen_draw);
    painter.drawEllipse(rect);

    const int Size=10;
    QRect Rect_1{begin_pos_.x()-Size/2,
                 begin_pos_.y()-Size/2,
                 Size,Size};

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(rect.left()-Size/2,
                           rect.top()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.center().x()-Size/2,
                           rect.top()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.right()-Size/2,
                           rect.top()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.left()-Size/2,
                           rect.center().y()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.right()-Size/2,
                           rect.center().y()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.left()-Size/2,
                           rect.bottom()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.center().x()-Size/2,
                           rect.bottom()-Size/2,
                           Size, Size));
    painter.drawRect(QRect(rect.right()-Size/2,
                           rect.bottom()-Size/2,
                           Size, Size));

    return QDialog::paintEvent(event);
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"pos="<<event->pos();
    QRect rect = QRect(begin_pos_, end_pos_).normalized();
    if (rect.isValid() && rect.width() > 0 && rect.height() > 0)
    {
        const int Size = 10;
        QRect handles[8] = {
            QRect(rect.left()-Size/2,
                  rect.top()-Size/2,
                  Size, Size),
            QRect(rect.center().x()-Size/2,
                  rect.top()-Size/2,
                  Size, Size),
            QRect(rect.right()-Size/2,
                  rect.top()-Size/2,
                  Size, Size),
            QRect(rect.left()-Size/2,
                  rect.center().y()-Size/2,
                  Size, Size),
            QRect(rect.right()-Size/2,
                  rect.center().y()-Size/2,
                  Size, Size),
            QRect(rect.left()-Size/2,
                  rect.bottom()-Size/2,
                  Size, Size),
            QRect(rect.center().x()-Size/2,
                  rect.bottom()-Size/2,
                  Size, Size),
            QRect(rect.right()-Size/2,
                  rect.bottom()-Size/2,
                  Size, Size)
        };
        for (int i = 0; i < 8; ++i)
        {
            if (handles[i].contains(event->pos()))
            {
                active_handle_ = i;
                return;
            }
        }
    }
    active_handle_ = -1;
    begin_pos_=event->pos();
    end_pos_=event->pos();
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    active_handle_ = -1;
    is_drawing_=false;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (active_handle_ != -1)
    {
        QRect rect = QRect(begin_pos_, end_pos_).normalized();
        int left = rect.left();
        int right = rect.right();
        int top = rect.top();
        int bottom = rect.bottom();
        QPoint pos = event->pos();
        switch (active_handle_)
        {
        case 0:
            left = qMin(pos.x(), right);
            top = qMin(pos.y(), bottom);
            break;
        case 1:
            top = qMin(pos.y(), bottom);
            break;
        case 2:
            right = qMax(pos.x(), left);
            top = qMin(pos.y(), bottom);
            break;
        case 3:
            left = qMin(pos.x(), right);
            break;
        case 4:
            right = qMax(pos.x(), left);
            break;
        case 5:
            left = qMin(pos.x(), right);
            bottom = qMax(pos.y(), top);
            break;
        case 6:
            bottom = qMax(pos.y(), top);
            break;
        case 7:
            right = qMax(pos.x(), left);
            bottom = qMax(pos.y(), top);
            break;
        }
        rect.setCoords(left, top, right, bottom);
        begin_pos_ = rect.topLeft();
        end_pos_ = rect.bottomRight();
    }
    else
    {
        end_pos_=event->pos();
    }

    update();
}

void Dialog::on_pushButton_color_clicked()
{
    color_dialog_->setModal(true);
    color_dialog_->show();
}
#include "mylineedit.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFocusEvent>

MyLineEdit::MyLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    //startTimer(1000);
}

bool MyLineEdit::event(QEvent* event)
{
    static int count = 0;
    //qDebug() << "event count=" << count++;

    if (event->type() == QEvent::Paint)
    {
        //return true;
    }

    QPaintEvent* paint_event = dynamic_cast<QPaintEvent*>(event);
    if (paint_event)
    {
        //return true;
    }

    return QLineEdit::event(event);
}

void MyLineEdit::mousePressEvent(QMouseEvent* event)
{
    /*
    qDebug() << "MyLineEdit mousePressEvent";
    qDebug() << "pos=" << event->pos();
    qDebug() << "globalPos=" << event->globalPos();
    qDebug() << "localPos=" << event->localPos();
    qDebug() << "windowPos=" << event->windowPos();
    qDebug() << "screenPos=" << event->screenPos();*/
}

void MyLineEdit::mouseMoveEvent(QMouseEvent* event)
{
    //qDebug() << "MyLineEdit mouseMoveEvent";
    //QPoint pos = event->pos();
    QPoint pos = event->windowPos().toPoint();
    move(pos);
}

void MyLineEdit::mouseReleaseEvent(QMouseEvent* event)
{
    //qDebug() << "mouseReleaseEvent";
}

void MyLineEdit::keyPressEvent(QKeyEvent* event)
{
    //qDebug() << "keyPressEvent text=" << event->text();
    //qDebug() << "key=" << event->key();
    if (event->key() == Qt::Key_A)
    {
        qDebug() << "Key A Pressed";
    }

    QLineEdit::keyPressEvent(event);
}

void MyLineEdit::focusInEvent(QFocusEvent* event)
{
    //qDebug() << "focusInEvent";

    QLineEdit::focusInEvent(event);
}

void MyLineEdit::focusOutEvent(QFocusEvent* event)
{
    //qDebug() << "focusOutEvent";

    QLineEdit::focusOutEvent(event);
}

void MyLineEdit::timerEvent(QTimerEvent* event)
{
    static int count = 0;
    //qDebug() << "timerEvent count=" << count++;
}

void MyLineEdit::paintEvent(QPaintEvent* event)
{
    static int count = 0;
    //qDebug() << "paintEvent count=" << count++;

    QLineEdit::paintEvent(event);
}

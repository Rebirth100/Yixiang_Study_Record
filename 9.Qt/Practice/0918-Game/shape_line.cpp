#include "shape_line.h"

ShapeLine::ShapeLine(QWidget *parent)
    : QObject{parent}
{
    button_1_ = new QPushButton(parent);
    button_2_ = new QPushButton(parent);
    button_3_ = new QPushButton(parent);
    button_4_ = new QPushButton(parent);

    button_1_->setGeometry(100, 100, Size, Size);
    button_2_->setGeometry(100+Size, 100, Size, Size);
    button_3_->setGeometry(100+2*Size, 100, Size, Size);
    button_4_->setGeometry(100+3*Size, 100, Size, Size);

    button_1_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_2_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_3_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_4_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
}

void ShapeLine::Left()
{
    InnerLeft(button_1_);
    InnerLeft(button_2_);
    InnerLeft(button_3_);
    InnerLeft(button_4_);
}

void ShapeLine::Down()
{
}

void ShapeLine::Right()
{
}

void ShapeLine::Change()
{
    int x_1 = button_1_->x();
    int y_1 = button_1_->y();
    x_1 += Size;
    y_1 -= Size;
    button_1_->move(x_1, y_1);

    int x_2 = button_2_->x();
    int y_2 = button_2_->y();

    int x_3 = button_3_->x();
    int y_3 = button_3_->y();
    x_3 -= Size;
    y_3 += Size;
    button_3_->move(x_3, y_3);

    int x_4 = button_4_->x();
    int y_4 = button_4_->y();
    x_4 -= 2*Size;
    y_4 += 2*Size;
    button_4_->move(x_4, y_4);
}

void ShapeLine::InnerLeft(QPushButton* button)
{
    int x = button->x();
    int y = button->y();
    x -= Size;
    button->move(x, y);
}

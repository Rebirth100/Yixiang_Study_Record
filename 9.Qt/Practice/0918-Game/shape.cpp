#include "shape.h"

Shape::Shape(int x, int y, QWidget *parent)
    : QObject{parent}
{
    button_1_ = new QPushButton(parent);
    button_2_ = new QPushButton(parent);
    button_3_ = new QPushButton(parent);
    button_4_ = new QPushButton(parent);

    button_1_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_2_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_3_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
    button_4_->setStyleSheet(
        QString::fromUtf8("background-color: rgb(85, 85, 255);"));
}

void Shape::Left()
{
    InnerLeft(button_1_);
    InnerLeft(button_2_);
    InnerLeft(button_3_);
    InnerLeft(button_4_);
}

void Shape::Down()
{
}

void Shape::Right()
{
}

void Shape::Position(int x, int y)
{
}

void Shape::InnerLeft(QPushButton* button)
{
    int x = button->x();
    int y = button->y();
    x -= Size;
    button->move(x, y);
}
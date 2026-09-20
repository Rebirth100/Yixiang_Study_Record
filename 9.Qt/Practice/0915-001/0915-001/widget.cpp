#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_1_clicked()
{
    int num=1;
    if(state_==Begin)
    {
        first_number_=1;
        num=first_number_;

        state_=First_number;
    }
    else if(state_==First_number)
    {
        first_number_*=10;
        first_number_+=1;
        num=first_number_;
    }
    else if(state_==Operation)
    {
        second_number_=1;
        num=second_number_;

        state_=Second_number;
    }
    else if(state_==Second_number)
    {
        second_number_*=10;
        second_number_+=1;
        num=second_number_;
    }

}


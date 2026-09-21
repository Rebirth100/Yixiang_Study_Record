#include "widget.h"
#include "ui_widget.h"
#include <qdebug.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,
            this,&Widget::method_1_Calculate);

    connect(ui->pushButton,SIGNAL(clicked()),
            this,SLOT(method_2_Calculate()));

    connect(ui->pushButton,&QPushButton::clicked,
            [this]()
            {
                doCalculation("lambda");
            });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::method_1_Calculate()
{
    doCalculation("1");
}

void Widget::method_2_Calculate()
{
    doCalculation("2");
}

void Widget::doCalculation(const QString &methodName)
{

}



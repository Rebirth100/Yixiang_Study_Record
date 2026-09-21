#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,
            this,&Widget::button_clicked);

    connect(ui->pushButton,&QPushButton::clicked,
            this,&Widget::button_clicked);

    connect(ui->pushButton,SIGNAL(clicked()),
            this,SLOT(button_clicked()));

    connect(ui->pushButton,&QPushButton::clicked,
            []
            {
                qDebug()<<"lambda";
            });

    connect(ui->radioButton,&QRadioButton::clicked,
            this,&Widget::radio_checked);

    connect(this,&Widget::MySignal,this,&Widget::MySlot);

    // connect(ui->checkBox,&QCheckBox::clicked,
    //         this,&Widget::Check_clicked);

    connect(this,&Widget::MySignal,
            ui->radioButton,&QRadioButton::click);

    connect(this,&Widget::setText,
            ui->lineEdit,&QLineEdit::setText);

    connect(ui->pushButton_2,&QPushButton::clicked,ui->radioButton,&QRadioButton::click);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::button_clicked()
{
    static int count=0;
    qDebug()<<"button clicked count="<<count++;
    // connect(ui->pushButton,&QPushButton::clicked,
    //         this,&Widget::button_clicked);
}

// void Widget::MySlot()
// {
//     qDebug()<<"MySlot";
// }


void Widget::radio_checked(bool flag)
{
    qDebug()<<"radio_chaecked flag="<<flag;
}

void Widget::MySlot(Student* studnet)
{
    //qDebug()<<"MySlot name="<<student->name_;
}

void Widget::on_pushButton_2_clicked()
{
    Student* student =new Student;
    student->name_="学生";
    //emit MySignal(student);

    emit setText("这是一行文字");
}
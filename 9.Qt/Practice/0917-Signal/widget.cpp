#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //第一种，推荐
    connect(ui->pushButton, &QPushButton::clicked,
            this, &Widget::button_clicked);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &Widget::button_clicked);

    //第二种
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(button_clicked()));

    //第三种
    connect(ui->pushButton, &QPushButton::clicked,
            []
            {
                qDebug() << "lambda";
            });

    connect(ui->radioButton, &QRadioButton::clicked,
            this, &Widget::radio_checked);

    connect(this, &Widget::MySignal, this, &Widget::MySlot);

    connect(this, &Widget::MySignal,
            ui->radioButton, &QRadioButton::click);

    connect(this, &Widget::setText,
            ui->lineEdit, &QLineEdit::setText);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::button_clicked()
{
    static int count = 0;
    qDebug() << "button clicked count=" << count++;
    //connect(ui->pushButton, &QPushButton::clicked,
    //        this, &Widget::button_clicked);
}

void Widget::radio_checked(bool flag)
{
    qDebug() << "radio_checked flag=" << flag;
}

void Widget::MySlot(Student* student/*, int id*/)
{
    //qDebug() << "MySlot name=" << student->name_;
}

void Widget::on_pushButton_2_clicked()
{
    Student* student = new Student;
    student->name_ = "学生";
    emit MySignal(student);

    emit setText("这是一行文字");
}

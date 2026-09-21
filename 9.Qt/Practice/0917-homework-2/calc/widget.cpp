#include "widget.h"
#include "ui_widget.h"
#include <QLineEdit>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLineEdit*lineEdit=new QLineEdit(this);
    lineEdit->setGeometry(20,20,580,40);

    QPushButton* btn_1=new QPushButton("1",this);
    btn_1->setGeometry(20,80,130,50);
    QPushButton* btn_2=new QPushButton("2",this);
    btn_2->setGeometry(160,80,130,50);
    QPushButton* btn_3=new QPushButton("3",this);
    btn_3->setGeometry(300,80,130,50);
    QPushButton* btn_add=new QPushButton("+",this);
    btn_add->setGeometry(440,80,130,50);

    QPushButton* btn_4=new QPushButton("4",this);
    btn_4->setGeometry(20,140,130,50);
    QPushButton* btn_5=new QPushButton("5",this);
    btn_5->setGeometry(160,140,130,50);
    QPushButton* btn_6=new QPushButton("6",this);
    btn_6->setGeometry(300,140,130,50);
    QPushButton* btn_sub=new QPushButton("-",this);
    btn_sub->setGeometry(440,140,130,50);

    QPushButton* btn_7=new QPushButton("7",this);
    btn_7->setGeometry(20,200,130,50);
    QPushButton* btn_8=new QPushButton("8",this);
    btn_8->setGeometry(160,200,130,50);
    QPushButton* btn_9=new QPushButton("9",this);
    btn_9->setGeometry(300,200,130,50);
    QPushButton* btn_mul=new QPushButton("*",this);
    btn_mul->setGeometry(440,200,130,50);

    QPushButton* btn_c=new QPushButton("C",this);
    btn_c->setGeometry(20,260,130,50);
    QPushButton* btn_0=new QPushButton("0",this);
    btn_0->setGeometry(160,260,130,50);
    QPushButton* btn_eq=new QPushButton("=",this);
    btn_eq->setGeometry(300,260,130,50);
    QPushButton* btn_div=new QPushButton("/",this);
    btn_div->setGeometry(440,260,130,50);



    connect(btn_1,&QPushButton::clicked,this,[=](){lineEdit->insert("1");});
    connect(btn_2,&QPushButton::clicked,this,[=](){lineEdit->insert("2");});
    connect(btn_3,&QPushButton::clicked,this,[=](){lineEdit->insert("3");});
    connect(btn_4,&QPushButton::clicked,this,[=](){lineEdit->insert("4");});
    connect(btn_5,&QPushButton::clicked,this,[=](){lineEdit->insert("5");});
    connect(btn_6,&QPushButton::clicked,this,[=](){lineEdit->insert("6");});
    connect(btn_7,&QPushButton::clicked,this,[=](){lineEdit->insert("7");});
    connect(btn_8,&QPushButton::clicked,this,[=](){lineEdit->insert("8");});
    connect(btn_9,&QPushButton::clicked,this,[=](){lineEdit->insert("9");});
    connect(btn_0,&QPushButton::clicked,this,[=](){lineEdit->insert("10");});


    connect(btn_add,&QPushButton::clicked,this,[=](){lineEdit->insert("+");});
    connect(btn_sub,&QPushButton::clicked,this,[=](){lineEdit->insert("-");});
    connect(btn_mul,&QPushButton::clicked,this,[=](){lineEdit->insert("*");});
    connect(btn_div,&QPushButton::clicked,this,[=](){lineEdit->insert("/");});


    connect(btn_c,&QPushButton::clicked,this,[=](){lineEdit->clear();});
}

Widget::~Widget()
{
    delete ui;
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // connect(ui->lineEdit,&QLineEdit::textEdited,
    //         this,&Widget::setWindowTitle);


    // QLineEdit* lineEdit=new QLineEdit(this);
    // lineEdit->setGeometry(100,100,300,30);

    QLineEdit* lineEdit_number_1=new QLineEdit(this);
    lineEdit_number_1->setGeometry(50,90,101,21);
    QLineEdit* lineEdit_number_2=new QLineEdit(this);
    lineEdit_number_2->setGeometry(200,90,101,21);
    QLineEdit* lineEdit_number_3=new QLineEdit(this);
    lineEdit_number_3->setGeometry(350,90,101,21);

    QLabel* label_add=new QLabel("+",this);
    label_add->setGeometry(170,90,16,16);
    QLabel* label_equal=new QLabel("=",this);
    label_equal->setGeometry(320,90,16,16);

    QPushButton* button=new QPushButton("计算",this);
    button->setGeometry(220,170,71,31);
}

Widget::~Widget()
{
    delete ui;
}

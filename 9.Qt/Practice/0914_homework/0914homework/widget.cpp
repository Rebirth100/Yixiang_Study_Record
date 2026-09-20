#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    num1=0;
    num2=0;
    op="";
    isNextNum=false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_0_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"0");
}

void Widget::on_pushButton_1_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"1");
}

void Widget::on_pushButton_2_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"2");
}


void Widget::on_pushButton_3_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"3");
}


void Widget::on_pushButton_4_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"4");
}


void Widget::on_pushButton_5_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"5");
}


void Widget::on_pushButton_6_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"6");
}


void Widget::on_pushButton_7_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"7");
}


void Widget::on_pushButton_8_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"8");
}


void Widget::on_pushButton_9_clicked()
{
    if(isNextNum)
    {
        ui->lineEdit_display->clear();
        isNextNum=false;
    }
    QString str =ui->lineEdit_display->text();
    ui->lineEdit_display->setText(str+"9");
}


void Widget::on_pushButton_add_clicked()
{
    num1=ui->lineEdit_display->text().toInt();
    op="+";
    isNextNum=true;
}


void Widget::on_pushButton_sub_clicked()
{
    num1=ui->lineEdit_display->text().toInt();
    op="-";
    isNextNum=true;
}


void Widget::on_pushButton_mul_clicked()
{
    num1=ui->lineEdit_display->text().toInt();
    op="*";
    isNextNum=true;
}


void Widget::on_pushButton_div_clicked()
{
    num1=ui->lineEdit_display->text().toInt();
    op="/";
    isNextNum=true;
}


void Widget::on_pushButton_result_clicked()
{
    num2=ui->lineEdit_display->text().toInt();
    int result=0;

    if(op=="+")
        result=num1+num2;
    else if(op=="-")
        result=num1-num2;
    else if(op=="*")
        result=num1*num2;
    else if(op=="/")
    {
        if(num2!=0)
        result=num1/num2;
        else
        {
            ui->lineEdit_display->setText("请输入非0数");
            return;
        }
    }
    ui->lineEdit_display->setText(QString::number(result));
    isNextNum=true;
}


void Widget::on_pushButton_del_clicked()
{
    ui->lineEdit_display->clear();
    num1=0;
    num2=0;
    op.clear();
    isNextNum=false;
}


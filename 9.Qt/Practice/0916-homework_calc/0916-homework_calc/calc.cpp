#include "calc.h"
#include "ui_calc.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

calc::calc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calc)
{
    ui->setupUi(this);

    //显示框
    QVBoxLayout* mainLayout=new QVBoxLayout;
    mainLayout->addWidget(ui->lineEdit_display);

    //1,2,3，+
    QHBoxLayout* hLayout_2=new QHBoxLayout;
    hLayout_2->addWidget(ui->pushButton_1);
    hLayout_2->addWidget(ui->pushButton_2);
    hLayout_2->addWidget(ui->pushButton_3);
    hLayout_2->addWidget(ui->pushButton_add);
    mainLayout->addLayout(hLayout_2);

    //4,5,6，-
    QHBoxLayout* hLayout_3=new QHBoxLayout;
    hLayout_3->addWidget(ui->pushButton_4);
    hLayout_3->addWidget(ui->pushButton_5);
    hLayout_3->addWidget(ui->pushButton_6);
    hLayout_3->addWidget(ui->pushButton_sub);
    mainLayout->addLayout(hLayout_3);

    //7,8,9，*
    QHBoxLayout* hLayout_4=new QHBoxLayout;
    hLayout_4->addWidget(ui->pushButton_7);
    hLayout_4->addWidget(ui->pushButton_8);
    hLayout_4->addWidget(ui->pushButton_9);
    hLayout_4->addWidget(ui->pushButton_mul);
    mainLayout->addLayout(hLayout_4);

    //C,0，=，/
    QHBoxLayout* hLayout_5=new QHBoxLayout;
    hLayout_5->addWidget(ui->pushButton_del);
    hLayout_5->addWidget(ui->pushButton_0);
    hLayout_5->addWidget(ui->pushButton_result);
    hLayout_5->addWidget(ui->pushButton_div);
    mainLayout->addLayout(hLayout_5);

    setLayout(mainLayout);
}

calc::~calc()
{
    delete ui;
}

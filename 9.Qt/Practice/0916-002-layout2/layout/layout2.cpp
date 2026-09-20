#include "layout2.h"
#include "ui_layout2.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

layout2::layout2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::layout2)
{
    ui->setupUi(this);

    //水平布局
    // QHBoxLayout*hLayout_1=new QHBoxLayout;
    // hLayout_1->addWidget(ui->pushButton_1);
    // hLayout_1->addWidget(ui->pushButton_2);
    // setLayout(hLayout_1);

    //垂直布局
    // QVBoxLayout* vLayout_1=new QVBoxLayout;
    // vLayout_1->addWidget(ui->pushButton_1);
    // vLayout_1->addWidget(ui->pushButton_2);
    // setLayout(vLayout_1);

    /*
    QHBoxLayout* hLayout_1=new QHBoxLayout;
    hLayout_1->addWidget(ui->pushButton_1);
    hLayout_1->addWidget(ui->pushButton_2);

    QHBoxLayout* hLayout_2=new QHBoxLayout;
    hLayout_2->addStretch();
    hLayout_2->addWidget(ui->lineEdit);
    hLayout_2->addStretch();
    QVBoxLayout* vLayout_1=new QVBoxLayout;
    //vLayout_1->addWidget(ui->lineEdit);
    vLayout_1->addLayout(hLayout_2);
    vLayout_1->addLayout(hLayout_1);
    setLayout(vLayout_1);*/

    /*
    QGridLayout* gLayout=new QGridLayout;
    gLayout->addWidget(ui->pushButton_1);
    gLayout->addWidget(ui->pushButton_2);
    gLayout->addWidget(ui->lineEdit);
    setLayout(gLayout);*/

    /*
    QGridLayout* gLayout=new QGridLayout;
    gLayout->addWidget(ui->pushButton_1,0,0);
    gLayout->addWidget(ui->pushButton_2,1,0);
    gLayout->addWidget(ui->lineEdit,0,1);
    gLayout->addWidget(ui->pushButton_3,0,2);
    gLayout->addWidget(ui->pushButton,2,0);
    setLayout(gLayout);*/

    /*
    QHBoxLayout* hLayout_1=new QHBoxLayout;
    hLayout_1->addWidget(ui->pushButton_1);
    hLayout_1->addWidget(ui->lineEdit);
    hLayout_1->addWidget(ui->pushButton_2);
    // QHBoxLayout* hLayout_1=new QHBoxLayout;
    // hLayout_1->addWidget(ui->pushButton_3);
    // hLayout_1->addWidget(ui->pushButton);


    QFormLayout* fLayout_1=new QFormLayout;
    // fLayout_1->addWidget(ui->pushButton_1);
    // fLayout_1->addWidget(ui->lineEdit);
    fLayout_1->addItem(hLayout_1);
    setLayout(fLayout_1);*/



    QHBoxLayout* hLayout_1=new QHBoxLayout;
    hLayout_1->addWidget(ui->lineEdit_number_1);
    hLayout_1->addWidget(ui->label_add);
    hLayout_1->addWidget(ui->lineEdit_number_2);
    hLayout_1->addWidget(ui->label_equal);
    hLayout_1->addWidget(ui->lineEdit_result);

    QHBoxLayout* hLayout_2=new QHBoxLayout;
    hLayout_2->addStretch();
    hLayout_2->addWidget(ui->pushButton_calc);
    hLayout_2->addStretch();

    QVBoxLayout* vLayout=new QVBoxLayout;
    vLayout->addLayout(hLayout_1);
    vLayout->addLayout(hLayout_2);
    setLayout(vLayout);


}

layout2::~layout2()
{
    delete ui;
}

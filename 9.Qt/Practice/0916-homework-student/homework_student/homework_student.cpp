#include "homework_student.h"
#include "ui_homework_student.h"

#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

homework_student::homework_student(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::homework_student)
{
    ui->setupUi(this);

    QVBoxLayout* mainLayout=new QVBoxLayout;
    mainLayout->addWidget(ui->label_title);

    QHBoxLayout* hLayout=new QHBoxLayout;
    hLayout->addWidget(ui->line);
    mainLayout->addLayout(hLayout);

    QHBoxLayout* hLayout_1=new QHBoxLayout;
    hLayout_1->addWidget(ui->label_name);
    hLayout_1->addWidget(ui->lineEdit_name);

    hLayout_1->addWidget(ui->label_age);
    hLayout_1->addWidget(ui->spinBox_age);

    hLayout_1->addWidget(ui->label_gen);
    hLayout_1->addWidget(ui->radioButton_boy);
    hLayout_1->addWidget(ui->radioButton_girl);

    hLayout_1->addWidget(ui->label_Eth);
    hLayout_1->addWidget(ui->comboBox_Eth);
    mainLayout->addLayout(hLayout_1);

    QHBoxLayout* hLayout_2=new QHBoxLayout;
    hLayout_2->addWidget(ui->label_addr);
    hLayout_2->addWidget(ui->comboBox_province);
    hLayout_2->addWidget(ui->comboBox_city);

    hLayout_2->addWidget(ui->label_birthday);
    hLayout_2->addWidget(ui->dateEdit_birthday);

    mainLayout->addLayout(hLayout_2);
    QHBoxLayout* hLayout_3=new QHBoxLayout;
    hLayout_3->addWidget(ui->line_2);
    mainLayout->addLayout(hLayout_3);

    QHBoxLayout* hLayout_4=new QHBoxLayout;
    hLayout_4->addWidget(ui->label_course);
    hLayout_4->addWidget(ui->checkBox_C);
    hLayout_4->addWidget(ui->checkBox_p);
    hLayout_4->addWidget(ui->checkBox_cpp);
    hLayout_4->addWidget(ui->checkBox_math);
    hLayout_4->addWidget(ui->checkBox_english);
    hLayout_4->addWidget(ui->checkBox_computer);
    hLayout_4->addWidget(ui->checkBox_network);
    hLayout_4->addWidget(ui->checkBox_struct);
    hLayout_4->addWidget(ui->checkBox_data);
    hLayout_4->addWidget(ui->checkBox_os);
    hLayout_4->addWidget(ui->checkBox_line_math);
    hLayout_4->addWidget(ui->checkBox_all);

    mainLayout->addLayout(hLayout_4);
    QHBoxLayout* hLayout_5=new QHBoxLayout;
    hLayout_5->addWidget(ui->line_3);

    mainLayout->addLayout(hLayout_5);
    QHBoxLayout* hLayout_6=new QHBoxLayout;
    hLayout_6->addWidget(ui->label_talk);
    hLayout_6->addWidget(ui->textEdit_talk);
    hLayout_6->addWidget(ui->pushButton_ok);
    hLayout_6->addWidget(ui->textBrowser_display);

    mainLayout->addLayout(hLayout_6);
    setLayout(mainLayout);
}

homework_student::~homework_student()
{
    delete ui;
}

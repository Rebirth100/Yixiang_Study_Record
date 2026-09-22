#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QRadioButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_open,&QAction::triggered,
            [this]
            {
                QMessageBox::information(this,"title","open");
            });

    // connect(ui->action_edit,&QMenu::triggered,
    //         []
    //         (QAction* acation)
    //         {
    //             qDebug()<<"acation="<<acation;
    //         });

    connect(ui->menu,&QMenu::hovered,
            [](QAction *action){qDebug()<<"action="<<action;});

    QToolBar* tool_bal=new QToolBar;
    QRadioButton* rb_1=new QRadioButton("1");
    QRadioButton* rb_2=new QRadioButton("2");
    tool_bal->addWidget(rb_1);
    tool_bal->addWidget(rb_2);
    connect(rb_1,&QRadioButton::toggled,[](bool checked){if(checked)qDebug()<<"1";});
    connect(rb_2,&QRadioButton::toggled,[](bool checked){if(checked)qDebug()<<"2";});

    QPushButton* button_open=new QPushButton("打开");
    tool_bal->addWidget(button_open);
    connect(button_open,&QPushButton::clicked,
            [this]
            {
                QMessageBox::information(this,"title","OPen");
            });
    tool_bal->addWidget(button_open);
    QLineEdit* line_edit=new QLineEdit;
    tool_bal->addWidget(line_edit);

    addToolBar(tool_bal);

    QWidget* widget=new QWidget;

    QLineEdit *lineEdit_num_1 = new QLineEdit(widget);
    // lineEdit_num_1->setGeometry(100,100,300,20);
    QLineEdit *lineEdit_num_2 = new QLineEdit(widget);
    QLineEdit *lineEdit_num_result = new QLineEdit(widget);
    QLabel *lable_add = new QLabel("+", widget);
    QLabel *lable_equal = new QLabel("=", widget);
    QPushButton *button_calc = new QPushButton("计算", widget);

    QHBoxLayout *hLayout_1 = new QHBoxLayout;
    hLayout_1->addWidget(lineEdit_num_1);
    hLayout_1->addWidget(lable_add);
    hLayout_1->addWidget(lineEdit_num_2);
    hLayout_1->addWidget(lable_equal);
    hLayout_1->addWidget(lineEdit_num_result);
    QHBoxLayout *hlayout_2 = new QHBoxLayout;
    hlayout_2->addStretch();
    hlayout_2->addWidget(button_calc);
    hlayout_2->addStretch();
    QVBoxLayout *vlayout_ = new QVBoxLayout;
    vlayout_->addLayout(hLayout_1);
    vlayout_->addLayout(hlayout_2);
    widget->setLayout(vlayout_);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

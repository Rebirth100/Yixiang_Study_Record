#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    file_dialog_=new QFileDialog(this);
    connect(file_dialog_,&QFileDialog::fileSelected,
            [](const QString& file)
            {
                qDebug()<<"file="<<file;
            });

    color_dialog_=new QColorDialog(this);
    connect(ui->pushButton_color,&QPushButton::clicked,this,
            &Dialog::pushButton_color);
    // connect(color_dialog_,&QColorDialog::colorSelected,
    //         [](const QColor& color)
    //         {
    //             int r=color.red();
    //             int g=color.green();
    //             int b=color.blue();
    //             QString sheet=QString(
    //                 "background-color:rgb(%1,%2,%3);")
    //                                 .arg(r).arg(g).arg(b);
    //             this->setStyleSheet(sheet);
    // });
    connect(color_dialog_,&QColorDialog::currentColorChanged,
            [this](const QColor color){
                int r=color.red();
                int g=color.green();
                int b=color.blue();
                QString sheet=QString("background:rgb(%1,%2,%3);")
                                    .arg(r).arg(g).arg(b);
                this->setStyleSheet(sheet);
    });

    connect(file_dialog_,&QFileDialog::currentChanged,
            [](const QString path){qDebug()<<"path="<<path;});
    //void directoryEntered(const QString &directory);

    font_dialog = new QFontDialog(this);
    connect(font_dialog, &QFontDialog::fontSelected,
            [this](const QFont font) { ui->pushButton_font->setFont(font); });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_open_clicked()
{
    QDialog* new_dialog=new QDialog(this);
    new_dialog->resize(300,300);
    new_dialog->setModal(true);
    new_dialog->show();

}


void Dialog::on_pushButton_file_clicked()
{
    //QFileDialog* file_dialog =new QFileDialog(this);
    file_dialog_->setModal(true);
    file_dialog_->show();
}

void Dialog::pushButton_color()
{
    color_dialog_->setModal(true);
    color_dialog_->show();
}

void Dialog::on_pushButton_font_clicked()
{
    font_dialog->setModal(true);
    font_dialog->show();
}


void Dialog::on_pushButton_message_clicked()
{
    QMessageBox::information(this, "标题", "这是一个对话框");
    QMessageBox::question(this, "标题", "Are you crazy?");
    QMessageBox::critical(this, "标题", "即将自毁");
    QMessageBox::warning(this, "标题", "warning!");
}




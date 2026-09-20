#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Student)
{
    ui->setupUi(this);
}

Student::~Student()
{
    delete ui;
}

void Student::on_pushButton_ok_clicked()
{
    //姓名
    QString name=ui->lineEdit_name->text();
    QString label_name=ui->label_name->text();
    QString name_total=label_name+":"+name;
    ui->textBrowser_display->append(name_total);

    //年龄
    QString age=ui->label_age->text();
    QString label_age=ui->spinBox_age->text();
    QString age_total=age+":"+label_age;
    ui->textBrowser_display->append(age_total);

    //性别
    QString gen;
    if(ui->radioButton_boy->isChecked())
    {
        gen=ui->radioButton_boy->text();
    }
    else if(ui->radioButton_girl->isChecked())
    {
        gen=ui->radioButton_girl->text();
    }
    ui->textBrowser_display->append(ui->label_gen->text()+":"+gen);
    // QString gen=ui->label_gen->text();
    // QString label_gen=ui->label_gen->text();

    //QString radioButton_boy
    //bool ischacked();


    //民族
    QString Eth=ui->comboBox_Eth->currentText();
    QString label_Eth=ui->label_Eth->text();
    QString Eth_total=label_Eth+":"+Eth;
    ui->textBrowser_display->append(Eth_total);

    //籍贯
    QString addr=ui->label_addr->text();
    QString pro=ui->comboBox_province->currentText();
    QString city=ui->comboBox_city->currentText();
    QString addr_total=addr+":"+pro+city;
    ui->textBrowser_display->append(addr_total);


    //生日
    QString birthday=ui->label_birthday->text();
    QString date=ui->dateEdit_birthday->date().toString("yyyy-MM-dd");
    QString date_total=birthday+":"+date;
    ui->textBrowser_display->append(date_total);

    //课程
    QString course=ui->label_course->text();
    QString C=ui->checkBox_C->text();

    QString all=ui->checkBox_all->text();
    QString all_one=course+":"+all;
    ui->textBrowser_display->append(all_one);

    //自我评价
    QString talk=ui->label_talk->text();
    QString label_talk=ui->textEdit_talk->toPlainText();
    QString talk_total=talk+":"+label_talk;
    ui->textBrowser_display->append(talk_total);


}


void Student::on_checkBox_all_clicked(bool checked)
{
    qDebug()<<"checked="<<checked;

    if(checked)
    {
        ui->checkBox_C->setChecked(true);
        ui->checkBox_computer->setChecked(true);
    }
    else
    {
        ui->checkBox_C->setChecked(false);
        ui->checkBox_computer->setChecked(false);
    }
}
void Student::on_checkBox_C_clicked(bool checked)
{
    if(checked==false)
    {
        ui->checkBox_all->setChecked(false);
    }
}


void Student::on_comboBox_province_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1 =ui->comboBox_province->currentText();
    if(arg1.compare("陕西省")==0)
    {
        ui->comboBox_city->addItem("西安市");
        ui->comboBox_city->addItem("咸阳市");
    }
    else if(arg1.compare("河南省")==0)
    {
        ui->comboBox_city->addItem("太原");
        ui->comboBox_city->addItem("大同");
    }
}





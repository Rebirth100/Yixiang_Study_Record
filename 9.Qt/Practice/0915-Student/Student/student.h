#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Student;
}
QT_END_NAMESPACE

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    ~Student() override;

private slots:
    void on_pushButton_ok_clicked();

    void on_checkBox_all_clicked(bool checked);

    void on_comboBox_province_currentTextChanged(const QString &arg1);

    void on_checkBox_C_clicked(bool checked);

private:
    Ui::Student *ui;
};
#endif // STUDENT_H

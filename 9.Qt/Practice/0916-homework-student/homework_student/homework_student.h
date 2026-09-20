#ifndef HOMEWORK_STUDENT_H
#define HOMEWORK_STUDENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class homework_student;
}
QT_END_NAMESPACE

class homework_student : public QWidget
{
    Q_OBJECT

public:
    explicit homework_student(QWidget *parent = nullptr);
    ~homework_student() override;

private:
    Ui::homework_student *ui;
};
#endif // HOMEWORK_STUDENT_H

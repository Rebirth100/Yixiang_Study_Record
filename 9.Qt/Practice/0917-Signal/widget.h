#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Student
{
public:
    QString name_;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void button_clicked();

    void radio_checked(bool flag);

    void MySlot(Student* student/*, int id*/);

    void on_pushButton_2_clicked();

signals:
    void MySignal(Student* student);

    void setText(const QString &);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

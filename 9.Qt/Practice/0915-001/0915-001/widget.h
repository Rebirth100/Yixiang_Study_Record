#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_pushButton_1_clicked();

private:
    enum State
    {
        Begin,
        First_number,
        Operation,
        Second_number,
        Equal,
        Result=Equal,
    };

private:
    Ui::Widget *ui;


    State state_=Begin;
    int first_number_=0;
    int second_number_=0;

};
#endif // WIDGET_H

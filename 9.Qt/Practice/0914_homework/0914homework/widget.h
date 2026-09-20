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

    void on_pushButton_0_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_mul_clicked();

    void on_pushButton_div_clicked();

    void on_pushButton_result_clicked();

    void on_pushButton_del_clicked();

private:
    Ui::Widget *ui;

private:
    int num1;
    int num2;
    QString op;
    bool isNextNum;
};
#endif // WIDGET_H

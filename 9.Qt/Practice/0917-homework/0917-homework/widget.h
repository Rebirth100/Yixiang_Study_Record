#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

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
    void method_1_Calculate();
    void method_2_Calculate();

private:
    void doCalculation(const QString &methodName);

    Ui::Widget *ui;
};
#endif // WIDGET_H

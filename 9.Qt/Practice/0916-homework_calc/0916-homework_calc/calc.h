#ifndef CALC_H
#define CALC_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class calc;
}
QT_END_NAMESPACE

class calc : public QWidget
{
    Q_OBJECT

public:
    explicit calc(QWidget *parent = nullptr);
    ~calc() override;

private:
    Ui::calc *ui;
};
#endif // CALC_H

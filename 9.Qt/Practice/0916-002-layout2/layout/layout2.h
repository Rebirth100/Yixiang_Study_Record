#ifndef LAYOUT2_H
#define LAYOUT2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class layout2;
}
QT_END_NAMESPACE

class layout2 : public QWidget
{
    Q_OBJECT

public:
    explicit layout2(QWidget *parent = nullptr);
    ~layout2() override;

private:
    Ui::layout2 *ui;
};
#endif // LAYOUT2_H

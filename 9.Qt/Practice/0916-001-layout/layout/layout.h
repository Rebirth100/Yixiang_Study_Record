#ifndef LAYOUT_H
#define LAYOUT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class layout;
}
QT_END_NAMESPACE

class layout : public QWidget
{
    Q_OBJECT

public:
    explicit layout(QWidget *parent = nullptr);
    ~layout() override;

private:
    Ui::layout *ui;
};
#endif // LAYOUT_H

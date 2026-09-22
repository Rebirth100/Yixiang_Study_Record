#ifndef DIALOG_H
#define DIALOG_H

#include <QTimer>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_stop_timer_clicked();

    void on_pushButton_stop_timer_2_clicked();

private:
    Ui::Dialog *ui;
    int lineEdit_timer_id_ = 0;
    QTimer* timer_ = nullptr;
};
#endif // DIALOG_H

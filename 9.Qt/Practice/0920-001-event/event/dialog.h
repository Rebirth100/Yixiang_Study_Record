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

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    bool eventFilter(QObject *watched,QEvent* event)override;

private slots:
    void on_pushButton_stop_timer_clicked();
    void on_pushButton_stop_timer_2_clicked();

private:
    Ui::Dialog *ui;
    int lineEdit_time_id_=0;
    QTimer* timer_=nullptr;
};
#endif // DIALOG_H

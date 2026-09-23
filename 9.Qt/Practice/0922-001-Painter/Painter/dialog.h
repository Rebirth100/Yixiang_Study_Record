#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>

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
    void paintEvent(QPaintEvent* event)override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
private slots:
    void on_pushButton_color_clicked();

private:
    Ui::Dialog *ui;
    QPoint begin_pos_;
    QPoint end_pos_;
    QColor pen_color_{0,0,0};
    QColorDialog* color_dialog_=nullptr;
    bool is_drawing_ = false;
    int active_handle_ = -1;
};
#endif // DIALOG_H
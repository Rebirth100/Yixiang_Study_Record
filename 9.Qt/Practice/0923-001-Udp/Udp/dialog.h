#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>

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

private slots:
    void on_pushButton_start_clicked();

private:
    Ui::Dialog *ui;
    QUdpSocket* socket_ = nullptr;
};
#endif // DIALOG_H

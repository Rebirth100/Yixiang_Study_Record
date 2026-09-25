#ifndef DIALOG_H
#define DIALOG_H
#include <QTcpServer>
#include <QDialog>
#include <QtHttpServer>

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
    void on_pushButton_open_clicked();

private:
    Ui::Dialog *ui;
    QTcpServer* tcp_server_= nullptr;
    QHttpServer* http_server_=nullptr;
};
#endif // DIALOG_H

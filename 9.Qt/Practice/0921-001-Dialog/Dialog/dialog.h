#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

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

    void on_pushButton_file_clicked();

    void pushButton_color();

    void on_pushButton_font_clicked();

    void on_pushButton_message_clicked();

private:
    Ui::Dialog *ui;
    QFileDialog* file_dialog_=nullptr ;
    QColorDialog* color_dialog_=nullptr;
    QFontDialog* font_dialog=nullptr;
};
#endif // DIALOG_H

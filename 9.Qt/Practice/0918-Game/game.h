#ifndef GAME_H
#define GAME_H

#include <QDialog>

class Shape;

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game() override;

private slots:
    void on_pushButton_left_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::Game *ui;

    Shape* shape_ = nullptr;
};
#endif // GAME_H

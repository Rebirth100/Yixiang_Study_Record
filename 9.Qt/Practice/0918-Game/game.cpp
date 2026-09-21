#include "game.h"
#include "ui_game.h"

#include "shape_line.h"
#include "shape_t.h"

Game::Game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    //line_ = new ShapeLine(this);
    shape_ = new ShapeT(100, 100, this);
}

Game::~Game()
{
    delete ui;
}

void Game::on_pushButton_left_clicked()
{
    shape_->Left();
}


void Game::on_pushButton_change_clicked()
{
    shape_->Change();
}


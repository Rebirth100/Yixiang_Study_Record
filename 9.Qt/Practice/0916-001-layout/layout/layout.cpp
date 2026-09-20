#include "layout.h"
#include "ui_layout.h"

layout::layout(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::layout)
{
    ui->setupUi(this);
}

layout::~layout()
{
    delete ui;
}

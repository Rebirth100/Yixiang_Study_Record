#include "shape_t.h"

ShapeT::ShapeT(int x, int y, QWidget *parent)
    : Shape(x, y, parent)
{
    Position(x, y);
}

void ShapeT::Change()
{
}

void ShapeT::Position(int x, int y)
{
    button_1_->setGeometry(x, y, Size, Size);
    button_2_->setGeometry(x+Size, y, Size, Size);
    button_3_->setGeometry(x+2*Size, y, Size, Size);
    button_4_->setGeometry(x+Size, y-Size, Size, Size);
}
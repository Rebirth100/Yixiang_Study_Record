#ifndef SHAPE_T_H
#define SHAPE_T_H

#include "shape.h"

class ShapeT : public Shape
{
public:
    ShapeT(int x, int y, QWidget *parent);

public:
    virtual void Change();

protected:
    virtual void Position(int x, int y);
};

#endif // SHAPE_T_H

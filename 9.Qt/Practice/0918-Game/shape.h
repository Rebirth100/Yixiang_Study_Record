#ifndef SHAPE_H
#define SHAPE_H

#include <QPushButton>

class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(int x, int y, QWidget *parent = nullptr);

public:
    void Left();

    void Down();

    void Right();

    virtual void Change() = 0;

protected:
    virtual void Position(int x, int y) = 0;

private:
    void InnerLeft(QPushButton* button);

signals:

protected:
    const int Size = 30;
    QPushButton* button_1_ = nullptr;
    QPushButton* button_2_ = nullptr;
    QPushButton* button_3_ = nullptr;
    QPushButton* button_4_ = nullptr;
};

#endif // SHAPE_H

#ifndef SHAPE_H
#define SHAPE_H

#include <QPushButton>

class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(QWidget *parent = nullptr);

public:
    void Left();
    void Right();
    void Down();
    virtual void Change();

protected:
    virtual void Position(int x,int y)=0;

private:
    void InnerLeft(QPushButton* button);
    void InnerRight(QPushButton* button);
    void InnerDown(QPushButton* button);
    void InnerChange(QPushButton* button);
signals:

private:
    const int Size=30;
    QPushButton* button_1_ =nullptr;
    QPushButton* button_2_ =nullptr;
    QPushButton* button_3_ =nullptr;
    QPushButton* button_4_ =nullptr;
};



#endif // SHAPE_LINE_H

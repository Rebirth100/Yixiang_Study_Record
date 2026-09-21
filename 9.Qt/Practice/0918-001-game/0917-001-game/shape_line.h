#ifndef SHAPE_LINE_H
#define SHAPE_LINE_H

#include <QObject>
#include <QPushButton>

class ShapeLine : public QObject
{
    Q_OBJECT
public:
    explicit ShapeLine(QWidget *parent = nullptr);

public:
    void Left();
    void Right();
    void Down();
    void Change();

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

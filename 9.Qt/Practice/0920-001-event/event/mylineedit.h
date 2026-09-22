#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit:public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent=nullptr);

signals:

protected:
    bool event(QEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void timerEvent(QTimerEvent* event)override;
    void paintEvent(QPaintEvent* event)override;
};

#endif // MYLINEEDIT_H

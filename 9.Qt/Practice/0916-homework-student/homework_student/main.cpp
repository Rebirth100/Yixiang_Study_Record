#include "homework_student.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    homework_student w;
    w.show();
    return QApplication::exec();
}

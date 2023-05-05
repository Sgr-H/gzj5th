#include "widgetui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widgetui w;
    w.show();
    return a.exec();
}

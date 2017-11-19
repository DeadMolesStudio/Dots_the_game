#include "widget.h"
#include <QApplication>
//#include "level.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Level level(15, 6, 6);
    Widget w;
    w.show();

    return a.exec();
}

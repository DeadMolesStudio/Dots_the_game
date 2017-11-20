//#include "widget.h"
#include <QApplication>
//#include "level.h"
#include "field.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Level level(15, 6, 6);
    //Widget w;
    Field w(0, 7, 7);
    w.show();

    return a.exec();
}

#include <QApplication>
#include "level.h"
#include "field.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Level level(15, 7, 7);
    //level.get_field().show();
    Field w(0, 7, 7);
    w.show();
    return a.exec();
}

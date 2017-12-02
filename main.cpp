#include <QApplication>
#include "level.h"
#include "field.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Level level(0, 5, 6, 6);
    level.show();
    return a.exec();
}

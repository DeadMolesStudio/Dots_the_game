#include <QApplication>
#include "level.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Level level(0, 10, 7, 7);
    level.show();
    return a.exec();
}

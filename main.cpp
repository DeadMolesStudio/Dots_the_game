#include <QApplication>
#include "level.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Level *level = new Level(0, 15, 7, 7);
    level->show();
    return a.exec();
}

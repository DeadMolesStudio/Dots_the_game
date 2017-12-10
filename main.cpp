#include <QApplication>
#include "level.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Level *level = new Level(0, 15, 7, 7);
    MainWindow *window = new MainWindow();
    //window->show();
    //level->show();
    return a.exec();
}

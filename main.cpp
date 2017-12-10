#include <QApplication>
#include "level.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *window = new MainWindow();
    return a.exec();
}

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *)
{
    stack = new QStackedWidget();
    level = new Level(0, 15, 7, 7);
    menu = new Menu();

    createMainWindow();
}

void MainWindow::createMainWindow()
{
    stack->addWidget(menu);

    stack->addWidget(level);
    stack->addWidget(level->selecter);

    stack->setCurrentIndex(0);
    stack->show();
    connect(menu, &Menu::quit_SIGNAL, this, &MainWindow::quit);
    connect(menu, &Menu::play_SIGNAL, this, &MainWindow::play);
    connect(menu, &Menu::choose_level_SIGNAL, this, &MainWindow::choose_level);


}

void MainWindow::play()
{
    stack->setCurrentIndex(stack->indexOf(level));
}

void MainWindow::quit()
{
    QCoreApplication::exit();
}

void MainWindow::choose_level()
{

}

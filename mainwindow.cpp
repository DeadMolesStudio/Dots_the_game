#include "mainwindow.h"

MainWindow::MainWindow(QWidget *)
{
    stack = new QStackedWidget();
    level = new Level(0, 15, 7, 7);
    menu = new Menu();
    level_selecter = new Level_selecter(0, 4);
    help_window = new Help();
    createMainWindow();
}

void MainWindow::createMainWindow()
{
    stack->setWindowTitle("Dots");
    stack->setWindowIcon(QIcon(QPixmap(":/images/icon.png")));
    this->setWindowIcon(QIcon(QPixmap(":/images/icon.png")));
    menu->setWindowIcon(QIcon(QPixmap(":/images/icon.png")));
    stack->setWindowIconText("kek");
    stack->addWidget(menu);
    stack->addWidget(level);
    stack->addWidget(level->selecter);
    stack->addWidget(level_selecter);

    stack->setCurrentIndex(0);
    stack->setFixedSize(level->sizeHint());
    menu->setFixedSize(stack->sizeHint());
    level_selecter->setFixedSize(stack->sizeHint());
    help_window->setFixedWidth(stack->sizeHint().width());
    help_window->setFixedHeight(stack->sizeHint().height() * 1.5);

    stack->addWidget(help_window);

    stack->show();
    connect(menu, &Menu::quit_SIGNAL, this, &MainWindow::quit);
    connect(menu, &Menu::play_SIGNAL, this, &MainWindow::play);
//    connect(level_selecter, &Level_selecter::play_SIGNAL, this, &MainWindow::play);

    connect(menu, &Menu::choose_level_SIGNAL, this, &MainWindow::choose_level);
    connect(menu, &Menu::help_SIGNAL, this, &MainWindow::help);
    connect(level, &Level::show_selecter_SIGNAL, this, &MainWindow::choose_bonus);
    connect(level_selecter, &Level_selecter::to_menu_SIGNAL, this, &MainWindow::show_menu);

    connect(level, &Level::to_menu_SIGNAL, this, &MainWindow::show_menu);

    connect(level_selecter, &Level_selecter::selected_level, this, &MainWindow::new_level);
    connect(this, &MainWindow::level_activate, level, &Level::choosed_level);
    connect(level, &Level::clear_me, this, &MainWindow::clear_level);

    connect(help_window, &Help::to_menu, this, &MainWindow::show_menu);


}

void MainWindow::play()
{
    stack->setCurrentIndex(stack->indexOf(level));
    stack->setFixedSize(level->size());
}

void MainWindow::quit()
{
    QCoreApplication::exit();
}

void MainWindow::choose_level()
{
    stack->setFixedSize(stack->sizeHint());
    stack->setCurrentWidget(level_selecter);
}

void MainWindow::help()
{
    qDebug() << "HELP";
    stack->setFixedSize(stack->sizeHint());
    stack->setCurrentIndex(stack->indexOf(help_window));
}

void MainWindow::new_level(uint number)
{
    stack->removeWidget(level);
    stack->removeWidget(level->selecter);
    level = new Level(0, 15, 7, 7);
    stack->addWidget(level);
    stack->addWidget(level->selecter);
    connect(this, &MainWindow::level_activate, level, &Level::choosed_level);
    connect(level, &Level::show_selecter_SIGNAL, this, &MainWindow::choose_bonus);
    connect(level, &Level::to_menu_SIGNAL, this, &MainWindow::show_menu);
    connect(level, &Level::clear_me, this, &MainWindow::clear_level);

    emit level_activate(number);
    play();
}

void MainWindow::clear_level()
{
    stack->removeWidget(level);
    stack->removeWidget(level->selecter);
    level = new Level(0, 15, 7, 7);
    stack->addWidget(level);
    stack->addWidget(level->selecter);
    connect(this, &MainWindow::level_activate, level, &Level::choosed_level);
    connect(level, &Level::show_selecter_SIGNAL, this, &MainWindow::choose_bonus);
    connect(level, &Level::to_menu_SIGNAL, this, &MainWindow::show_menu);
    connect(level, &Level::clear_me, this, &MainWindow::clear_level);

}

void MainWindow::choose_bonus(bool show)
{
    if (show)
    {
        stack->setCurrentIndex(stack->indexOf(level->selecter));
    }
    else
    {
        stack->setCurrentIndex(stack->indexOf(level));
    }
}

void MainWindow::show_menu()
{
    stack->setCurrentWidget(menu);
    stack->setFixedSize(level->sizeHint());
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "level.h"
#include <QStackedWidget>
#include <menu.h>
#include <level_selecter.h>
#include <QIcon>
#include "help.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
private:
    QStackedWidget *stack;
    Level *level;
    Menu *menu;
    Level_selecter *level_selecter;
    Help *help_window;
    QVector<QPushButton*> buttons;
    void createMainWindow();

private slots:
    void play();
    void quit();
    void choose_level();
    void choose_bonus(bool show);
    void show_menu();
    void help();
    void new_level(uint number);
    void clear_level();
signals:
    void level_activate(uint number);
};

#endif // MAINWINDOW_H

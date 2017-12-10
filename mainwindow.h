#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "level.h"
#include <QStackedWidget>
#include <menu.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
private:
    QStackedWidget *stack;
    Level *level;
    Menu *menu;
    QVector<QPushButton*> buttons;

    void createMainWindow();

private slots:
    void play();
    void quit();
    void choose_level();
};

#endif // MAINWINDOW_H

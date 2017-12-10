#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>
#include <QDebug>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = 0);

private:
    QVector<QPushButton*> buttons;
    QGridLayout *layout;

private slots:
    void quit_SLOT();
    void choose_level_SLOT();
    void play_SLOT();

signals:
    void play_SIGNAL();
    void choose_level_SIGNAL();
    void quit_SIGNAL();
};

#endif // MENU_H

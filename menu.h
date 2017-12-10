#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>
#include <QDebug>
#include <QLabel>
#include <QPicture>


class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = 0);

private:
    QVector<QPushButton*> buttons;
    QGridLayout *layout;
    QLabel *logo;

private slots:
    void quit_SLOT();
    void choose_level_SLOT();
    void play_SLOT();
    void help_SLOT();

signals:
    void play_SIGNAL();
    void choose_level_SIGNAL();
    void quit_SIGNAL();
    void help_SIGNAL();
};

#endif // MENU_H

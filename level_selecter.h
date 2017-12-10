#ifndef LEVEL_SELECTER_H
#define LEVEL_SELECTER_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QDebug>
#include <QGridLayout>

class Level_selecter : public QWidget
{
    Q_OBJECT
public:
    Level_selecter(QWidget *parent, size_t count);

private:
    QVector<QPushButton*> buttons;
    QPushButton *back;
    QGridLayout *grid;
    size_t count;

signals:
    void selected_level(size_t number);
    void to_menu_SIGNAL();
    void play_SIGNAL();

private slots:
    void to_menu();
    void pressed();

};

#endif // LEVEL_SELECTER_H

#ifndef BONUSES_H
#define BONUSES_H

#include <QWidget>
#include <QVector>
#include <QTextEdit>
#include <QGridLayout>
#include <QStyleOption>
#include <QPushButton>
#include <cell.h>
#include <chip.h>
#include <math.h>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

class Bonuses : public QWidget
{
    Q_OBJECT
public:
    explicit Bonuses(QWidget *parent = 0);
    ~Bonuses();
private:
    QVector<QTextEdit*> blocks;
    QTextEdit *name;
    QGridLayout *grid;
    size_t current_quants;

    void createBonusesWindow();
    void paintEvent(QPaintEvent *event);
    void set_color(int color);

public slots:
    void addQuant(int color);
    void clear();
};

#endif // BONUSES_H

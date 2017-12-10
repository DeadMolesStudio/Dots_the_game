#ifndef SELECTER_H
#define SELECTER_H

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

class Selecter : public QWidget
{
    Q_OBJECT
public:
    explicit Selecter(QWidget *parent = 0);

    ~Selecter();

private:
    QVector<QPushButton*> buttons;
    QGridLayout *grid;

    void createSelecterWindow();
    void paintEvent(QPaintEvent *event);



private slots:
    void line_clicked();
    void random_clicked();
    void color_clicked();

signals:
    void selected(int bonus);
};

#endif // SELECTER_H

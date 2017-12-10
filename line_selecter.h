#ifndef LINE_SELECTER_H
#define LINE_SELECTER_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QVBoxLayout>
#include <QDebug>

class Line_selecter : public QWidget
{
    Q_OBJECT
public:
    Line_selecter(QWidget *parent, size_t rows, QSize field_size);
private:
    QVector<QPushButton*> lines;
    size_t rows;
    QVBoxLayout *box;
private slots:
    void pressed();
signals:
    void choosed_line(size_t number);

};

#endif // LINE_SELECTER_H

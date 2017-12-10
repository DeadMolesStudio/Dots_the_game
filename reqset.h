#ifndef REQSET_H
#define REQSET_H

#include <QWidget>
#include <QVector>
#include <QTextEdit>
#include <QGridLayout>
#include <cell.h>
#include <chip.h>
#include "requirement.h"
#include <QString>
#include <QStyleOption>

//struct req_element
//{
//    Cell *cell;
//    QTextEdit *info;

//    req_element();
//    req_element(Chip chip, size_t left);
//    ~req_element();
//};

class ReqSet : public QWidget
{
    Q_OBJECT
public:
    explicit ReqSet(QWidget *parent = 0, QVector<Requirement> reqs = QVector<Requirement>());
    ~ReqSet();
private:
    //QVector<req_element> elems;
    QVector<Cell*> icons;
    QVector<QTextEdit*> numbers;
    QGridLayout *grid;
    QTextEdit *name;
    void create_req_Window();
    void paintEvent(QPaintEvent *event);
public slots:
    void update_info_reqs_slot(QVector<Requirement> reqs);
    void add_req(Requirement added);
};

//req_element::req_element(Chip chip, size_t left)
//{
//    cell = new Cell(0, chip, 0);
//    info = new QTextEdit(QString::number(left));

//}

//req_element::req_element()
//{
//    cell = new Cell(0, Chip(0,0),0);
//    info = new QTextEdit("vffffd");
//}

//req_element::~req_element()
//{
//    delete cell;
//    delete info;
//}

#endif // REQSET_H

#include "line_selecter.h"

Line_selecter::Line_selecter(QWidget *, size_t rows, QSize field_size)
{
    this->setFixedSize(field_size.width() + 1, field_size.height());
    box = new QVBoxLayout();
    for (size_t i = 0; i < rows; i++)
    {
        lines.append(new QPushButton(QString::number(i)));
        lines[i]->setFixedSize(field_size.width(), field_size.height()/rows - 3);
        lines[i]->setStyleSheet("QPushButton{background-color: transparent; color: transparent;} QPushButton:hover{background-color: rgba(248,248,255,200);}");
        connect(lines[i], &QPushButton::clicked, this, &Line_selecter::pressed);
//        connect(lines[i], &QPushButton::)
        box->addWidget(lines[i]);
        box->setAlignment(lines[i], Qt::AlignLeft);
        box->setAlignment(lines[i], Qt::AlignTop);

    }
    this->setLayout(box);
}

void Line_selecter::pressed()
{
    emit choosed_line(qobject_cast<QPushButton*>(sender())->text().toUInt());
    qDebug() << qobject_cast<QPushButton*>(sender())->text().toUInt();
}



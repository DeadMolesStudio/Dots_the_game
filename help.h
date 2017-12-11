#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVector>
#include <QPixmap>

class Help : public QWidget
{
    Q_OBJECT
public:
    Help(QWidget *parent = 0);
signals:
    void to_menu();
private slots:
    void to_menu_SLOT();
private:
    QGridLayout *grid;
    QVector<QLabel*> labels;
    QLabel *logo;
    QVector<QPlainTextEdit*> text;
    QPushButton *back;

};

#endif // HELP_H

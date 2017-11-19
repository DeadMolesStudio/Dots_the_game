#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    this->resize(600,600);          // Задаем размеры виджета, то есть окна
    this->setFixedSize(600,600);    // Фиксируем размеры виджета

    scene = new QGraphicsScene();   // Инициализируем графическую сцену
    //level = new Level();
    chip = new Chip_graph*[5];      // Инициализируем фишки
    for (int i = 0; i < 5; i++)
    {
        chip[i] = new Chip_graph();
    }
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали


    scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены

//    scene->addLine(-250, -250, 0, 0, QPen(Qt::blue));     //testline
//    scene->addLine(-250, 250, 0, 0, QPen(Qt::green));     //testline
    scene->addLine(-250,0,250,0, QPen(Qt::black));   // Добавляем горизонтальную линию через центр
    scene->addLine(0,-250,0,250, QPen(Qt::black));   // Добавляем вертикальную линию через центр

    for (int i = 0; i < 5; i++)
    {
        scene->addItem(chip[i]);   // Добавляем на сцену треугольник
        chip[i]->setPos(-250 + 25*i, 250 - 25*i);
    }
        // Устанавливаем треугольник в центр сцены


}

Widget::~Widget()
{
    delete []chip;
    delete ui;
}


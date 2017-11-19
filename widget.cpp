#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget*)
{
    this->resize(600,600);          // Задаем размеры виджета, то есть окна
    //this->setFixedSize(600,600);    // Фиксируем размеры виджета

    //scene = new QGraphicsScene();   // Инициализируем графическую сцену
    //level = new Level();

    createGridForChips();

//    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
      //graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали


      //scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены

//      scene->addLine(-250,0,250,0, QPen(Qt::black));   // Добавляем горизонтальную линию через центр
//      scene->addLine(0,-250,0,250, QPen(Qt::black));   // Добавляем вертикальную линию через центр

//    for (int i = 0; i < 5; i++)
//    {
//        for (int j = 0; j < 5; j++)
//        {
//            scene->addItem(cells[i][j]);   // Добавляем на сцену фишку
//            cells[i][j]->setPos(-250 + 50*i, 250 - 50*i);
//        }
//    }


}

Widget::~Widget()
{
    for (int i = 0; i < 5; i++)
        delete cells[i];

    delete [] cells;
    delete grid;
    //delete ui;
}

void Widget::slotFromChip()
{
    QMessageBox::information(this,
                                "Зафиксировано нажатие на фишку",
                              "Вы нажали на фишку!!!");
}

void Widget::createGridForChips()
{
    grid = new QGridLayout();
//    grid->setHorizontalSpacing(1);
//    grid->setVerticalSpacing(1);
//    grid->setContentsMargins(2, 2, 2, 2);

//    QPushButton ***chip = new QPushButton**[5];      // Инициализируем фишки
//    for (int i = 0; i < 5; i++)
//    {
//        chip[i] = new QPushButton*[5];
//        grid->setRowMinimumHeight(i, 10);
//        for(int j = 0; j < 5; j++)
//        {
//            grid->setColumnMinimumWidth(j, 10);
//            chip[i][j] = new QPushButton("fuck");
//            chip[i][j]->setFixedSize(50,50);
//            //connect(chip[i][j], &Chip_graph::signal1,this, &Widget::slotFromChip);
//            grid->addWidget(chip[i][j], i,j);

//        }
//    }



    cells = new Cell**[5];      // Инициализируем фишки
    for (int i = 0; i < 5; i++)
    {
        cells[i] = new Cell*[5];
        for(int j = 0; j < 5; j++)
        {
            cells[i][j] = new Cell();
            connect(cells[i][j], &Cell::signal1,this, &Widget::slotFromChip);
            grid->addWidget(cells[i][j], i,j);

        }
    }
    this->setLayout(grid);
}

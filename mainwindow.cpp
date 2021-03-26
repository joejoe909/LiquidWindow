/*
 * Programmer Aleksey Osipov
 * email: aliks-os@yandex.ru
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->showMaximized();

    this->setGeometry(200,200,800,800);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    QLabel *lab1 = new QLabel("Label1");
   // QLabel *lab2 = new QLabel("Label2");
    TContainer *con1 = new TContainer(this, QPoint(10, 10), lab1);
    TContainer *con2 = new TContainer(this, QPoint(20, 50)/*,lab2*/);


    QWidget *test = new QWidget(con2);
    test->setStyleSheet("background: green;");
    test->show();

    con2->setChildWidget(test);

}

MainWindow::~MainWindow() {
    delete ui;
}

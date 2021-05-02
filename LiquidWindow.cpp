#include "LiquidWindow.h"
#include "ui_LiquidWindow.h"

LiquidWindow::LiquidWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiquidWindow)
{
    ui->setupUi(this);
}

LiquidWindow::~LiquidWindow()
{
    delete ui;
}

#ifndef LIQUIDWINDOW_H
#define LIQUIDWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiquidWindow;
}

class LiquidWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiquidWindow(QWidget *parent = nullptr);
    ~LiquidWindow();

private:
    Ui::LiquidWindow *ui;
};

#endif // LIQUIDWINDOW_H

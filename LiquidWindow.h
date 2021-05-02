#ifndef LIQUIDWINDOW_H
#define LIQUIDWINDOW_H

#include <QWidget>

namespace Ui {
class LiquidWindow;
}

class LiquidWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LiquidWindow(QWidget *parent = nullptr);
    ~LiquidWindow();

private:
    Ui::LiquidWindow *ui;
};

#endif // LIQUIDWINDOW_H

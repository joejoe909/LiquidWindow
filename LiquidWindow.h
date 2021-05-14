/*
 * Programmer Aleksey Osipov
 * email: aliks-os@yandex.ru
 */

/*
 * Refactored into "LiquidWindow" by Joe Farrish
 * github: joejoe909
 */


#ifndef LIQUIDWINDOW_H
#define LIQUIDWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include "TitleBar.h"

enum modes{
   NONE = 0,
   MOVE = 1,
   RESIZETL = 2,
   RESIZET = 3,
   RESIZETR = 4,
   RESIZER = 5,
   RESIZEBR = 6,
   RESIZEB = 7,
   RESIZEBL = 8,
   RESIZEL = 9
};

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
QT_END_NAMESPACE

namespace Ui {
class LiquidWindow;
}

class LiquidWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiquidWindow(QWidget *parent = nullptr, QPoint *p = new QPoint);
    ~LiquidWindow();

protected:
    int mode;

    QPoint position;
    QVBoxLayout *vLayout;
    void setCursorShape(const QPoint &e_pos);
    bool eventFiler(QObject *obj, QEvent *evt);
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void moveEvent(QMoveEvent *e);
    void enterEvent(QEnterEvent *e);
    void createWindow();
    void redrawComponents();
    void createTitleBar();
    void createMainFrame();
    void checkScreen();


    //QWidget *titlebar;
    bool m_infocus;
    bool m_isEditing;
    QFrame *mainarea;


signals:
    void inFocus(bool mode);
    void outFocus(bool mode);
private:
    Ui::LiquidWindow *ui;
    QLabel *MosPos;
    QList<QScreen*> screens;
    int numOfScreens;
    QRect useableGeo;
    QScreen *currentScreen;
    TitleBar *titlebar;
    QVBoxLayout *vertLay;
};

#endif // LIQUIDWINDOW_H

/*
 * Programmer Aleksey Osipov
 * email: aliks-os@yandex.ru
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>


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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, QPoint *p = new QPoint);
  ~MainWindow();
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
    void redrawComponents();
    QWidget *titlebar;


    bool m_infocus;
    bool m_isEditing;

signals:
    void inFocus(bool mode);
    void outFocus(bool mode);

private:
    Ui::MainWindow *ui;
    QLabel *MosPos;
    QList<QScreen*> screens;
    int numOfScreens;
    QRect useableGeo;
    QScreen *currentScreen;

    void createActions();
    void createMenus();

    QMenu *testMenu1;
    QMenu *testMenu2;
    QMenu *testMenu3;

    QAction *testAction1;
    QAction *testAction2;
    QAction *testAction3;





    // QWidget interface
protected:

};

#endif // MAINWINDOW_H

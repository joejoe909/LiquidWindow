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
    void setCursorShape(const QPointF &e_pos);
    bool eventFiler(QObject *obj, QEvent *evt);
    void keyPressEvent(QKeyEvent*e);
    void focusInEvent(QFocusEvent*e);
    void focusOutEvent(QFocusEvent*e);
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    bool m_infocus;
    bool m_isEditing;

signals:
    void inFocus(bool mode);
    void outFocus(bool mode);

private:
    Ui::MainWindow *ui;
    QLabel *MosPos;
};

#endif // MAINWINDOW_H

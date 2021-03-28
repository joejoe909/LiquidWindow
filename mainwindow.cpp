/*
 * Programmer Aleksey Osipov
 * email: aliks-os@yandex.ru
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent, QPoint *p) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->showMaximized();
    setWindowFlags(Qt::CustomizeWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setGeometry(200,200,200,100);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->statusbar->setVisible(false);
    MosPos = new QLabel(this);
    MosPos->setText("uninited");
    MosPos->setGeometry(400,400,100,100);

    m_infocus = true;
    m_isEditing = true;
    this->installEventFilter(parent);



}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setCursorShape(const QPoint &e_pos)
{
    qDebug() << "setCursorShape()";
    const int diff = 8;
        if (
                //Left-Bottom
                ((e_pos.y() > y() + height() - diff) &&     //Bottom
                 (e_pos.x() < x() + diff)) ||               //Left
                //Right-Bottom
                ((e_pos.y() > y() + height() - diff) &&     //Bottom
                 (e_pos.x() > x() + width() - diff)) ||     //Right
                //Left-Top
                ((e_pos.y() < y() + diff) &&                //Top
                 (e_pos.x() < x() + diff)) ||               //Left
                //Right-Top
                ((e_pos.y() < y() + diff) &&                //Top
                 (e_pos.x() > x() + width() - diff))        //Right
                )
        {
            //Left-Bottom
            if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                    (e_pos.x() < x() + diff))               //Left
            {
                mode = RESIZEBL;
                setCursor(QCursor(Qt::SizeBDiagCursor));
            }
            //Right-Bottom
            if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                    (e_pos.x() > x() + width() - diff))     //Right
            {
                mode = RESIZEBR;
                setCursor(QCursor(Qt::SizeFDiagCursor));
            }
            //Left-Top
            if ((e_pos.y() < y() + diff) &&                 //Top
                    (e_pos.x() < x() + diff))               //Left
            {
                mode = RESIZETL;
                setCursor(QCursor(Qt::SizeFDiagCursor));
            }
            //Right-Top
            if ((e_pos.y() < y() + diff) &&                 //Top
                    (e_pos.x() > x() + width() - diff))     //Right
            {
                mode = RESIZETR;
                setCursor(QCursor(Qt::SizeBDiagCursor));
            }
        }
        // check cursor horizontal position
        else if ((e_pos.x() < x() + diff) ||                //Left
                 ((e_pos.x() > x() + width() - diff)))      //Right
        {
            if (e_pos.x() < x() + diff) {                   //Left
                setCursor(QCursor(Qt::SizeHorCursor));
                mode = RESIZEL;
            } else {                                        //Right
                setCursor(QCursor(Qt::SizeHorCursor));
                mode = RESIZER;
            }
        }
        // check cursor vertical position
        else if (((e_pos.y() > y() + height() - diff)) ||   //Bottom
                 (e_pos.y() < y() + diff))                  //Top
        {
            if (e_pos.y() < y() + diff) {                   //Top
                setCursor(QCursor(Qt::SizeVerCursor));
                mode = RESIZET;
            } else {                                        //Bottom
                setCursor(QCursor(Qt::SizeVerCursor));
                mode = RESIZEB;
            }
        } else {
                qDebug ()<< " mouse move event line 113";
            setCursor(QCursor(Qt::ArrowCursor));
            mode = MOVE;
                qDebug ()<< " mouse move event line 116";
        }

}

bool MainWindow::eventFiler(QObject *obj, QEvent *evt)
{
//    if(m_infocus){
//        //this is a good place to pain if you need to

//        return QMainWindow::eventFilter(obj,evt);
//    }
    qDebug() << "eventFilter";
    return QMainWindow::eventFilter(obj, evt);

}



void MainWindow::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "mosuePressEvent()";
     position = QPoint(e->globalPosition().x()-geometry().x(), e->globalPosition().y()-geometry().y());
     //if (!m_isEditing) return;
        // if (!m_infocus) return;
         if (e->buttons() == Qt::LeftButton) {
             qDebug() << "LeftButton event...";
             emit inFocus(true);
             qDebug() << "focus set to true";
             setCursorShape(e->globalPos());
            // return;
         }else if(e->button() == Qt::RightButton) {
             qDebug() << "RightButton event...";
             e->accept();
         }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QMainWindow::mouseReleaseEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << "mouseMoveEvent()";
    qDebug() << "parentWidget() = " << parentWidget();
    qDebug() << "X: " << e->globalPosition().x() << " Y: " << e->globalPosition().y();
    QMainWindow::mouseMoveEvent(e);
  //  if (!m_isEditing) return;
        if (!m_infocus) return;
            qDebug ()<< " mouse move event line 163  m_infocus is:" << m_infocus << "mode is: " << mode;
        if (!e->buttons() && Qt::LeftButton) {
            QPoint p = QPoint(e->x() + geometry().x(), e->y() + geometry().y());
            setCursorShape(p);
               qDebug ()<< " mouse move event line 167";
            return;
        }
    qDebug ()<< " mouse move event line 170";
        if ((mode == MOVE || mode == NONE) && e->buttons() == Qt::LeftButton) {
//                qDebug ()<< " mouse move event line 174";
              QPoint toMove = e->globalPos() - position;
//            if (toMove.x() < 0) return;
//            if (toMove.y() < 0) return;
//                qDebug ()<< " mouse move event line 178";
//            if (toMove.x() > this->width()) return;
//                qDebug ()<< " mouse move event line 180";
//            move(toMove);
//                qDebug ()<< " mouse move event line 181";
//            this->repaint();
//                qDebug ()<< " mouse move event line 184";
//            return;

            move(toMove);

        }
        /*f ((mode != MOVE) && e->buttons() && Qt::LeftButton) {
            switch (mode){
            case RESIZETL: {    //Left-Top
                int newwidth = e->globalX() - position.x() - geometry().x();
                int newheight = e->globalY() - position.y() - geometry().y();
                QPoint toMove = e->globalPos() - position;
                resize(this->geometry().width() - newwidth, this->geometry().height() - newheight);
                move(toMove.x(), toMove.y());
                break;
            }
            case RESIZETR: {    //Right-Top
                int newheight = e->globalY() - position.y() - geometry().y();
                QPoint toMove = e->globalPos() - position;
                resize(e->x(), this->geometry().height() - newheight);
                move(this->x(), toMove.y());
                break;
            }
            case RESIZEBL: {    //Left-Bottom
                int newwidth = e->globalX() - position.x() - geometry().x();
                QPoint toMove = e->globalPos() - position;
                resize(this->geometry().width() - newwidth, e->y());
                move(toMove.x(), this->y());
                break;
            }
            case RESIZEB: {     //Bottom
                resize(width(), e->y());
                break;
            }
            case RESIZEL: {     //Left
                int newwidth = e->globalX() - position.x() - geometry().x();
                QPoint toMove = e->globalPos() - position;
                resize(this->geometry().width() - newwidth, height());
                move(toMove.x(), this->y());
                break;
            }
            case RESIZET: {     //Top
                int newheight = e->globalY() - position.y() - geometry().y();
                QPoint toMove = e->globalPos() - position;
                resize(width(), this->geometry().height() - newheight);
                move(this->x(), toMove.y());
                break;
            }
            case RESIZER: {     //Right
                resize(e->x(), height());
                break;
            }
            case RESIZEBR: {    //Right-Bottom
                resize(e->x(), e->y());
                break;
            }
            }
            this->parentWidget()->repaint();
        }
    qDebug ()<< " mouse move event line 232";*/

}

void MainWindow::moveEvent(QMoveEvent *e)
{
    qDebug () << "mouse moveEvent";
    qDebug() << "X: " << e->pos().x() << " Y: " << e->pos().y();


}

void MainWindow::enterEvent(QEnterEvent *e)
{
    qDebug() << "enter event";
     qDebug() << "X: " << e->pos().x() << " Y: " << e->pos().y();

}

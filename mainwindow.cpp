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

    this->setGeometry(200,200,800,800);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setFocus();
    this->move(*p);
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

void MainWindow::setCursorShape(const QPointF &e_pos)
{
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
            setCursor(QCursor(Qt::ArrowCursor));
            mode = MOVE;
        }

}

bool MainWindow::eventFiler(QObject *obj, QEvent *evt)
{
    if(m_infocus){
        //this is a good place to pain if you need to
        return QMainWindow::eventFilter(obj,evt);
    }
    return QMainWindow::eventFilter(obj, evt);
}


void MainWindow::keyPressEvent(QKeyEvent *)
{

}

void MainWindow::focusInEvent(QFocusEvent *e)
{
    m_infocus = true;
    this->installEventFilter(this);
    this->repaint();
    emit inFocus(true);
}

void MainWindow::focusOutEvent(QFocusEvent *e)
{
    if(!m_isEditing) return;
    mode = NONE;
    emit outFocus(false);
    m_infocus = false
;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
     position = QPoint(e->globalPosition().x()-geometry().x(), e->globalPosition().y()-geometry().y());
     if (!m_isEditing) return;
         if (!m_infocus) return;
         if (e->buttons() == Qt::LeftButton) {
             qDebug() << "LeftButton event...";
             setCursorShape(e->globalPosition());
             return;
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
    qDebug() << "X: " << e->globalPosition().x() << " Y: " << e->globalPosition().y();

}

#include "LiquidWindow.h"
#include "ui_LiquidWindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QScreen>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>


LiquidWindow::LiquidWindow(QWidget *parent, QPoint *p) :
    QMainWindow(parent),
    ui(new Ui::LiquidWindow)
{
    ui->setupUi(this);
        //this->showMaximized();
        setWindowFlags(Qt::CustomizeWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        this->setMouseTracking(true);
        this->setGeometry(200,200,700,500);

       //this->setGeometry(200,200,700,500);
        ui->centralwidget->setMouseTracking(true);
        ui->centralwidget->setStyleSheet("background-color: 'orange';");
        QVBoxLayout *vertLay = new QVBoxLayout(this);
        vertLay->setSpacing(0);
        vertLay->setContentsMargins(5,5,5,5);
        ui->centralwidget->setLayout(vertLay);

        titlebar = new TitleBar(this);


        titlebar->setMaximumHeight(33);
        titlebar->setMouseTracking(true);
      //  titlebar->setGeometry(contentsRect().x()+5, contentsRect().y()+5, contentsRect().width()-10, 30);
        vertLay->addWidget(titlebar);

        mainarea = new QFrame(this);
        mainarea->setStyleSheet("background: 'blue'");
       // mainarea->setContentsMargins(0,0,0,0);
        vertLay->addWidget(mainarea);

        screens = QGuiApplication::screens();
        numOfScreens = screens.size();

        currentScreen = QGuiApplication::screenAt(geometry().center());
        qDebug() << "On screen: " << currentScreen->availableGeometry();

        m_infocus = true;
        m_isEditing = true;
        this->installEventFilter(parent);
        qDebug () << position;




}

LiquidWindow::~LiquidWindow()
{
    delete ui;
}

void LiquidWindow::setCursorShape(const QPoint &e_pos)
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
                    qDebug() << "cursor shape set to Qt::SizeBDiagCursor";
                }
                //Right-Bottom
                if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                        (e_pos.x() > x() + width() - diff))     //Right
                {
                    mode = RESIZEBR;
                    setCursor(QCursor(Qt::SizeFDiagCursor));
                    qDebug() << "cursor shape set to Qt::SizeFDiagCursor";
                }
                //Left-Top
                if ((e_pos.y() < y() + diff) &&                 //Top
                        (e_pos.x() < x() + diff))               //Left
                {
                    mode = RESIZETL;
                    setCursor(QCursor(Qt::SizeFDiagCursor));
                    qDebug() << "cursor shape set to Qt::SizeFDiagCursor";
                }
                //Right-Top
                if ((e_pos.y() < y() + diff) &&                 //Top
                        (e_pos.x() > x() + width() - diff))     //Right
                {
                    mode = RESIZETR;
                    setCursor(QCursor(Qt::SizeBDiagCursor));
                    qDebug() << "cursor shape set to Qt::SizeBDiagCursor";
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
                    qDebug() << "cursor shape set to Qt::SizeHorCursor";
                }
            }
            // check cursor vertical position
            else if (((e_pos.y() > y() + height() - diff)) ||   //Bottom
                     (e_pos.y() < y() + diff))                  //Top
            {
                if (e_pos.y() < y() + diff) {                   //Top
                    setCursor(QCursor(Qt::SizeVerCursor));
                    mode = RESIZET;
                    qDebug() << "cursor shape set to Qt::SizeGerCursor";
                } else {                                        //Bottom
                    setCursor(QCursor(Qt::SizeVerCursor));
                    mode = RESIZEB;
                    qDebug() << "cursor shape set to Qt::SizeVerCursor";
                }
            } else {

                setCursor(QCursor(Qt::ArrowCursor));

                mode = MOVE;

            }

}

bool LiquidWindow::eventFiler(QObject *obj, QEvent *evt)
{
        qDebug() << "eventFilter";
        return QMainWindow::eventFilter(obj, evt);
}

void LiquidWindow::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "mosuePressEvent()";
     position = QPoint(e->globalPosition().x()-geometry().x(), e->globalPosition().y()-geometry().y());
         if (e->buttons() == Qt::LeftButton) {
             //if
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

void LiquidWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QMainWindow::mouseReleaseEvent(e);
    currentScreen = QGuiApplication::screenAt(geometry().center());
    qDebug() << "mosueReleaseEvent - On screen: " << currentScreen->availableGeometry();
    repaint();
}

void LiquidWindow::mouseMoveEvent(QMouseEvent *e)
{
    QRect rectHld = this->geometry();
    QMainWindow::mouseMoveEvent(e);
        if (!m_infocus) return;
        if (!e->buttons() && Qt::LeftButton) {
            QPoint p = QPoint(e->x() + geometry().x(), e->y() + geometry().y());
            setCursorShape(p);
            return;
        }
        if ((mode == MOVE || mode == NONE) && e->buttons() == Qt::LeftButton) {
           currentScreen = QGuiApplication::screenAt(geometry().center());
           QPoint toMove = e->globalPos() - position;
           move(toMove);

        }
       if ((mode != MOVE) && e->buttons() && Qt::LeftButton) {
            switch (mode){
            case RESIZETL: {    //Left-Top
                 QRect newGeo(e->globalPos().x(), e->globalPos().y(), (rectHld.width() + (rectHld.x() - e->globalPosition().x())), (rectHld.height() + (rectHld.y() - e->globalPosition().y())));
                 if((newGeo.x() > currentScreen->availableGeometry().x() + 70 && newGeo.width() > 70) && (newGeo.y() >= 28 && newGeo.height() > 70)) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZETR: {    //Right-Top
                 QRect newGeo(rectHld.x(), e->globalPos().y(), (rectHld.width() + (e->x()-rectHld.width())), (rectHld.height() + (rectHld.y() - e->globalPosition().y())));
                 if((newGeo.x() > currentScreen->availableGeometry().x() + 70 && newGeo.width() > 70) && (newGeo.y() >= currentScreen->availableGeometry().y() + 28 && newGeo.height() > 70)) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZEBL: {    //Left-Bottom
                 QRect newGeo(e->globalPos().x(), rectHld.y(), (rectHld.width() + (rectHld.x() - e->globalPos().x())), (rectHld.height() + (e->y() - rectHld.height() )));
                 if((newGeo.x() > currentScreen->availableGeometry().x() + 70 && newGeo.width() > 70) && (newGeo.height() > 70)) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZEB: {     //Bottom
                  QRect newGeo(rectHld.x(), rectHld.y(), rectHld.width(), (rectHld.height() + (e->y()-rectHld.height())));
                  if(newGeo.height() > 70 ) resize(width(), newGeo.height()); this->setGeometry(newGeo);
                  return;
                  break;
            }
            case RESIZEL: {     //Left
                 QRect newGeo(e->globalPos().x(), rectHld.y(), (rectHld.width() + (rectHld.x() - e->globalPos().x())), rectHld.height());
                 currentScreen = QGuiApplication::screenAt(geometry().center());
                 if(newGeo.x() > currentScreen->availableGeometry().x() + 70 && newGeo.width() > 70) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZET: {     //Top
                 QRect newGeo(rectHld.x(), e->globalPos().y(), rectHld.width(), (rectHld.height() + (rectHld.y() - e->globalPosition().y())));
                 if((newGeo.y() >= 28) && (newGeo.height() > 70)) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZER: {     //Right
                 QRect newGeo(rectHld.x(), rectHld.y(), e->x(), rectHld.height());
                 if(newGeo.x() > currentScreen->availableGeometry().x() + 70 && newGeo.width() > 70) this->setGeometry(newGeo);
                 return;
                 break;
            }
            case RESIZEBR: {    //Right-Bottom
                 QRect newGeo(rectHld.x(), rectHld.y(), e->x(),  (rectHld.height() + (e->y()-rectHld.height())));
                 if(newGeo.width() > 90 && newGeo.height() > 70) this->setGeometry(newGeo);
                 return;
                 break;
            }
            }
            this->parentWidget()->repaint();
       }
}

void LiquidWindow::moveEvent(QMoveEvent *e)
{
    // qDebug () << "mouse moveEvent";
    // qDebug() << "X: " << e->pos().x() << " Y: " << e->pos().y();
}

void LiquidWindow::enterEvent(QEnterEvent *e)
{
    qDebug() << "enter event";
    qDebug() << "X: " << e->pos().x() << " Y: " << e->pos().y();
}

void LiquidWindow::redrawComponents()
{

}

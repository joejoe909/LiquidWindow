#include "TitleBar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QFrame>
#include <QSizePolicy>

TitleBar::TitleBar(QWidget *parent): QWidget(parent)
{

    hLayout = new QHBoxLayout(this);
    hLayout->setParent(this);
    this->setStyleSheet("background-color: 'green';");
    //this->setMouseTracking(true);
    //this->setGeometry(parent->x(), parent->y(), parent->height(), parent->width());
    hLayout->setContentsMargins(0,0,0,0);
    titlebar = new QFrame(this);
  // titlebar->setContentsMargins(2,2,2,2);
    titlebar->setStyleSheet("color: 'green';");
   // titlebar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titlebar->setMouseTracking(true);
    titleBarLayout = new QHBoxLayout();  //
    titleBarLayout->setContentsMargins(8,2,-1,0);
    titlebar->setLayout(titleBarLayout); //

    hLayout->addWidget(titlebar);

//    QLabel *anthrLbl = new QLabel(this);
//    anthrLbl->setText("this is another test");
//    anthrLbl->setStyleSheet("color: 'blue'; background: 'red';");
//    anthrLbl->setContentsMargins(5,5,-5,-5);
//    titleBarLayout->addWidget(anthrLbl);

}

void TitleBar::addWidget(QWidget *titleBarWidget)
{
    titleBarLayout->addWidget(titleBarWidget);

}

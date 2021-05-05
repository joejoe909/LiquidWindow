#include "TitleBar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QFrame>

TitleBar::TitleBar(QWidget *parent): QWidget(parent)
{

    hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    this->setStyleSheet("background-color: 'green';");
    //this->setGeometry(parent->x(), parent->y(), parent->height(), parent->width());
    //hLayout->setContentsMargins(5,5,5,5);
    hLayout->setSpacing(0);
//    QLabel *newLbl = new QLabel(this);
//    newLbl->setText("This is a test");
//    newLbl->setStyleSheet("color: 'red'; background-color: 'turquoise';");
//    newLbl->setContentsMargins(5,5,-5,-5);

    titlebar = new QFrame(this);
    //titlebar->setContentsMargins(2,2,2,2);
    titlebar->setStyleSheet("color: 'green';");
    titlebar->setMouseTracking(true);
    hLayout->addWidget(titlebar);



    //newLbl->setGeometry(parent->width()/2, parent->height()/2, 150,100);
//    hLayout->addWidget(newLbl);

//    QSpacerItem *hSpacer= new QSpacerItem(100,100, QSizePolicy::Expanding, QSizePolicy::Fixed);
//    hLayout->addItem(hSpacer);

//    QLabel *anthrLbl = new QLabel(this);
//    anthrLbl->setText("this is another test");
//    anthrLbl->setStyleSheet("color: 'blue'; background: 'red';");
//    anthrLbl->setContentsMargins(5,5,-5,-5);
//    hLayout->addWidget(anthrLbl);

}

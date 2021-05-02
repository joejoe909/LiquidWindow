#include "TitleBar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

TitleBar::TitleBar(QWidget *parent): QWidget(parent)
{

    hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    this->setStyleSheet("background-color: 'green';");
    hLayout->setContentsMargins(5,5,-5,-5);
    hLayout->setSpacing(0);
    QLabel *newLbl = new QLabel(this);
    newLbl->setText("This is a test");
    newLbl->setStyleSheet("color: 'red'; background-color: 'turquoise';");
    newLbl->setContentsMargins(5,5,-5,-5);
    //newLbl->setGeometry(parent->width()/2, parent->height()/2, 150,100);
    hLayout->addWidget(newLbl);

    QSpacerItem *hSpacer= new QSpacerItem(100,100, QSizePolicy::Expanding, QSizePolicy::Fixed);
    hLayout->addItem(hSpacer);

    QLabel *anthrLbl = new QLabel(this);
    anthrLbl->setText("this is another test");
    anthrLbl->setStyleSheet("color: 'blue'; background: 'red';");
    anthrLbl->setContentsMargins(5,5,-5,-5);
    hLayout->addWidget(anthrLbl);

}

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar(QWidget *parent = nullptr);
    QHBoxLayout *hLayout;
};

#endif // TITLEBAR_H

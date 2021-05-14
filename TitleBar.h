#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QFrame;
class intrLbl;
class QHBoxLayout;
//class UTA;
QT_END_NAMESPACE



class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar(QWidget *parent = nullptr);
    void addWidget(QWidget *titleBarWidget);

private:
    QHBoxLayout *hLayout;
    QHBoxLayout *titleBarLayout;
    QFrame *titlebar;



};

#endif // TITLEBAR_H

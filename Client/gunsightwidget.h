#ifndef GUNSIGHTWIDGET_H
#define GUNSIGHTWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGridLayout>

#include <QEvent>

class GunSightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GunSightWidget(QWidget *parent = nullptr);

    void setHAngle(double value);
    void setHorOffset(double value);
    void setVerOffset(double value);
    void setBackGround(int type);
    void setGunsightColor(int gSColor);

private:
    QPixmap gunSight;
    QGraphicsScene scene;
    QGraphicsView gv;

    QGridLayout gl;

    QPen linePen;

    QGraphicsItem *itemGunSight{} ;
    QGraphicsItem *itemVLine{} ;
    QGraphicsItem *itemHLine{} ;
    QGraphicsItem *debugRect{} ;

    const int etalonGunSightSite = 1024;
    const int centralCrossLineSize = 60;

    double hAngle = -1;
    double horCoeff {};
    double verCoeff {};

    double itemGunSightWidth;

    QString col;

private slots:

    void setSize();
    void calcGreenCross(double currWidth, double currHeight);
    bool eventFilter(QObject *, QEvent *);


};

#endif // GUNSIGHTWIDGET_H

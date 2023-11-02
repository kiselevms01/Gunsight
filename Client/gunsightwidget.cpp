#include "gunsightwidget.h"
#include <QObject>
#include <QDebug>
#include <QLine>
#include <QColor>
#include <QPen>
#include <QScrollBar>

GunSightWidget::GunSightWidget(QWidget *parent)
    : QWidget{parent}
{
    QObject::installEventFilter(this);

    /* Убираем скроллинг */
    gv.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gv.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    /*Добавляем слой и заносим на него QGraphicsView*/
    setLayout(&gl);
    gl.addWidget(&gv);


    /* Задаём сцену и отображаем QGraphicsView */
    gv.setScene(&scene);
    gv.show();

    scene.setBackgroundBrush(Qt::black);

    /* Инициализируем прицел */
    gunSight.load(":/img/crosshair red.svg");
    itemGunSight = scene.addPixmap(gunSight);

    /* Инициализируем зелёный крест в центре */
    QColor lineColor(Qt::darkGreen);
    linePen.setColor(lineColor);
    linePen.setWidth(3);

    itemVLine = scene.addLine(0,0,0,centralCrossLineSize, linePen);
    itemHLine = scene.addLine(-centralCrossLineSize/2,centralCrossLineSize/2,centralCrossLineSize/2,centralCrossLineSize/2, linePen);

}

void GunSightWidget::setHAngle(double value)
{
    hAngle = value;
    setSize();
}

void GunSightWidget::setHorOffset(double value)
{
    horCoeff = value;
    setSize();
}

void GunSightWidget::setVerOffset(double value)
{
    verCoeff = value;
    setSize();
}

void GunSightWidget::setBackGround(int type)
{
    switch (type) {
    case 0:
        scene.setBackgroundBrush(Qt::black);
        break;
    case 1:
        scene.setBackgroundBrush(Qt::white);
        break;
    case 2:
        scene.setBackgroundBrush(Qt::gray);
        break;
    }
}

void GunSightWidget::setGunsightColor(int gSColor)
{
    if(hAngle != -1)
    {
        switch (gSColor) {
        case 0:
            col = ":/img/crosshair red.svg";
            setSize();
            break;
        case 1:
            col = ":/img/crosshair black.svg";
            setSize();
            break;
        }
    }
}

void GunSightWidget::setSize()
{
    /* приводим соотношение сторон окна с прицелом */
    double currHeight = gv.height(); // выясняется новая высота graphicView
    double currWidth = (currHeight/3)*4; // высчитывается чтобы было 3 на 4 (height поменялось когда растягивали, от него уже меняем width)
    gv.setFixedWidth(currWidth); // устанавливаем

    /* Приводим положение координат к 0 QGraphicsView */
    scene.setSceneRect(gv.rect()); // приводим 0 координат в верхний левый угол виджета, так как по умолчанию
    // когда добавляем элемент на сцену и он автоматически встает в центр, размер сцены становится равным размеру прицела.
    // т.е. с помощью rect()  мы сделали квадрат scene таким же, как квадрат gv
    calcGreenCross(scene.width(),scene.height());

    /* Инициализируем прицел */
    if(itemGunSight)
        scene.removeItem(itemGunSight);
    gunSight.load(col);
    itemGunSight = scene.addPixmap(gunSight);

    /* Позиционируем прицел */
    itemGunSightWidth = (1.2/hAngle) * (scene.width()/etalonGunSightSite); // считаем реальный размер по инф. с сервера
    itemGunSight->setScale(itemGunSightWidth); // масштабируем ( коэф прицела относительно сцены)

    /* Положение прицела при нулевом смещении */
    int gunSightX = currWidth/2 - itemGunSight->boundingRect().width()/2 * itemGunSight->scale();
    int gunSightY = currHeight/2 - itemGunSight->boundingRect().height()/2 * itemGunSight->scale();
    int gunSightXDelta = scene.width()*horCoeff/2;
    int gunSightYDelta = scene.height()*verCoeff/2;

    itemGunSight->setPos(gunSightX + gunSightXDelta, gunSightY + gunSightYDelta);
}

void GunSightWidget::calcGreenCross(double currWidth, double currHeight)
{
    int xPos = currWidth/2;
    int yPos = currHeight/2 - centralCrossLineSize/2;
    itemHLine->setPos(xPos, yPos);
    itemVLine->setPos(xPos, yPos);
}

bool GunSightWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this)
    {
        if(ev->type() == QEvent::Resize)
            setSize();
    }
    return false;
}

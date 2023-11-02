#include "client.h"
#include "ui_client.h"
#include <QtSvg/QSvgRenderer>
#include <QPainter>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("Клиент");

    netClass = new Network;
    netClass->moveToThread(&thrClient);
    connect(&thrClient, &QThread::finished, netClass, &Network::deleteLater);
    connect(netClass, &Network::datagrammRead , this, &Client::writeText);
    thrClient.start();

    ui->gl->addWidget(&gw);
}

Client::~Client()
{
    thrClient.exit();
    thrClient.wait();
    delete ui;
}

void Client::writeText(QByteArray datagram)
{
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in >> str_hAngle >> str_Hor >> str_Vert;
    ui->lb_HAngle->setText("Угол камеры: " + str_hAngle + " град.");
    gw.setHAngle(str_hAngle.toDouble());
    ui->lb_Hor->setText("Отступ по горизонтали: " + str_Hor);
    gw.setHorOffset(str_Hor.toDouble());
    ui->lb_Vert->setText("Отступ по вертикали: " + str_Vert);
    gw.setVerOffset(str_Vert.toDouble());
    emit on_cBx_ScopeClr_activated(ui->cBx_ScopeClr->currentIndex());
}

void Client::on_cBx_BackColor_activated(int index)
{
    gw.setBackGround(index);
}

void Client::on_cBx_ScopeClr_activated(int index)
{
    gw.setGunsightColor(index);
}

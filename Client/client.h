#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QThread>
#include "network.h"
#include "gunsightwidget.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void writeText(QByteArray datagram);
private slots:

    void on_cBx_BackColor_activated(int index);

    void on_cBx_ScopeClr_activated(int index);

private:
    Ui::Client *ui;
    Network *netClass{};
    QString str_hAngle, str_Hor, str_Vert;
    QThread thrClient;
    GunSightWidget gw;
};
#endif // CLIENT_H

#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QThread>
#include <QString>
#include "sendclient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    void sendData();

private slots:
    void on_sld_HAngle_valueChanged();
    void on_sld_Hor_valueChanged();
    void on_sld_Vert_valueChanged();

private:
    Ui::Server *ui;

    QThread thrServ;
    SendClient *sendClient{};


signals:
    void sendDatagramm(QByteArray datagramm);
};

#endif // SERVER_H

#ifndef SENDCLIENT_H
#define SENDCLIENT_H

#include <QObject>
#include <QUdpSocket>

class SendClient : public QObject
{
    Q_OBJECT

public:
    explicit SendClient(QObject *parent = nullptr);

public slots:
    void setDatagram(QByteArray datagram);

private:
    int port;
};

#endif // SENDCLIENT_H

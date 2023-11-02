#include "sendclient.h"

SendClient::SendClient(QObject *parent) :
    QObject(parent)
{

}

void SendClient::setDatagram(QByteArray datagram)
{
    port = 2512;
    QUdpSocket socket;
    socket.writeDatagram(datagram, QHostAddress::LocalHost, port);
}

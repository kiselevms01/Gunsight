#include "network.h"

Network::Network(QObject *parent)
    : QObject{parent}
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 2512);
    connect(socket, &QUdpSocket::readyRead, this, &Network::readDatagramm);
}

void Network::readDatagramm()
{
    QByteArray datagram;

    while(socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
    }

    emit datagrammRead(datagram);
}

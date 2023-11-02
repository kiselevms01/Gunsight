#include "fromserver.h"

FromServer::FromServer(QThread *parent) : QThread(parent)
{

}

//QByteArray FromServer::datagram() const
//{
//    return m_datagram;
//}

void FromServer::run()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 2512);

    while(socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
    }
    QDataStream in(&datagram, QIODevice::ReadOnly);
    QString str_hAngel, str_Hor, str_Vert;
    in >> str_hAngel >> str_Hor >> str_Vert;
    qDebug() << str_hAngel;
    emit writeData(str_hAngel);

    emit finished();
}

//void FromServer::setDatagram(QByteArray datagram)
//{
//    if (m_datagram == datagram)
//        return;

//    m_datagram = datagram;
//    emit datagramChanged(m_datagram);
//}

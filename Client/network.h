#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);

private:
    QUdpSocket *socket;
private slots:
    void readDatagramm();
signals:
    void datagrammRead(QByteArray datagramm);
};

#endif // NETWORK_H

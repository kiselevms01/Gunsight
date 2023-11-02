#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle("Сервер");

    ui->lb_Hor->setNum(ui->sld_Hor->value()/100);
    ui->lb_Hor->setNum(ui->sld_Hor->value());
    ui->lb_Ver->setNum(ui->sld_Vert->value());

    connect(ui->pBt_Send, SIGNAL(clicked()), this, SLOT(sendData()));

    sendClient = new SendClient; // создаем экземпляр класса SendClient
    sendClient->moveToThread(&thrServ); // переводим его в поток
    connect(&thrServ, &QThread::finished, sendClient, &SendClient::deleteLater);// на случай если поток завершится, чтобы там все очистилось
    connect(this, &Server::sendDatagramm, sendClient, &SendClient::setDatagram); // соединяет основной класс с классом в потоке
    thrServ.start();
}

Server::~Server()
{
    thrServ.exit();
    thrServ.wait();
    delete ui;
}

void Server::on_sld_HAngle_valueChanged()
{
    ui->lb_HAngle->setText(QString("%1").arg(float(ui->sld_HAngle->value())/100));
}

void Server::on_sld_Hor_valueChanged()
{
    ui->lb_Hor->setText(QString("%1").arg(float(ui->sld_Hor->value())/100));
}

void Server::on_sld_Vert_valueChanged()
{
    ui->lb_Ver->setText(QString("%1").arg(float(ui->sld_Vert->value())/100));
}

void Server::sendData()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << ui->lb_HAngle->text() << ui->lb_Hor->text() << ui->lb_Ver->text();
    emit sendDatagramm(datagram);
}



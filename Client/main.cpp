#include "client.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/serverIco.png"));
    Client w;
    w.show();
    return a.exec();
}

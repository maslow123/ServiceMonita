#include <QCoreApplication>
#include "websocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    service s;
    timer t;
    websocket w;

    return a.exec();
}

#include <QCoreApplication>
#include <QDebug>
#include "testservice.h"

#include "qrpcserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestService service;
    TestServiceTwo serverTwo;

    QRpcServer server;
    server.addService(&service);
    server.addService(&serverTwo);

    bool bOk = server.start(9999,"0.0.0.0");

    qDebug() << "bOk:" << bOk;

    return a.exec();
}

#ifndef QRPCSOCKET_H
#define QRPCSOCKET_H

#include "qrpcchannel.h"

QRPC_BEGIN_NAMESPACE

class QRpcSocketPrivate;
class QRPC_EXPORT QRpcSocket : public QRpcChannel
{
    Q_OBJECT
    Q_DISABLE_COPY(QRpcSocket)
    Q_DECLARE_PRIVATE(QRpcSocket)
signals:
    void signalConnectClosed();
protected:
    QRpcSocket(QRpcSocketPrivate &dd, QObject *parent = nullptr);
    friend class QRpcServerPrivate;
};

using QRpcSocketPtr = std::shared_ptr<QRpcSocket>;

QRPC_END_NAMESPACE

#endif // QRPCSOCKET_H

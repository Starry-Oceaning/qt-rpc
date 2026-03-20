#ifndef QRPCSERVICE_H
#define QRPCSERVICE_H

#include "qrpcdefs.h"

QRPC_BEGIN_NAMESPACE

class QRPC_EXPORT QRpcService : public QObject
{
    Q_OBJECT
public:
    explicit QRpcService(QObject *parent = nullptr);
    virtual void registerRpcType();
    virtual QByteArray moduleName() const;
protected:
    QByteArray requestUrl() const;
    unsigned int channelId() const;
    QByteArray requestUserData() const;
};

QRPC_END_NAMESPACE

#endif // QRPCSERVICE_H

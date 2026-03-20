#ifndef QRPCCHANNEL_H
#define QRPCCHANNEL_H

#include "qrpccall.h"
#include "qrpcresult.h"

QRPC_BEGIN_NAMESPACE

class QRpcChannelPrivate;
class QRPC_EXPORT QRpcChannel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QRpcChannel)
    Q_DECLARE_PRIVATE(QRpcChannel)
public:
    bool isValid() const;
    void close();
    QString localaddr();
    QString peeraddr();
    template <typename... Args>
    QRpcResultCall invokeMethod(const QRpcCall &call, const Args&... args) {
        static_assert(sizeof...(Args) <= 10, "invokeMethod supports at most 10 arguments");
        QList<QGenericArgument> invokeArgs;
        invokeArgs.reserve(sizeof...(Args));
        int dummy[] = { (invokeArg(invokeArgs, args), 0 )... };
        (void)dummy;
        return invoke(call, invokeArgs);
    }
    inline QRpcResultCall invokeMethod(const QRpcCall &call) {
        QList<QGenericArgument> invokeArgs;
        return invoke(call, invokeArgs);
    }
protected:
    QRpcChannel(QRpcChannelPrivate &dd, QObject *parent = nullptr);
private:
    QRpcResultCall invoke(const QRpcCall &call, const QList<QGenericArgument> &vals);
};

QRPC_END_NAMESPACE

#endif // QRPCCHANNEL_H

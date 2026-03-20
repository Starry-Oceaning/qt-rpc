#ifndef QRPCRESULT_H
#define QRPCRESULT_H

#include "qrpcdefs.h"
#include <QVariant>
#include <QDebug>
#include <memory>

QRPC_BEGIN_NAMESPACE

struct QRpcResultCallData;
class QRPC_EXPORT QRpcResultCall
{
public:
    enum Error {
        Unknown,
        Success,
        InvokeFailed,
        Timeout,
        NetworkError,
        DeserializationFailed,
        ModuleNotFound,
        MethodNotFound,
        InvalidArgument,
        PacketTooLarge,
        BufferOverflow,
        OutOfMemory,
        TypeMismatch
    };
    QRpcResultCall();
    virtual ~QRpcResultCall() = default;
    QRpcResultCall::Error error() const;
    const QString errorString() const;
protected:
    QVariant returnValue() const;
    void translation(int);
private:
    std::shared_ptr<QRpcResultCallData> d;
    friend class QRpcChannel;
};

template<typename T>
class QRpcResult : public QRpcResultCall
{
public:
    typedef T Type;

    QRpcResult() { registered(); }
    QRpcResult(const QRpcResultCall &call)
        : QRpcResultCall(call) {
        registered();
        translation(qMetaTypeId<T>());
    }

    QRpcResult& operator=(const QRpcResultCall &other) {
        QRpcResultCall::operator=(other);
        translation(qMetaTypeId<T>());
        return *this;
    }

    template<typename U>
    QRpcResult(const QRpcResult<U> &) = delete;
    template<typename U>
    QRpcResult(QRpcResult<U> &&) = delete;
    template<typename U>
    QRpcResult& operator=(const QRpcResult<U> &) = delete;
    template<typename U>
    QRpcResult& operator=(QRpcResult<U> &&) = delete;


    Type returnValue() const {
        return qvariant_cast<Type>(QRpcResultCall::returnValue());
    }

    operator Type() const {
        return returnValue();
    }

    friend QDebug operator<<(QDebug debug, const QRpcResult<T> &result) {
        QDebugStateSaver saver(debug);
        debug << result.returnValue();
        return debug;
     }
private:
    void registered() {
        static bool registere = [](){
            qRpcRegisterMetaType<T>();
            return true;
        }();
        Q_UNUSED(registere);
    }
};

template<>
class QRpcResult<void> : public QRpcResultCall
{
public:
    QRpcResult() = default;
    QRpcResult(const QRpcResultCall &call)
        : QRpcResultCall(call) {}
    QRpcResult &operator=(const QRpcResultCall &other) {
        QRpcResultCall::operator=(other);
        return *this;
    }

    template<typename U>
    QRpcResult(const QRpcResult<U> &) = delete;
    template<typename U>
    QRpcResult(QRpcResult<U> &&) = delete;
    template<typename U>
    QRpcResult& operator=(const QRpcResult<U> &) = delete;
    template<typename U>
    QRpcResult& operator=(QRpcResult<U> &&) = delete;
};

QRPC_END_NAMESPACE

#endif // QRPCRESULT_H

#ifndef QRPCALL_H
#define QRPCALL_H

#include "qrpcglobal.h"
#include <memory>

QRPC_BEGIN_NAMESPACE

struct QRpcCallData;
class QRPC_EXPORT QRpcCall final
{
public:
    explicit QRpcCall(qint32 timeout = 30000);
    explicit QRpcCall(const QByteArray &moduleName, const QByteArray &methodName, qint32 timeout = 30000);
    ~QRpcCall();
    QRpcCall(const QRpcCall &) = delete;
    QRpcCall &operator=(const QRpcCall &) = delete;

    /*
    * 设置调用模块名称
    * @param moduleName 模块名称
    */
    void setModuleName(const QByteArray &moduleName);

    /*
    * 获取调用模块名称
    * @return
    */
    const QByteArray &moduleName() const;

    /*
    * 获取调用方法名称
    * @param moduleName 方法名称
    */
    void setMethodName(const QByteArray &methodName);

    /*
    * 设置调用方法名称
    * @return
    */
    const QByteArray &methodName() const;

    /*
    * 设置调用超时时间, 默认30s
    * @param timeout 超时时间
    */
    void setTimeout(qint32 timeout);

    /*
    * 获取调用超时时间
    * @return
    */
    const qint32 timeout() const;

    /*
    * 设置用户数据
    * @param data 用户数据
    */
    void setUserData(const QByteArray &data);

    /*
    * 获取用户数据
    * @return
    */
    const QByteArray &userData() const;

protected:
    std::unique_ptr<QRpcCallData> d;
};

QRPC_END_NAMESPACE

#endif // QRPCALL_H

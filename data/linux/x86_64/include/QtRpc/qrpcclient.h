#ifndef QRPCCLIENT_H
#define QRPCCLIENT_H

#include "qrpcchannel.h"
#include "qrpcservice.h"

QRPC_BEGIN_NAMESPACE

class QRpcService;
class QRpcClientPrivate;
class QRPC_EXPORT QRpcClient : public QRpcChannel
{
    Q_OBJECT
    Q_DISABLE_COPY(QRpcClient)
    Q_DECLARE_PRIVATE(QRpcClient)
public:
    explicit QRpcClient(QObject *parent = nullptr);

    /*
    * 启动线程池; 若不调用此接口，则每一个客户端都将开启一个独立的线程。
    * 在创建客户端之前调用，每个进程只需要调用一次，重复调用将以第一次设置为准。
    * @param num 线程数量
    */
    static bool startupThreadPool(int num = 1);

    /*
    * 清理线程池;
    * 在所有客户端都销毁后执行，否则会出现异常。
    */
    static void cleanupThreadPool();

    /*
     * 添加服务
     * @param pService 服务实例
     */
    bool addService(QRpcService *pService);

    /*
     * 移除服务
     * @param pService 服务实例
     */
    void removeService(QRpcService *pService);

    /*
    * 设置是否断线重连(默认关闭)
    * @param flag 自动重连标志
    * 提示：在调用connectToServer前设置有效;
    *      调用connectToServer后设置的在下次调用connectToServer后生效
    */
    void setAutoReconnect(bool flag);

    /*
    * 获取自动重连开启状态
    * @return
    */
    bool isAutoReconnect() const;

    /*
    * 设置心跳上报间隔,单位：ms  默认10000ms
    * @param interval 小于或等于0,不开启心跳发送
    * 提示：服务器若开启了心跳检测,客户端不上报心跳,服务器将在心跳超时后主动断开客户端连接
    *      服务器默认心跳超时为30000ms,客户端发送心跳的间隔必须小于30000ms,因为网络传输也会消耗时间.
    *      在调用connectToServer前设置有效;
    */
    void setHeartbeatInterval(int interval);

    /*
    * 获取心跳上报间隔时间,单位：ms
    * @return interval
    */
    int heartbeatInterval() const;

    /*
    * 设置心跳超时时间，单位：ms  默认30000ms
    * @param timeout 小于或等于0,不开启检测
    * 提示：开启心跳检测后,若在单位时间内没有收到客户端的数据请求,服务器将会主动断开客户端的连接.
    *      该函数在调用start之前调用
    */
    void setHeartbeatTimeout(int timeout);

    /*
    * 获取心跳超时时间,单位：ms
    * @return timeout
    */
    int heartbeatTimeout() const;

    /*
    * 设置数据包的最大长度
    * @param length 包大小
    * 提示:在调用start之前设置,不设置默认为6M
    */
    void setPackageMaxLength(unsigned int length);

    /*
    * 获取数据包的最大长度
    * @return length
    */
    unsigned int packageMaxLength() const;

    /*
    * 连接到RPC服务器
    * @param host 服务器ip
    * @param port 服务器端口
    * @param bAsync 异步连接标志,若使用异步连接,通过信号signalConnectChanged获取连接状态
    * @return
    * 提示：若开启了自动重连,调用该函数即使返回false，框架内部也会自动再次重新连接,
    *      可以通过信号signalConnectChanged获取连接状态
    */
    bool connectToServer(const char* host, quint16 port, bool bAsync = false);

    /*
    * 断开与服务器的连接
    */
    void disconnectFromServer();

signals:
    /*
     * 连接状态改变信号
     * @param isValid 连接状态
     */
    void signalConnectChanged(bool isValid);

protected:
    QRpcClient(QRpcClientPrivate &dd, QObject *parent = nullptr);
};

QRPC_END_NAMESPACE

#endif // QRPCCLIENT_H

#ifndef QRPCSERVER_H
#define QRPCSERVER_H

#include "qrpcchannel.h"
#include "qrpcservice.h"
#include "qrpcsocket.h"

QRPC_BEGIN_NAMESPACE

class QRpcServerPrivate;
class QRPC_EXPORT QRpcServer : public QRpcChannel
{
    Q_OBJECT
    Q_DISABLE_COPY(QRpcServer)
    Q_DECLARE_PRIVATE(QRpcServer)
public:
    explicit QRpcServer(QObject *parent = nullptr);

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
    * 提示:在调用start之前设置,不设置默认为10M
    */
    void setPackageMaxLength(unsigned int);

    /*
    * 获取数据包的最大长度
    * @return length
    */
    unsigned int packageMaxLength();

    /*
    * 设置通信线程池的数量；该线程池用于处理套接字的通信。若要设置工作线程池的数量请使用 QThreadPool::globalInstance()->setMaxThreadCount()
    * @param count 线程数量
    * 提示:若不设置,则获取cpu线程核心数作为工作线程数量;
    *     即使count设为0,工作线程数量也将会保持1个线程, 该接口在调用start 之前设置有效。
    */
    void setThreadPoolCount(unsigned int count);

    /*
    * 获取通信线程池数量
    * @return
    */
    unsigned int threadPoolCount() const;

    /*
     * 启动RPC服务器
     * @param port 需要绑定的端口,传0时使用随机端口
     * @param host 需要绑定的ip
     * @return
     * 提示：若RPC服务器处于运行状态,调用该接口将会失败
     */
    bool start(quint16 port, const char* host = "0.0.0.0");

    /*
     * 获取绑定的端口,当调用\see start 时端口传入为0时,可以通过该方法获取实际使用的端口.若端口无效返回0
     * @return
     */
    quint16 port();

    /*
     * RPC服务器是否处于运行状态
     * @return
     */
    bool isRuning() const;

    /*
     * 停止RPC服务器
     */
    void stop();

    /*
     * 获取连接客户端
     * * @param id 连接id
     */
    QList<QRpcSocketPtr> sockets();
    QRpcSocketPtr socket(unsigned int id);


signals:

    /*
     * 客户端连接信号
     * @param id 连接id
     * @param isConnected 连接与断开标志
     */
    void signalClientConnected(unsigned int id, bool isConnected);

protected:
    QRpcServer(QRpcServerPrivate &dd, QObject *parent = nullptr);
};

QRPC_END_NAMESPACE

#endif // QRPCSERVER_H

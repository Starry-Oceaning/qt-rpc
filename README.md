# Qt RPC Framework

## 项目简介

Qt RPC Framework 是一个基于 **C++ 和 Qt** 实现的轻量级远程过程调用（RPC）框架，用于在分布式系统或多进程系统中实现高效、简洁的服务调用。

该框架提供统一的调用接口，使开发者能够像调用本地函数一样调用远程服务，同时隐藏底层网络通信、序列化、连接管理等复杂细节。

本仓库仅提供 **预编译二进制库（如 `.so`、`.dll`）**，用于直接集成到现有项目中使用，不包含源代码。

---

## 主要特性

- 基于 **Qt C++** 开发，易于集成到 Qt 项目
- 支持 **同步 RPC 调用**
- 支持 **服务注册与调用**
- 高效的 **序列化与反序列化机制**
- 支持 **多线程并发处理**
- 模块化设计，易于扩展
- 支持 Linux / Windows 平台

---

## 典型应用场景

- 分布式服务通信
- 微服务架构
- 多进程通信
- 设备与控制系统通信
- 后端服务调用框架

---

## 目录结构

```
project
├─ data/				# 预编译库文件
│   ├─xxx平台/			# 不同操作系统平台
│   │   ├─xxx环境/		# 不同编译环境
│   │       ├─ bin/
│   │       ├─ lib/
│   │       ├─ include/
│   │       └─ mkspecs/
├─ example/              
│   ├─ client/       	#客户端调用示例
│   └─ server/		 	#服务端开发示例 
│
├─ LICENSE           	# 软件许可证
└─ README.md
```

---

## 环境要求

- C++11 或以上
- Qt 5.x
- 支持的操作系统：
  - Linux
  - Windows

---

## 集成方式

选择对应平台和编译环境的库文件，将 `bin`、`lib`、`include`、`mkspecs` 目录拷贝到 Qt 对应目录下，然后在 `.pro` 文件中使用：

```qmake
QT += qrpc
```
即可使用。

## PRC注册

注册依赖 **自定义 MOC 工具**，使用方式如下：

1. 下载对应版本的 moc 工具：[moc](https://github.com/Starry-Oceaning/qt-moc-rpc)
2. 将下载的 moc 替换 Qt 安装目录下 `bin` 目录中的现有 `moc`
3. 在编译项目时，moc 会自动生成注册代码，无需手动注册

## 示例代码

### 定义服务

```cpp
#include "qrpcservice.h" //引用rpc头文件
QRPC_USE_NAMESPACE  // 使用命名空间

class TestService : public QRpcService  // 继承QRpcService
{
    Q_OBJECT
    Q_RPC_MODULE("TestService")   // 定义模块名称
public:
	Q_INVOKABLE int add(int a, int b) {  //写在public下面的函数需要加上 'Q_INVOKABLE' 关键字
		return a + b;
	}
	
public slots:
	int sub(int a, int b) {
		return a - b;
	}

private slots:
	int mul(int a, int b) {
		return a * b;
	}

};
```
支持基础类型与大本分容器及自定义结构体。更多的示例请参考example目录下的例子,里面有相对完整的示例。

### 注册服务
```cpp
#include <QCoreApplication>

#include "qrpcserver.h" //引用rpc头文件
QRPC_USE_NAMESPACE  // 使用命名空间

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestService service; 

    QRpcServer server;
    server.addService(&service);

    bool bOk = server.start(9999,"0.0.0.0");

    return a.exec();
}

```

### 客户端调用

```cpp
#include "qrpcclient.h"  //引用rpc头文件
QRPC_USE_NAMESPACE  // 使用命名空间

QRpcClient client;
client.connectToServer("127.0.0.1", 9999);

QRpcCall call;
call.setModuleName("TestService");
call.setMethodName("add");

QRpcResult<int> result = client.invokeMethod(call, 10, 20);
int nRet = result;
qDebug() << result.error() << result.errorString() << nRet; //nRet = 30

```
支持基础类型与大本分容器及自定义结构体。更多的示例请参考example目录下的例子,里面有相对完整的示例。

## 注意事项
虽然接口支持QVariant、QVariantMap、QVariantHash这些类型，但复杂的类型需要手动注册，详细使用方式请查看example目录下的例子。<span style="color:red">强烈建议提供的接口里面不要使用含QVariant的类型</span>，因为你并不知道对方会传入一个什么样的类型，如果传入的类型你没有注册，将会引发灾难性后果，如果你必须要使用，那么请确定你确实理解了它的用法。

## 许可证

本项目采用 **Binary Software License（二进制软件许可协议）**。

- 本仓库仅提供 **二进制文件**
- 不提供源代码
- 禁止反编译、修改或重新分发

详细许可条款请参见 `LICENSE` 文件。

---

## 作者

**lucky**

---

## 免责声明

本软件按 **“AS IS”** 形式提供，不提供任何形式的明示或暗示担保，包括但不限于适销性、特定用途适用性或非侵权担保。

在任何情况下，作者或版权持有人均不对因使用或无法使用本软件而产生的任何损失承担责任。

---

## 联系方式

如果你有任何问题或建议，可以通过提交 Issue 与作者联系。

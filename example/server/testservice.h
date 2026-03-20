#ifndef TESTSERVICE_H
#define TESTSERVICE_H

#include "qrpcservice.h"

#include <QDateTime>
#include <QSize>
#include <QChar>
#include <QVariantMap>
#include <QSet>
#include <QStack>
#include <QVector>
#include <QLinkedList>
#include <QQueue>
#include <QMultiHash>
#include <QVariantMap>
#include <QVariantHash>
#include <QDebug>

QRPC_USE_NAMESPACE

using namespace std;

struct CustomizeData {
    QSet<QString> sets;
    QString     string;
    QMultiMap<int, double> mulMap;
    QPair<QByteArray, std::string> pair;

    friend inline QDataStream &operator<<(QDataStream &out, const CustomizeData &in)
    {
        out << in.sets << in.string << in.mulMap << in.pair;
        return out;
    }

    friend inline QDataStream &operator>>(QDataStream &in, CustomizeData &out)
    {
        in >> out.sets >> out.string >> out.mulMap >> out.pair;
        return in;
    }
};
Q_DECLARE_METATYPE(CustomizeData)


//typedef multimap<int, QString> MulMap;
//using UnMap = unordered_map<int, QString>;

class TestService : public QRpcService
{
    Q_OBJECT
    Q_RPC_MODULE("TestService")
public:
    TestService();
    Q_INVOKABLE void testFun1();
    Q_INVOKABLE void testFun2(int number);
    Q_INVOKABLE int testFun3(int a, int b);
    Q_INVOKABLE QChar testFun4(const QString &qString,
                                 const QByteArray &qByteArray,
                                 double dValue,
                                 float fValue,
                                 quint64 uIntValue,
                                 bool bValue,
                                 std::string cString,
                                 QDateTime dateTime,
                                 QSize size);


    Q_INVOKABLE bool testFun5(const QList<int>,
                                 const QVector<QString>,
                                 const QSet<QByteArray>,
                                 const QStack<std::string>,
                                 const QQueue<QSize>,
                                 const QMap<quint64, std::vector<int>>,
                                 const QHash<int, QString>,
                                 const QLinkedList<double>,
                                 const QMultiHash<int, QString>,
                                 const QMultiMap<QByteArray, double>);

    Q_INVOKABLE CustomizeData testFun6(const std::list<int>,
                                 const std::vector<std::string>,
                                 const std::set<double>,
                                 const std::deque<QSize>,
                                 const map<quint64, QVector<int>>,
                                 const multimap<int, QString>,
                                 const unordered_map<int, QString>);

    Q_INVOKABLE QByteArray testFun7(CustomizeData data);

public slots:
    bool testReference1(CustomizeData &data);
    bool testReference2(const QString &inStr, QHash<int, QString>& hash);

};


class TestServiceTwo : public QRpcService
{
    Q_OBJECT
    Q_RPC_MODULE("TestServiceTwo")
private slots:
    bool testVariant1(QVariant v);
    bool testVariant2(QVariantMap v);
    bool testVariant3(QVariantHash v);

private slots:
    bool testComplexVariant(QVariant v);

};

#endif // TESTSERVICE_H

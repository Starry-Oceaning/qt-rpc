#include "testservice.h"
#include <QDebug>



TestService::TestService()
{
    qRpcRegisterMetaType<QHash<QByteArray, QByteArray>>();
}

void TestService::testFun1()
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
}

void TestService::testFun2(int number)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "\t" << "number:" << number;
}

int TestService::testFun3(int a, int b)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "\t" << "a:" << a << "b:" << b;
    return  a + b;
}

QChar TestService::testFun4(const QString &qString,
                            const QByteArray &qByteArray,
                            double dValue,
                            float fValue,
                            quint64 uIntValue,
                            bool bValue,
                            std::string cString,
                            QDateTime date,
                            QSize size)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "\t" << "QString:" << qString;
    qDebug() << "\t" << "QByteArray:" << qByteArray;
    qDebug() << "\t" << "double:" << QString::number(dValue, 'f', 10);
    qDebug() << "\t" << "float:" << fValue;
    qDebug() << "\t" << "quint64:" << uIntValue;
    qDebug() << "\t" << "bool:" << bValue;
    qDebug() << "\t" << "std::string:" << cString.c_str();
    qDebug() << "\t" << "QDateTime:" << date;
    qDebug() << "\t" << "QSize:" << size;

    return QChar('a');
}

bool TestService::testFun5(const QList<int> list,
                           const QVector<QString> vec,
                           const QSet<QByteArray> set,
                           const QStack<std::string> stack,
                           const QQueue<QSize> queue,
                           const QMap<quint64, std::vector<int> > map,
                           const QHash<int, QString> hash,
                           const QLinkedList<double> linkList,
                           const QMultiHash<int, QString> mulHash,
                           const QMultiMap<QByteArray, double> mulMap)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "\t" << "QList<int>:" << list;
    qDebug() << "\t" << "QVector<QString>:" << vec;
    qDebug() << "\t" << "QSet<QByteArray>:" << set;
    qDebug() << "\t" << "QStack<std::string>:";
    for (const auto &item : stack) {
        qDebug() << "\t\t" << QString::fromStdString(item);
    }
    qDebug() << "\t" << " QQueue<QSize>:" << queue;
    qDebug() << "\t" << "QMap<quint64, std::vector<int> >:" << map;
    qDebug() << "\t" << "QHash<int, QString>:" << hash;
    qDebug() << "\t" << "QLinkedList<double>:";
    for (QLinkedListIterator<double> i(linkList); i.hasNext(); ) {
        qDebug() << "\t\t" << i.next();
    }
    qDebug() << "\t" << "QMultiHash<int, QString>:" << mulHash;
    qDebug() << "\t" << "QMultiMap<QByteArray, double>:" << mulMap;
    return true;
}

CustomizeData TestService::testFun6(const std::list<int> list,
                                    const std::vector<std::string> vec,
                                    const std::set<double> set,
                                    const std::deque<QSize> deq,
                                    const map<quint64, QVector<int> > map,
                                    const multimap<int, QString> mulMap,
                                    const unordered_map<int, QString> unMap)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "\t" << "std::list<int>:";
    for (auto v : list) {
        qDebug() << "\t\t" << v;
    }

    qDebug() << "\t" << "std::vector<std::string>:";
    for (auto v : vec) {
        qDebug() << "\t\t" << v.c_str();
    }

    qDebug() << "\t" << "std::set<double>:";
    for (auto v : set) {
        qDebug() << "\t\t" << v;
    }

    qDebug() << "\t" << "std::deque<QSize>:";
    for (auto v : deq) {
        qDebug() << "\t\t" << v;
    }

    qDebug() << "\t" << "std::map<quint64, QVector<int> >:";
    for (auto v : map) {
        qDebug() << "\t\t" << v.first << "," <<v.second;
    }

    qDebug() << "\t" << "std::multimap<int, QString>:";
    for (auto v : mulMap) {
        qDebug() << "\t\t" << v.first << "," <<v.second;
    }

    qDebug() << "\t" << "std::unordered_map<int, QString>:";
    for (auto v : unMap) {
        qDebug() << "\t\t" << v.first << "," <<v.second;
    }

    CustomizeData data;
    data.sets.insert("set1");
    data.sets.insert("set2");
    data.string = "qstring";
    data.mulMap.insert(11,20.2);
    data.mulMap.insert(11,21.2);
    data.mulMap.insert(22,30.2);
    data.mulMap.insert(22,31.2);
    data.pair.first = "bytearray";
    data.pair.second = "std::string";
    return  data;
}

QByteArray TestService::testFun7(CustomizeData data)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "sets:" << data.sets;
    qDebug() << "string:" << data.string;
    qDebug() << "mulMap:" << data.mulMap;
    qDebug() << "pair:" << data.pair.first << data.pair.second.c_str();

    return QByteArray("abcd");
}

bool TestService::testReference1(CustomizeData &data)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    data.sets.insert("set1");
    data.sets.insert("set2");
    data.string = "qstring";
    data.mulMap.insert(11,20.2);
    data.mulMap.insert(11,21.2);
    data.mulMap.insert(22,30.2);
    data.mulMap.insert(22,31.2);
    data.pair.first = "bytearray";
    data.pair.second = "std::string";
    return true;
}

bool TestService::testReference2(const QString &inStr, QHash<int, QString> &hash)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "inStr:" << inStr;
    qDebug() << "hash:" << hash;

    hash[1] = "111";
    hash[2] = "222";
    hash[3] = "333";
    return true;
}

bool TestServiceTwo::testVariant1(QVariant v)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "v:" << v;
    return true;
}

bool TestServiceTwo::testVariant2(QVariantMap v)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "v:" << v;
    return true;
}

bool TestServiceTwo::testVariant3(QVariantHash v)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "v:" << v;
    return true;
}

bool TestServiceTwo::testComplexVariant(QVariant v)
{
    qDebug() << "invoke:" << __FUNCTION__ << this->channelId() << this->requestUrl();
    qDebug() << "v:" << v;
    return true;
}


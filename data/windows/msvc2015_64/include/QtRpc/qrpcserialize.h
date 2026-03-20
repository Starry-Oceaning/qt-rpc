#ifndef QSERIALIZE_H
#define QSERIALIZE_H

#include <QDataStream>
#include <array>
#include <vector>
#include <queue>
#include <string>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <deque>
#include <memory>

Q_DECLARE_METATYPE(std::string)

inline QDataStream &operator<<(QDataStream &out, const char &value)
{
    out << QChar(value);
    return out;
}

inline QDataStream &operator>>(QDataStream &in, char &value)
{
    QChar ca;
    in >> ca;
    value = ca.toLatin1();
    return in;
}

inline QDataStream &operator<<(QDataStream &out, const std::string &value)
{
    QString qStr = QString::fromStdString(value);
    out << qStr;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, std::string &value)
{
    QString qStr;
    in >> qStr;
    value = qStr.toStdString();
    return in;
}

template <typename T, typename V>
inline QDataStream &operator<<(QDataStream &out, const std::pair<T, V> &value)
{
    out << value.first;
    out << value.second;
    return out;
}

template <typename T, typename V>
inline QDataStream &operator>>(QDataStream &in, std::pair<T, V> &value)
{
    in >> value.first;
    in >> value.second;
    return in;
}

template <typename T, size_t _Size>
inline QDataStream &operator<<(QDataStream &out, const std::array<T, _Size> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << (*it);
    }
    return out;
}

template <typename T, size_t _Size>
inline QDataStream &operator>>(QDataStream &in, std::array<T, _Size> &value)
{
    size_t index = 0;
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i){
        T tmp;
        in >> tmp;
        if (index < _Size)
        {
            value[index] = tmp;
        }
        ++index;
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::vector<T> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << (*it);
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::vector<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i){
        T tmp;
        in >> tmp;
        value.push_back(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::queue<T> &value)
{
    std::queue<T> tmpQueue = value;
    int size = (int)value.size();
    out << size;
    while (!tmpQueue.empty())
    {
        T tmp;
        tmp = tmpQueue.front();
        tmpQueue.pop();
        out << tmp;
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::queue<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i)
    {
        T tmp;
        in >> tmp;
        value.push(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::deque<T> &value)
{
    std::deque<T> tmpQueue = value;
    int size = (int)value.size();
    out << size;
    while (!tmpQueue.empty())
    {
        T tmp;
        tmp = tmpQueue.front();
        tmpQueue.pop_front();
        out << tmp;
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::deque<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i)
    {
        T tmp;
        in >> tmp;
        value.push_back(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::list<T> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << (*it);
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::list<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        value.push_back(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::set<T> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << (*it);
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::set<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        value.insert(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::multiset<T> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << (*it);
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::multiset<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        value.insert(tmp);
    }
    return in;
}

template <typename T, typename V>
inline QDataStream &operator<<(QDataStream &out, const std::map<T, V> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << it->first;
        out << it->second;
    }
    return out;
}

template <typename T, typename V>
inline QDataStream &operator>>(QDataStream &in, std::map<T, V> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T first;
        V second;
        in >> first;
        in >> second;
        std::pair<T,V> pair(first, second);
        value.insert(pair);
    }
    return in;
}

template <typename T, typename V>
inline QDataStream &operator<<(QDataStream &out, const std::multimap<T, V> &value)
{
    auto it = value.begin();
    int size = (int)value.size();
    out << size;
    for (; it != value.end(); it++)
    {
        out << it->first;
        out << it->second;
    }
    return out;
}

template <typename T, typename V>
inline QDataStream &operator>>(QDataStream &in, std::multimap<T, V> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T first;
        V second;
        in >> first;
        in >> second;
        std::pair<T,V> pair(first, second);
        value.insert(pair);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::stack<T> &value)
{
    std::stack<T> tmpStack = value;
    int size = (int)value.size();
    out << size;
    while (!tmpStack.empty())
    {
        T tmp = tmpStack.top();
        out << tmp;
        tmpStack.pop();
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::stack<T> &value)
{
    std::stack<T> tmpStack;
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        tmpStack.push(tmp);
    }
    while(!tmpStack.empty())
    {
        value.push(tmpStack.top());
        tmpStack.pop();
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::unordered_set<T> &value)
{
    int size = (int)value.size();
    out << size;
    for (const auto &item : value) {
        out << item;
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::unordered_set<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        value.insert(tmp);
    }
    return in;
}

template <typename T>
inline QDataStream &operator<<(QDataStream &out, const std::unordered_multiset<T> &value)
{
    int size = (int)value.size();
    out << size;
    for (const auto &item : value) {
        out << item;
    }
    return out;
}

template <typename T>
inline QDataStream &operator>>(QDataStream &in, std::unordered_multiset<T> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        T tmp;
        in >> tmp;
        value.insert(tmp);
    }
    return in;
}

template <typename K, typename V>
inline QDataStream &operator<<(QDataStream &out, const std::unordered_map<K, V> &value)
{
    int size = (int)value.size();
    out << size;
    for (const auto &pair : value) {
        out << pair.first;
        out << pair.second;
    }
    return out;
}

template <typename K, typename V>
inline QDataStream &operator>>(QDataStream &in, std::unordered_map<K, V> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        K key;
        V val;
        in >> key;
        in >> val;
        value.insert({key, val});
    }
    return in;
}

template <typename K, typename V>
inline QDataStream &operator<<(QDataStream &out, const std::unordered_multimap<K, V> &value)
{
    int size = (int)value.size();
    out << size;
    for (const auto &pair : value) {
        out << pair.first;
        out << pair.second;
    }
    return out;
}

template <typename K, typename V>
inline QDataStream &operator>>(QDataStream &in, std::unordered_multimap<K, V> &value)
{
    int size;
    in >> size;
    for(int i = 0; i < size && !in.atEnd(); ++i) {
        K key;
        V val;
        in >> key;
        in >> val;
        value.insert({key, val});
    }
    return in;
}

inline QDataStream &operator<<(QDataStream &out, const long &value)
{
    out << qint64(value);
    return out;
}

inline QDataStream &operator>>(QDataStream &in, long &value)
{
    qint64 tmp;
    in >> tmp;
    value = static_cast<long>(tmp);
    return in;
}

Q_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(QMultiMap)
Q_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(QMultiHash)
Q_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(std::multimap)
Q_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(std::unordered_map)
Q_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(std::unordered_multimap)
Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(std::set)
Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(std::multiset)
Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(std::unordered_set)
Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(std::unordered_multiset)
Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(std::deque)

#endif // QSERIALIZE_H

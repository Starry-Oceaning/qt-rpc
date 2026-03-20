#ifndef QRPCDEFS_H
#define QRPCDEFS_H

#include <QMetaType>
#include <QVariant>
#include "qrpcglobal.h"
#include "qrpcserialize.h"

QRPC_BEGIN_NAMESPACE

#define Q_RPC_MODULE(module) \
public: \
    virtual void registerRpcType() override; \
    virtual QByteArray moduleName() const override \
        { static QByteArray name(module); return name; }

template <typename T>
inline const char* qRpcRegisterMetaType() {
    static const char* name = [] {
            const int typeId = qRegisterMetaTypeStreamOperators<T>();
            static QByteArray baseName = QMetaType::typeName(typeId);
            qRegisterMetaTypeStreamOperators<T>(QByteArray(baseName + "&").constData());
            return baseName.constData();
        }();
    return name;
}

template <typename T>
inline void qRpcRegisterMetaType(const char *aName) {
    const QByteArray baseName(aName);
    qRegisterMetaTypeStreamOperators<T>(baseName.constData());
    qRegisterMetaTypeStreamOperators<T>(QByteArray(baseName + "&").constData());
    QRPC::qRpcRegisterMetaType<T>();
}

template <typename T>
struct RefType {
    T& ref;
    explicit RefType(T& r) : ref(r) {}
};

template <typename T>
RefType<T> qReference(T& ref) { return RefType<T>(ref); }

template <typename T>
struct TypeHandler {
    using DecayedType = typename std::decay<T>::type;

    static const char* name() {
        return qRpcRegisterMetaType<DecayedType>();
    }

    static const void* data(const T& value) {
        return &value;
    }
};

template <typename T>
struct TypeHandler<RefType<T>> {
    using DecayedType = typename std::decay<T>::type;

    static const char* name() {
        static QByteArray name = QByteArray(qRpcRegisterMetaType<DecayedType>()).append('&');
        return name.constData();
    }

    static const void* data(const RefType<T>& wrapper) {
        return &wrapper.ref;
    }
};

template <class T>
int invokeArg(QList<QGenericArgument>& argsList, const T& value) {
    using Handler = typename std::conditional<std::is_same<T, RefType<typename TypeHandler<T>::DecayedType>>::value,TypeHandler<T>,TypeHandler<T>>::type;
    argsList.append(QGenericArgument(Handler::name(), Handler::data(value)));
    return 0;
}

QRPC_END_NAMESPACE

#endif // QRPCDEFS_H

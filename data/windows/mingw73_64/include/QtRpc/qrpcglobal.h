#ifndef QTRPC_GLOBAL_H
#define QTRPC_GLOBAL_H

#include <QtCore/qobjectdefs.h>

#define QRPC_BEGIN_NAMESPACE    namespace QRPC {
#define QRPC_END_NAMESPACE  }
#define QRPC_USE_NAMESPACE  using namespace QRPC;

#ifndef QT_STATIC
    #if defined(QRPC_LIBRARY)
    #  define QRPC_EXPORT Q_DECL_EXPORT
    #else
    #  define QRPC_EXPORT Q_DECL_IMPORT
    #endif
#else
#  define QRPC_EXPORT
#endif


#endif // QTRPC_GLOBAL_H

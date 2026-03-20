TEMPLATE = subdirs
CONFIG   += ordered

SUBDIRS += \
    example



QMAKE_PRE_LINK += cp $$PWD/data/* $$[QT_INSTALL_PREFIX]

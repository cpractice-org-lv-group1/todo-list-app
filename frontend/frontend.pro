QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfriend.cpp \
    addtask.cpp \
    categories.cpp \
    datafillhelper.cpp \
    form.cpp \
    friendinfo.cpp \
    logwriter.cpp \
    main.cpp \
    operations.cpp \
    registration.cpp \
    taskinfo.cpp \
    vectordata.cpp

HEADERS += \
    addfriend.h \
    addtask.h \
    categories.h \
    datafillhelper.h \
    form.h \
    friendinfo.h \
    logwriter.h \
    operations.h \
    registration.h \
    taskinfo.h \
    vectordata.h

FORMS += \
    addfriend.ui \
    addtask.ui \
    categories.ui \
    form.ui \
    friendinfo.ui \
    registration.ui \
    taskinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

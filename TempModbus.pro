QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 添加 libmodbus 头文件和库路径
INCLUDEPATH += /opt/libmodbus/install/include
LIBS += -L/opt/libmodbus/install/lib -lmodbus

# 启用多线程
CONFIG += c++17 thread
QT      += serialport
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    modbusworker.cpp \
    tempwdiget.cpp

HEADERS += \
    modbusworker.h \
    tempwdiget.h

TRANSLATIONS += \
    TempModbus_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

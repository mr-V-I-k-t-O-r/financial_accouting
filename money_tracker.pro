QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    create_report.cpp \
    employee.cpp \
    main.cpp \
    mainwindow.cpp \
    operation.cpp \
    organization.cpp \
    person.cpp \
    post.cpp \
    subject.cpp \
    type.cpp

HEADERS += \
    account.h \
    create_report.h \
    employee.h \
    mainwindow.h \
    operation.h \
    organization.h \
    person.h \
    post.h \
    subject.h \
    type.h

FORMS += \
    account.ui \
    create_report.ui \
    employee.ui \
    mainwindow.ui \
    operation.ui \
    organization.ui \
    person.ui \
    post.ui \
    subject.ui \
    type.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

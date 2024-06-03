    QT       += core gui
    QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin/addemployee.cpp \
    admin/addteacher.cpp \
    admin/admaccount.cpp \
    admin/adminadd.cpp \
    admin/users.cpp \
    admin/usersdelete.cpp \
    databasemanager.cpp \
    department/addwork.cpp \
    department/confirm.cpp \
    department/departmentaccount.cpp \
    department/listworks.cpp \
    department/readyworks.cpp \
    employee/confirmwork.cpp \
    employee/empaccount.cpp \
    employee/empprofil1.cpp \
    employee/empprofil2.cpp \
    employee/newworks.cpp \
    main.cpp \
    mainwindow.cpp \
    worksdatamanager.cpp

HEADERS += \
    admin/addemployee.h \
    admin/addteacher.h \
    admin/admaccount.h \
    admin/adminadd.h \
    admin/users.h \
    admin/usersdelete.h \
    databasemanager.h \
    department/addwork.h \
    department/confirm.h \
    department/departmentaccount.h \
    department/listworks.h \
    department/readyworks.h \
    employee/confirmwork.h \
    employee/empaccount.h \
    employee/empprofil1.h \
    employee/empprofil2.h \
    employee/newworks.h \
    mainwindow.h \
    worksdatamanager.h

FORMS += \
    admin/addemployee.ui \
    admin/addteacher.ui \
    admin/admaccount.ui \
    admin/adminadd.ui \
    admin/users.ui \
    admin/usersdelete.ui \
    department/addwork.ui \
    department/confirm.ui \
    department/departmentaccount.ui \
    department/listworks.ui \
    department/readyworks.ui \
    employee/confirmwork.ui \
    employee/empaccount.ui \
    employee/empprofil1.ui \
    employee/empprofil2.ui \
    employee/newworks.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#-------------------------------------------------
#
# Project created by QtCreator 2020-04-19T23:41:29
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
                                    QT       += charts

TARGET = demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Load.cpp \
    Store.cpp \
    searchcategorydialog.cpp \
    searchvegedialog.cpp \
    searchplantdialog.cpp \
    addvegdialog.cpp \
    addcategorydialog.cpp \
    addplantdialog.cpp \
    editcategorydialog.cpp \
    editvegdialog.cpp \
    editplantdialog.cpp \
    deletecategorydialog.cpp \
    deletevegdialog.cpp \
    deleteplantdialog.cpp \
    staticyeardialog.cpp \
    staticvegdialog.cpp \
    exportyeardialog.cpp \
    exportcategorydialog.cpp \
    exportcustomdialog.cpp

HEADERS += \
        mainwindow.h \
    struct.h \
    Load.h \
    Store.h \
    searchcategorydialog.h \
    searchvegedialog.h \
    searchplantdialog.h \
    addvegdialog.h \
    addcategorydialog.h \
    addplantdialog.h \
    editcategorydialog.h \
    editvegdialog.h \
    editplantdialog.h \
    deletecategorydialog.h \
    deletevegdialog.h \
    deleteplantdialog.h \
    staticyeardialog.h \
    staticvegdialog.h \
    exportyeardialog.h \
    exportcategorydialog.h \
    exportcustomdialog.h

FORMS += \
        mainwindow.ui \
    Load.ui \
    Store.ui \
    searchcategorydialog.ui \
    searchvegedialog.ui \
    searchplantdialog.ui \
    addvegdialog.ui \
    addcategorydialog.ui \
    addplantdialog.ui \
    editcategorydialog.ui \
    editvegdialog.ui \
    editplantdialog.ui \
    deletecategorydialog.ui \
    deletevegdialog.ui \
    deleteplantdialog.ui \
    staticyeardialog.ui \
    staticvegdialog.ui \
    exportyeardialog.ui \
    exportcategorydialog.ui \
    exportcustomdialog.ui

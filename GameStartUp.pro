QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


RC_ICONS = app.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LoadImage.cpp \
    bubblewidget.cpp \
    bulletin.cpp \
    carousel.cpp \
    main.cpp \
    home.cpp \
    managewidget.cpp \
    setting.cpp \
    topbar.cpp

HEADERS += \
    CustomCheckBox.h \
    CustomRadioButton.h \
    LoadImage.h \
    bubblewidget.h \
    bulletin.h \
    carousel.h \
    home.h \
    managewidget.h \
    setting.h \
    topbar.h

FORMS += \
    bubblewidget.ui \
    bulletin.ui \
    carousel.ui \
    home.ui \
    managewidget.ui \
    setting.ui \
    topbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

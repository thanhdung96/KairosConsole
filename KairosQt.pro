QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lcurl

INCLUDEPATH += \
    $$PWD/KairosQt/include \
    $$PWD/include

SOURCES += \
    KairosQt/src/logindialog.cpp \
    main.cpp \
    KairosQt/src/mainwindow.cpp \
    src/Dto/BaseDto.cpp \
    src/Dto/Security/ActivateDto.cpp \
    src/Dto/Security/BaseSecurityDto.cpp \
    src/Dto/Security/ChangePasswordDto.cpp \
    src/Dto/Security/LoginDto.cpp \
    src/Network/ApiHandler.cpp \
    src/Network/Helper/HTTPHeader.cpp \
    src/Network/Helper/UriBuilder.cpp \
    src/Response/BaseResponse.cpp

HEADERS += \
    KairosQt/include/logindialog.h \
    KairosQt/include/mainwindow.h \
    include/Dto/BaseDto.h \
    include/Dto/Security/ActivateDto.h \
    include/Dto/Security/BaseSecurityDto.h \
    include/Dto/Security/ChangePasswordDto.h \
    include/Dto/Security/LoginDto.h \
    include/Network/ApiHandler.h \
    include/Network/Constants/ApiConstants.h \
    include/Network/Helper/HTTPHeader.h \
    include/Network/Helper/UriBuilder.h \
    include/Network/Helper/json.hpp \
    include/Response/BaseResponse.h

FORMS += \
    KairosQt/design/logindialog.ui \
    KairosQt/design/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/creditCalculatorModel.cpp \
    Model/smartCalcModel.cpp \
    View/creditCalculatorView.cpp \
    View/graphView.cpp \
    View/smartCalcView.cpp \
    Control/smartCalcController.cpp \
    main.cpp \
    qcustomplot.cpp \

HEADERS += \
    Model/creditCalculatorModel.h \
    Model/smartCalcModel.h \
    View/creditCalculatorView.h \
    View/graphView.h \
    View/smartCalcView.h \
    Control/smartCalcController.h \
    qcustomplot.h

FORMS += \
    Ui/graphView.ui \
    Ui/smartCalcView.ui \
    Ui/creditCalculatorView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

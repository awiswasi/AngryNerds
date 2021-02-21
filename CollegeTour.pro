QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_window.cpp \
    display_colleges.cpp \
    edit_souvenirs.cpp \
    edit_universities.cpp \
    login_screen.cpp \
    main.cpp \
    college_tour.cpp \
    trip_planner.cpp

HEADERS += \
    admin_window.h \
    college_tour.h \
    display_colleges.h \
    edit_souvenirs.h \
    edit_universities.h \
    login_screen.h \
    trip_planner.h

FORMS += \
    admin_window.ui \
    collegetour.ui \
    display_colleges.ui \
    edit_souvenirs.ui \
    edit_universities.ui \
    login_screen.ui \
    trip_planner.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

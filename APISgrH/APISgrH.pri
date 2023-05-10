QT       += network sql serialport widgets

HEADERS += \
    $$PWD/APISgrH.h \
    $$PWD/singleton.h \
    $$PWD/stable.h

CONFIG          += precompile_header    #可以在项目中使用预编译头文件的支持。
#预编译
PRECOMPILED_HEADER=$$PWD/stable.h

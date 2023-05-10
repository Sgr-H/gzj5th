#include "widgetui.h"
#include <QApplication>
#include <QTextCodec>
#include "log.h"
#include "APISgrH/singleton.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThread::currentThread()->setObjectName("主线程");
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    //初始化日志
    Singleton<Log>::getInstance().init(QCoreApplication::applicationDirPath() + "/" +"etc/log.conf");
    Singleton<Log>::getInstance().debug("调试测试日志系统当中...");
    //    Log::instance()->init(QCoreApplication::applicationDirPath() + "/" +"etc/log.conf");
    //    Log::instance()->debug("调试测试日志系统当中...");
    //    Log::instance()->info("信息测试日志系统当中...");
    //    Log::instance()->warn("警告测试日志系统当中...");
    //    Log::instance()->error("错误测试日志系统当中...");
    Widgetui w;
    //    w.show();
    return a.exec();
}

#include "widgetui.h"
#include <QApplication>
#include <QTextCodec>
#include "log.h"
#include "APISgrH/singleton.h"

#include "View/date2view.h"
int main(int argc, char *argv[])
{
    //虚拟键盘
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    //当前进程为主线程
    QThread::currentThread()->setObjectName("主线程");
    //明确编码格式
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
    date2View d;
    d.show();
//    Widgetui w;
//    w.setWindowTitle(QString::fromUtf8("冠之杰网关"));
    //    w.show();
    return a.exec();
}

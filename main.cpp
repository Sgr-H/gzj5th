#include "widgetui.h"
#include <QApplication>
#include <QTextCodec>
#include "APISgrH/singleton.h"
//#include "Comm/tcpclient.h"

void createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        qDebug()<<QObject::tr("文件存在");
        return ;
    }
    //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
    }
    else{
        if(!fileName.compare("log.conf")){
          QTextStream txtOutput(tempFile);
          txtOutput << "log4j.rootLogger=all,console,File" << endl;
          txtOutput << "log4j.appender.File=org.apache.log4j.RollingFileAppender" << endl;
          txtOutput << "#log4j.appender.File.Encoding=UTF-8" << endl;
          txtOutput << "log4j.appender.File.appendFile=true" << endl;
          txtOutput << "log4j.appender.File.File=./log/log.txt" << endl;
          txtOutput << "log4j.appender.File.MaxFileSize=4096KB" << endl;
          txtOutput << "log4j.appender.File.MaxBackupIndex=7" << endl;
          txtOutput << "log4j.appender.File.layout=org.apache.log4j.PatternLayout" << endl;
          txtOutput << "log4j.appender.File.layout.ConversionPattern=%d{yyyy-MM-dd HH:mm:ss.zzz}[%t][%p] %m%n" <<endl << endl;
          txtOutput << "log4j.appender.console=org.apache.log4j.ConsoleAppender" << endl;
          txtOutput << "log4j.appender.console.target=STDOUT_TARGET" << endl;
          txtOutput << "log4j.appender.console.layout=org.apache.log4j.TTCCLayout" << endl;
          txtOutput << "log4j.appender.console.layout.dateFormat=dd.MM.yyyy hh:mm:ss.zzz" << endl;
          txtOutput << "log4j.appender.console.layout.contextPrinting=true" << endl;
        }
    }
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
    qDebug()<<tempDir.currentPath();
}

int main(int argc, char *argv[])
{
    //虚拟键盘
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    //当前进程为主线程
    QThread::currentThread()->setObjectName("主线程");
    qDebug()<<"maint tId: "<<QThread::currentThreadId();
    //明确编码格式
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    //初始化日志
    QString fileDir = QCoreApplication::applicationDirPath() + "/etc/";
    createFile(fileDir, "log.conf");
    Singleton<Log>::getInstance().init(QCoreApplication::applicationDirPath() + "/" +"etc/log.conf");
    Singleton<Log>::getInstance().debug("调试测试日志系统当中...");
    //    Log::instance()->init(QCoreApplication::applicationDirPath() + "/" +"etc/log.conf");
    //    Log::instance()->debug("调试测试日志系统当中...");
    //    Log::instance()->info("信息测试日志系统当中...");
    //    Log::instance()->warn("警告测试日志系统当中...");
    //    Log::instance()->error("错误测试日志系统当中...");

//    TcpClient d;
//    d.show();

    Widgetui w;
    w.setWindowTitle(QString::fromUtf8("冠之杰网关"));
    //    w.show();
    return a.exec();
}

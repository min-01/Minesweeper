#include "mainwindow.h"

#include <QApplication> // 包含一个应用程序类的头文件
#include <QLocale>
#include <QTranslator>

// argc命令行变量的数量，argv命令行变量的数组
int main(int argc, char *argv[])
{

    // a是应用程序对象，在Qt中，应用程序对象有且只有一个
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "saolei_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // 窗口对象
    MainWindow w;

    // 显示窗口
    w.show();
    // 让程序对象进入消息循环，代码阻塞
    return a.exec();
}

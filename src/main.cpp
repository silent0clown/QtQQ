#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //在show之前读取qss文件
    QFile qss(":/style/stylesheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("Open Success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet((style));
        qss.close();
    }
    else {
        qDebug("Open qss fail");
    }

    MainWindow w;
    w.show();
    return a.exec();
}

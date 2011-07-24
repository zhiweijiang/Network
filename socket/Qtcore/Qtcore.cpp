#include <QApplication>
#include <QtCore>
#include <QSettings>
#include <QString>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QSettings settings("akaedu.org", "mysetting");
    QString str("abcdefg");
    QStringList str1;

    str1<<"pycoming"<<"zhangyan"<<"list";

    settings.setValue("string", str);
    settings.setValue("stringlist", str1);
     settings.setValue("int", 5);
     settings.setValue("double", 3.0);

     QString getstr = settings.value("string").toString();
     QStringList getstr1 = settings.value("stringlist").toStringList();
     double getdou = settings.value("double").toDouble();
     int getint = settings.value("int").toInt();

     return a.exec();
}


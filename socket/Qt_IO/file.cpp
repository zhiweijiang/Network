#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    QFile file("test.txt");
    QString str1,str2="hello";

    if(!file.open(QIODevice::WriteOnly))
    {
        std::cerr<<"Cannot open file for writing:"
            <<qPrintable(file.errorString())<<endl;
        return 0;
    }

    QTextStream out(&file);
    out<<"THomas M.Dish:"<<334<<endl;
    file.close();

    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    in>>str1>>str2;
    file.close();
    QTextStream s(stdout);
    s<<str1<<endl<<str2<<endl;

    return 0;
}


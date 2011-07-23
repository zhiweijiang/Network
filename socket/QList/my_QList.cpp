#include <QList>
#include <stdio.h>
#include <QDebug>

int main(int argc, char ** argv)
{
    QList<int> list;
    QList<int>::iterator li;
    QList<int>::const_iterator cli;

    for(int i=0; i<10; i++)
    {
        list.insert(list.end(), i);
    }
    for(li = list.begin(); li != list.end(); li++)
    {
        qDebug()<<(*li);
        *li = *li*10;
    }
    for(cli = list.begin(); cli != list.end(); ++cli)
    {
        qDebug()<<*cli;
    }

    return 0;
}

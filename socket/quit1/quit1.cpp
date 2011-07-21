#include <QApplication>
#include <QPushButton>
#include <QFont>

int main(int argc, char ** argv)
{
    QApplication a(argc, argv);

    QPushButton quit("quit", 0);
    quit.resize(75, 30);
    quit.setFont(QFont("Times", 18, QFont::Bold));

    QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

    quit.show();

    return a.exec();
}

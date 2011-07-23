#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    setupUi(this);

    tcpSocket = new QTcpSocket(this);
  // connect(pushButton, SIGNAL(clicked()), this, SLOT(enter()));
    connect(pushButton, SIGNAL(clicked()), this, SLOT(sendMsg()));

   connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
   connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));

    tcpSocket->connectToHost(QHostAddress::LocalHost, 8000);
}

Dialog::~Dialog()
{
    delete ui;
}

/*
void Dialog::enter()
{
    buf += lineEdit -> text() + '\n';
    lineEdit->clear();

    textBrowser->setText(buf);
    textBrowser->moveCursor(QTextCursor::End);
}*/

void Dialog::sendMsg()
{
    QTextStream out(tcpSocket);
    out<<lineEdit->text()<<endl;

    lineEdit->clear();
}

void Dialog::recvMsg()
{
    if(!tcpSocket->canReadLine())
        return;

    QString responseLine;
    do{
        responseLine += tcpSocket->readLine();
    }while(tcpSocket->canReadLine());

    msgBuffer += responseLine;

    textBrowser->setText(msgBuffer);
    textBrowser->moveCursor(QTextCursor::End);
}

void Dialog::error()
{
    QMessageBox::critical(this, "socket error", tcpSocket->errorString());
    tcpSocket->close();
}

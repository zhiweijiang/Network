#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "ui_dialog.h"

/*namespace Ui
{
    class Dialog;
}*/

class Dialog : public QDialog,public Ui_Dialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    //void enter();
    void sendMsg();
    void recvMsg();
    void error();

private:
    QTcpSocket *tcpSocket;
    Ui::Dialog *ui;
    //QString buf;
    QString msgBuffer;
};

#endif // DIALOG_H

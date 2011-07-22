#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
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
    void enter();

private:
    Ui::Dialog *ui;
    QString buf;
};

#endif // DIALOG_H

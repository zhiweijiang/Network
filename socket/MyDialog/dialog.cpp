#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    setupUi(this);
    connect(pushButton, SIGNAL(clicked()), this, SLOT(enter()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::enter()
{
    buf += lineEdit -> text() + '\n';
    lineEdit->clear();

    textBrowser->setText(buf);
    textBrowser->moveCursor(QTextCursor::End);
}

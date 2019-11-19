#include "errorpopup.h"
#include "ui_errorpopup.h"

ErrorPopUp::ErrorPopUp(QWidget *parent, QString errorMessage) :
    QDialog(parent),
    ui(new Ui::ErrorPopUp)
{
    ui->setupUi(this);
    ui->textEdit->setText(errorMessage);
}

ErrorPopUp::~ErrorPopUp()
{
    delete ui;
}

void ErrorPopUp::on_pushButton_clicked()
{
    close();
}

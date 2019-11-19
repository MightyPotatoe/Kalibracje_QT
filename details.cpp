#include "details.h"
#include "ui_details.h"

details::details(RData *rka, size_t poczatek, size_t koniec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::details)
{
    ui->setupUi(this);
    QString tempString;
    tempString = QString::fromUtf8("Godzina:\tPopiol:\tWilgotność:\t\tKaloryczność:\tWysokość");
    for(size_t i = poczatek; i<=koniec;i++){
        QString read = QString::fromStdString(rka->getHour(i));
        tempString += "\n" + read;
        read = QString::number(rka->getAshes(i),'f',2);
        tempString += "\t" + read;
        read = QString::number(rka->getHumidity(i),'f',2);
        tempString += "\t" + read;
        read = QString::number(rka->getCalorific(i),'f',2);
        tempString += "\t\t" + read;
        read = QString::number(rka->getHeight(i),'f',2);
        tempString += "\t\t" + read;

    }
    ui->textBrowser->setText(tempString);
}

details::~details()
{
    delete ui;
}

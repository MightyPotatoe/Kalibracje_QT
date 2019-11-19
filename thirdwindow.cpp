#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "calculations.h"
#include "tgmath.h"
#include "details.h"


thirdWindow::thirdWindow(RData *rData, Parameters *parameters, Parameters *parametersNew, std::vector <size_t> vector_input,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdWindow)
{
    ui->setupUi(this);
    this->rData = rData;
    this->parameters = parameters;
    this->parametersNew = parametersNew;
    vector = vector_input;
    Calculations calculations(parameters->getDevice());
    std::string device = parameters->getDevice();

    //checking how many fields should stay visible
    int elements = ceil(vector.size()/2);
    for(size_t i = elements + 1; i <= 7; i++){
        QString labelName;
        QLabel *label;
        QPushButton * pushButton;
        QLineEdit * lineEdit;
        QTimeEdit * timeEdit;
        //hiding poczatek labels (1-7)
        labelName = "label_poczatek_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
         //hiding koniec labels (1-7)
        labelName = "label_koniec_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
        //hiding wysokosc labels (1-7)
        labelName = "label_wysokosc_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
        //hiding popiol labels (1-7)
        labelName = "label_popiol_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
        //hiding wilgotnosc labels (1-7)
        labelName = "label_wilgotnosc_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
        //hiding kalorycznosc labels (1-7)
        labelName = "label_kalorycznosc_" + QString::number(i);
        label = thirdWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
        //hiding wysokosc lineEdits (1-7)
        labelName = "lineEdit_wysokosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setVisible(false);
        //hiding popiol lineEdits (1-7)
        labelName = "lineEdit_popiol_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setVisible(false);
        //hiding wilgotnosc lineEdits (1-7)
        labelName = "lineEdit_wilgotnosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setVisible(false);
        //hiding kalorycznosc lineEdits (1-7)
        labelName = "lineEdit_kalorycznosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setVisible(false);
        //hiding poczatet timeEdits (1-7)
        labelName = "timeEdit_poczatek_" + QString::number(i);
        timeEdit = thirdWindow::findChild <QTimeEdit *>(labelName);
        timeEdit->setVisible(false);
        //hiding koniec timeEdits (1-7)
        labelName = "timeEdit_koniec_" + QString::number(i);
        timeEdit = thirdWindow::findChild <QTimeEdit *>(labelName);
        timeEdit->setVisible(false);
        //hiding szczegoly pushButton (1-7)
        labelName = "pushButton_szczegoly_" + QString::number(i);
        pushButton = thirdWindow::findChild <QPushButton *>(labelName);
        pushButton->setVisible(false);
    }

    //filling existing fields with R_data
    for(int i = 1; i<=elements; i++){
        QString labelName;
        QLineEdit * lineEdit;
        QTimeEdit * timeEdit;
        QString tempString;
        QTime time;
        //filling timeEditPoczatek
        tempString = QString::fromStdString(rData->getHour(vector[2*i-2]));
        labelName = "timeEdit_poczatek_" + QString::number(i);
        timeEdit = thirdWindow::findChild <QTimeEdit *>(labelName);
        timeEdit->setTime(QTime::fromString(tempString, "HH:mm:ss"));
        //filling timeEditKoniec
        tempString = QString::fromStdString(rData->getHour(vector[2*i-1]));
        labelName = "timeEdit_koniec_" + QString::number(i);
        timeEdit = thirdWindow::findChild <QTimeEdit *>(labelName);
        timeEdit->setTime(QTime::fromString(tempString, "HH:mm:ss"));
        //filling lineEdit Wysokosc
        tempString = QString::number(calculations.average(*rData,vector[2*i-2],vector[2*i-1],"wysokosc"),'f',2);
        labelName = "lineEdit_wysokosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setText(tempString);
        //filling lineEdit popiol
        tempString = QString::number(calculations.average(*rData,vector[2*i-2],vector[2*i-1],"popiol"),'f',2);
        labelName = "lineEdit_popiol_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setText(tempString);
        //filling lineEdit wilgotnosc
        tempString = QString::number(calculations.average(*rData,vector[2*i-2],vector[2*i-1],"wilgotnosc"),'f',2);
        labelName = "lineEdit_wilgotnosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setText(tempString);
        //filling lineEdit kalorycznosc
        tempString = QString::number(calculations.average(*rData,vector[2*i-2],vector[2*i-1],"kalorycznosc"),'f',2);
        labelName = "lineEdit_kalorycznosc_" + QString::number(i);
        lineEdit = thirdWindow::findChild <QLineEdit *>(labelName);
        lineEdit->setText(tempString);
    }

    ui->lineEdit_staryStdAm->setText(QString::number(parameters->getStdAm()));
    ui->lineEdit_staryStdCs->setText(QString::number(parameters->getStdCs()));
    ui->lineEdit_staryStdMoc->setText(QString::number(parameters->getStdMoc()));
    ui->lineEdit_nowyStdAm->setText(QString::number(parametersNew->getStdAm()));
    ui->lineEdit_nowyStdCs->setText(QString::number(parametersNew->getStdCs()));
    ui->lineEdit_nowyStdMoc->setText(QString::number(parametersNew->getStdMoc()));

    calculations.calculateCorrections(rData,parameters,parametersNew,vector);

    ui-> lineEdit_A0 ->setText(QString::number(parametersNew->getA0(),'t',1));
    ui-> lineEdit_A1 ->setText(QString::number(parametersNew->getA1(),'t',1));
    ui-> lineEdit_MM0 ->setText(QString::number(parametersNew->getMM0(),'t',1));
    ui-> lineEdit_MM1 ->setText(QString::number(parametersNew->getMM1(),'t',1));

    //wypelnij raport
    QString tempString = QString::fromUtf8("Godzina\tPopiol\tWilgotność\tWysokość\tKaloryczność");
    QString tempString2 = QString::fromUtf8("Godzina\tPopiol\tWilgotność\tWysokość\tKaloryczność");

    double sumAshesAll = 0;
    double sumAshesAllNew = 0;
    double sumHumidityAll =0;
    double sumHumidityAllNew =0;
    double sumHeightAll = 0;
    double sumHeightAllNew = 0;
    double sumCalAll = 0;
    double sumCalAllNew = 0;
    for(size_t i = 0; i < vector.size(); i+=2){
        double sumAshes = 0;
        double sumAshesOld = 0;
        double sumHumidity = 0;
        double sumHeight = 0;
        double sumCal = 0;
        for(size_t j = vector[i]; j <= vector[i+1]; j++){

            double Am = rData->getAm(j);
            double Cs = rData->getCs(j);
            double power = rData->getPower(j);

            tempString += "\n" + QString::fromStdString(rData->getHour(j));
            //tempString += "\t" + QString::number(calculations.calculateAshes(parameters,Am,Cs),'t',1);
            //sumAshesOld += calculations.calculateAshes(parameters,Am,Cs);
            tempString += "\t" + QString::number(rData->getAshes(j),'t',1);
            sumAshesOld += rData->getAshes(j);
            tempString += "\t" + QString::number(rData->getHumidity(j),'t',1);
            tempString += "\t" + QString::number(rData->getHeight(j),'t',1);
            tempString += "\t" + QString::number(rData->getCalorific(j),'t',1);


            tempString2 += "\n" + QString::fromStdString(rData->getHour(j));
            sumAshes += calculations.calculateAshes(parametersNew,Am,Cs);
            //tempString2 += "\t" + QString::number(obliczenia.liczPopiol(noweParametry,Am,Cs),'t',1);
            tempString2 += "\t" + QString::number(calculations.calculateAshes(parametersNew,Am,Cs),'t',1);
            sumHumidity += calculations.calculateHumidity(parametersNew,Am,Cs,power);
            tempString2 += "\t" + QString::number(calculations.calculateHumidity(parametersNew,Am,Cs,power),'t',1);
            sumHeight += calculations.calculateHeight(parametersNew,Am,Cs);
            tempString2 += "\t" + QString::number(calculations.calculateHeight(parametersNew,Am,Cs),'t',1);
            sumCal += calculations.calculateCalorific(parametersNew,Am,Cs,power);
            tempString2 += "\t" + QString::number(calculations.calculateCalorific(parametersNew,Am,Cs,power),'t',1);
        }
        tempString += "\n-----------" + QString::fromUtf8("\nŚrednia:\t") + QString::number(sumAshesOld/(vector[i+1]-vector[i]+1),'t',1);
        sumAshesAll += sumAshesOld/(vector[i+1]-vector[i]+1);
        tempString += "\t" + QString::number(calculations.average(*rData,vector[i],vector[i+1],"wilgotnosc"),'t',1);
        sumHumidityAll += calculations.average(*rData,vector[i],vector[i+1],"wilgotnosc");
        tempString += "\t" + QString::number(calculations.average(*rData,vector[i],vector[i+1],"wysokosc"),'t',1);
        sumHeightAll += calculations.average(*rData,vector[i],vector[i+1],"wysokosc");
        tempString += "\t" + QString::number(calculations.average(*rData,vector[i],vector[i+1],"kalorycznosc"),'t',1);
        sumCalAll += calculations.average(*rData,vector[i],vector[i+1],"kalorycznosc");

        tempString += "\n-----------";
        tempString2 += "\n-----------" + QString::fromUtf8("\nŚrednia:\t") + QString::number(sumAshes/(vector[i+1]-vector[i]+1),'t',1);
        sumAshesAllNew += sumAshes/(vector[i+1]-vector[i]+1);
        tempString2 += "\t" + QString::number(sumHumidity/(vector[i+1]-vector[i]+1),'t',1);
        sumHumidityAllNew += sumHumidity/(vector[i+1]-vector[i]+1);
        tempString2 += "\t" + QString::number(sumHeight/(vector[i+1]-vector[i]+1),'t',1);
        sumHeightAllNew += sumHeight/(vector[i+1]-vector[i]+1);
        tempString2 += "\t" + QString::number(sumCal/(vector[i+1]-vector[i]+1),'t',1);
        sumCalAllNew += sumCal/(vector[i+1]-vector[i]+1);
        tempString2 += "\n-----------";
    }
    ui->textBrowser->setText(tempString);
    ui->textBrowser_2->setText(tempString2);
    ui->lineEdit_popAvg->setText(QString::number(sumAshesAll/(vector.size()/2),'t',2));
    ui->lineEdit_wilgAvg->setText(QString::number(sumHumidityAll/(vector.size()/2),'t',2));
    ui->lineEdit_wysAvg->setText(QString::number(sumHeightAll/(vector.size()/2),'t',2));
    ui->lineEdit_KalAvg->setText(QString::number(sumCalAll/(vector.size()/2),'t',2));
    ui->lineEdit_popAvg_2->setText(QString::number(sumAshesAllNew/(vector.size()/2),'t',2));
    ui->lineEdit_wilgAvg_2->setText(QString::number(sumHumidityAllNew/(vector.size()/2),'t',2));
    ui->lineEdit_wysAvg_2->setText(QString::number(sumHeightAllNew/(vector.size()/2),'t',2));
    ui->lineEdit_KalAvg_2->setText(QString::number(sumCalAllNew/(vector.size()/2),'t',2));

}

thirdWindow::~thirdWindow()
{
    delete ui;
}

void thirdWindow::on_pushButton_szczegoly_1_clicked()
{
    details *e = new details(rData, vector[0], vector[1]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

void thirdWindow::on_pushButton_szczegoly_2_clicked()
{
    details *e = new details(rData, vector[2], vector[3]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

void thirdWindow::on_pushButton_szczegoly_3_clicked()
{
    details *e = new details(rData, vector[4], vector[5]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}


void thirdWindow::on_pushButton_szczegoly_4_clicked()
{
    details *e = new details(rData, vector[6], vector[7]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

void thirdWindow::on_pushButton_szczegoly_5_clicked()
{
    details *e = new details(rData, vector[8], vector[9]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

void thirdWindow::on_pushButton_szczegoly_6_clicked()
{
    details *e = new details(rData, vector[10], vector[11]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

void thirdWindow::on_pushButton_szczegoly_7_clicked()
{
    details *e = new details(rData, vector[12], vector[13]);
    e->setWindowFlags(Qt::WindowStaysOnTopHint);
    e->exec();
}

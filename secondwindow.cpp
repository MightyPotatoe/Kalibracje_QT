#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "fstream"
#include "rka.h"
#include "errorpopup.h"
#include "calculations.h"
#include "thirdwindow.h"

secondWindow::secondWindow(QWidget *parent, std::string patch, std::string urzadzenie_pass, std::string rName) :
    QMainWindow(parent),
    ui(new Ui::secondWindow)
{
    ui->setupUi(this);





    //getting data from Parametry.txt --------------------------------------------------------------------
    std::fstream file;
    std::string filename = patch + "/Parametry.txt";
    file.open(filename);

    while(!file.eof()){
        std::string lineOfText;
        getline(file, lineOfText);
        QString tempString= "";
        if(lineOfText.find("#") == std::string::npos){
            tempString = findInTextLine(lineOfText, "wspH=", 5);
            if(tempString.compare("")!=0){
                parametry->setWspH(tempString.toDouble());
                ui->label_parWspH->setText(QString::number(parametry->getWspH(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "DT_Cs=", 6);
            if(tempString.compare("")!=0){
                parametry->setDtCs(tempString.toDouble());
                ui->label_dtCs->setText(QString::number(parametry->getDtCs(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "DT_Am=", 6);
            if(tempString.compare("")!=0){
                parametry->setDtAm(tempString.toDouble());
                ui->label_dtAm->setText(QString::number(parametry->getDtAm(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "Overlap=", 8);
            if(tempString.compare("")!=0){
                parametry->setOverlap(tempString.toDouble());
                ui->label_overlap->setText(QString::number(parametry->getOverlap(),'t',2));
            }
        }
    }
    file.close();

    //getting data from Wspolczynniki.txt --------------------------------------------------------------------
    filename = patch + "/Wspolczynniki.txt";
    file.open(filename);

    while(!file.eof()){
        std::string lineOfText;
        QString tempString;
        getline(file, lineOfText);

        if(lineOfText.find("#")==std::string::npos){
            tempString = findInTextLine(lineOfText, "wspA0=", 6);
            if(tempString.compare("")!=0){
                parametry->setA0(tempString.toDouble());
                ui->label_wspA0->setText(QString::number(parametry->getA0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspA1=", 6);
            if(tempString.compare("")!=0){
                parametry->setA1(tempString.toDouble());
                ui->label_wspA1->setText(QString::number(parametry->getA1(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspA2=", 6);
            if(tempString.compare("")!=0){
                parametry->setA2(tempString.toDouble());
                ui->label_wspA2->setText(QString::number(parametry->getA2(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQ0=", 6);
            if(tempString.compare("")!=0){
                parametry->setQ0(tempString.toDouble());
                ui->label_wspQ0->setText(QString::number(parametry->getQ0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQA=", 6);
            if(tempString.compare("")!=0){
                parametry->setQA(tempString.toDouble());
                ui->label_wspQA->setText(QString::number(parametry->getQA(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQM=", 6);
            if(tempString.compare("")!=0){
                parametry->setQM(tempString.toDouble());
                ui->label_wspQM->setText(QString::number(parametry->getQM(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspM0=", 6);
            if(tempString.compare("")!=0){
                parametry->setMM0(tempString.toDouble());
                ui->label_wspMM0->setText(QString::number(parametry->getMM0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspMM1=", 7);
            if(tempString.compare("")!=0){
                parametry->setMM1(tempString.toDouble());
                ui->label_wspMM1->setText(QString::number(parametry->getMM1(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspMM2=", 7);
            if(tempString.compare("")!=0){
                parametry->setMM2(tempString.toDouble());
                ui->label_wspMM2->setText(QString::number(parametry->getMM2(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspP0=", 6);
            if(tempString.compare("")!=0){
                parametry->setP0(tempString.toDouble());
            }
            tempString = findInTextLine(lineOfText, "wspP1=", 6);
            if(tempString.compare("")!=0){
                parametry->setP1(tempString.toDouble());

            }
            tempString = findInTextLine(lineOfText, "wspP2=", 6);
            if(tempString.compare("")!=0){
                parametry->setP2(tempString.toDouble());
            }
            tempString = findInTextLine(lineOfText, "wspP3=", 6);
            if(tempString.compare("")!=0){
                parametry->setP3(tempString.toDouble());
            }

        }
    }
    file.close();

    parametry->setUrzadzenie(urzadzenie_pass);
    Rka *initR = new Rka(patch,rName,parametry->getUrzadzenie());
    daneR = initR;

    QString tempString;
    tempString = QString::number(daneR->getStdAm(0));
    parametry->setStdAm(tempString.toDouble());
    ui->label_parStdAm->setText(QString::number(parametry->getStdAm(),'t',0));

    tempString = QString::number(daneR->getStdCs(0));
    parametry->setStdCs(tempString.toDouble());
    ui->label_parStdCs->setText(QString::number(parametry->getStdCs(),'t',0));

    tempString = QString::number(daneR->getStdMoc(0));
    parametry->setStdMoc(tempString.toDouble());
    ui->label_parStdMoc->setText(QString::number(parametry->getStdMoc(),'t',0));

    Calculations obliczenia(urzadzenie);
    parametry->setPStdAm(obliczenia.calculatePAm(parametry, parametry->getStdAm(),parametry->getStdCs()));
    parametry->setPStdCs(obliczenia.calculatePCs(parametry, parametry->getStdAm(),parametry->getStdCs()));

    //hiding UI elements
    ui->line_standard->setVisible(false);
    ui->lineEdit_stdAm->setVisible(false);
    ui->lineEdit_stdCs->setVisible(false);
    ui->lineEdit_stdMoc->setVisible(false);
    ui->line_wysokosci->setVisible(false);

    for(size_t i = 1; i <= 7; i++){
        QString labelName = "radioButton_" + QString::number(i);
        QRadioButton * radioButtonlabel = secondWindow::findChild <QRadioButton *>(labelName);
        radioButtonlabel->setVisible(false);

        labelName = "lineEdit_" + QString::number(i);
        QLineEdit * lineEditabel = secondWindow::findChild <QLineEdit *>(labelName);
        lineEditabel->setVisible(false);

        labelName = "label_WysokoscStart_" + QString::number(i);
        QLabel * label = secondWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);

        labelName = "timeEdit_start_" + QString::number(i);
        QTimeEdit * timeEditLabel = secondWindow::findChild <QTimeEdit *>(labelName);
        timeEditLabel->setVisible(false);

        labelName = "label_koniec_" + QString::number(i);
        label = secondWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);

        labelName = "timeEdit_koniec_" + QString::number(i);
        timeEditLabel = secondWindow::findChild <QTimeEdit *>(labelName);
        timeEditLabel->setVisible(false);

        labelName = "label_wysokosc_" + QString::number(i);
        label = secondWindow::findChild <QLabel *>(labelName);
        label->setVisible(false);
    }
    for(size_t i = 8; i <= 9; i++){
        QString labelName = "radioButton_" + QString::number(i);
        QRadioButton * label = secondWindow::findChild <QRadioButton *>(labelName);
        label->setVisible(false);
    }

    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false); 
    ui->label_9->setVisible(false);

    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
}

secondWindow::~secondWindow()
{
    delete ui;

}

QString secondWindow::findInTextLine(std::string lineOfText, std::string whatToFind, unsigned long stringLength){
    if(lineOfText.find(whatToFind)!=std::string::npos){
        QString tempQString = QString::fromStdString(&lineOfText[lineOfText.find(whatToFind) + stringLength]);
        return tempQString;
    }
    return "";
}

void secondWindow::on_pushButton_2_clicked()
{
    QTime time1 = ui->timeEdit->time();
    QTime time2 = ui->timeEdit_2->time();
    //checking if time is correct
    if(time2.hour()*60*60+time2.minute()*60+time2.second()<=time1.hour()*60*60+time1.minute()*60+time1.second()){
        QString errorMessage = QString::fromUtf8("Błędnie podano wartości czasu");
        ErrorPopUp * w = new ErrorPopUp(this, errorMessage);
        w->exec();
    }
    else{
        pustaTasmaStart = daneR->findTimeIndex(time1);
        pustaTasmaStop = daneR->findTimeIndex(time2);
        //hiding UI elements
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->timeEdit->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        //showing UI elements
        for(size_t i = 1; i <= 9; i++){
            QString labelName = "radioButton_" + QString::number(i);
            QRadioButton * label = secondWindow::findChild <QRadioButton *>(labelName);
            label->setVisible(true);
        }
        ui->lineEdit_stdAm->setVisible(true);
        ui->line_standard->setVisible(true);
        ui->lineEdit_stdCs->setVisible(true);
        ui->lineEdit_stdMoc->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);

        Calculations obliczenia(parametry->getUrzadzenie());
        QString string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"am"));
        ui->lineEdit_stdAm->setText(string);
        string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"cs"));
        ui->lineEdit_stdCs->setText(string);
        string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"moc"));
        ui->lineEdit_stdMoc->setText(string);
        ui->pushButton_3->setVisible(true);

    }
}

void secondWindow::on_pushButton_clicked()
{
    Calculations obliczenia(parametry->getUrzadzenie());
    std::vector <size_t> indexVector = obliczenia.findEmptyBelt(*daneR);
    pustaTasmaStart = indexVector[0];
    pustaTasmaStop = indexVector[1];
    QString tempQstring = QString::fromStdString(daneR->getGodzina(indexVector[0]));
    QTime time = QTime::fromString(tempQstring,"HH:mm:ss");
    ui->timeEdit->setTime(time);
    tempQstring = QString::fromStdString(daneR->getGodzina(indexVector[1]));
    time = QTime::fromString(tempQstring,"HH:mm:ss");
    ui->timeEdit_2->setTime(time);
}

void secondWindow::on_radioButton_clicked()
{}

void secondWindow::on_radioButton_1_clicked()
{
    Calculations obliczenia(parametry->getUrzadzenie());
    QString string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"am"));
    ui->lineEdit_stdAm->setText(string);
    ui->lineEdit_stdAm->setReadOnly(true);
}

void secondWindow::on_radioButton_4_clicked()
{
    Calculations obliczenia(parametry->getUrzadzenie());
    QString string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"cs"));
    ui->lineEdit_stdCs->setText(string);
    ui->lineEdit_stdCs->setReadOnly(true);
}

void secondWindow::on_radioButton_7_clicked()
{
    Calculations obliczenia(parametry->getUrzadzenie());
    QString string = QString::number(obliczenia.standard(*daneR, pustaTasmaStart,pustaTasmaStop,"moc"));
    ui->lineEdit_stdMoc->setText(string);
    ui->lineEdit_stdMoc->setReadOnly(true);
}

void secondWindow::on_radioButton_2_clicked()
{
    QString string = QString::number(daneR->getStdAm(1));
    ui->lineEdit_stdAm->setText(string);
    ui->lineEdit_stdAm->setReadOnly(true);
}

void secondWindow::on_radioButton_5_clicked()
{
    QString string = QString::number(daneR->getStdCs(1));
    ui->lineEdit_stdCs->setText(string);
    ui->lineEdit_stdCs->setReadOnly(true);
}

void secondWindow::on_radioButton_8_clicked()
{
    QString string = QString::number(daneR->getStdMoc(1));
    ui->lineEdit_stdMoc->setText(string);
    ui->lineEdit_stdMoc->setReadOnly(true);
}

void secondWindow::on_radioButton_3_clicked()
{
    ui->lineEdit_stdAm->setReadOnly(false);
}

void secondWindow::on_radioButton_6_clicked()
{
    ui->lineEdit_stdCs->setReadOnly(false);
}

void secondWindow::on_radioButton_9_clicked()
{
    ui->lineEdit_stdMoc->setReadOnly(false);
}

void secondWindow::on_pushButton_3_clicked()
{
    Calculations obliczenia(parametry->getUrzadzenie());
    ui->lineEdit_stdAm->setReadOnly(true);
    ui->lineEdit_stdCs->setReadOnly(true);
    ui->lineEdit_stdMoc->setReadOnly(true);

    for(size_t i = 1; i <= 9; i++){
        QString labelName = "radioButton_" + QString::number(i);
        QRadioButton * label = secondWindow::findChild <QRadioButton *>(labelName);
        label->setEnabled(false);
    }

    ui->line_wysokosci->setVisible(true);
    ui->label_9->setVisible(true);
    ui->pushButton_3->setVisible(false);
    vector = obliczenia.findDifferentHeight(*daneR, parametry->getUrzadzenie());
    QString tempString;

    if(vector.size()<2){
        //error here
    }
    else{
        for(int i = 1; i<=vector.size()/2; i++){
                QString tempString;
                QString labelName = "label_WysokoscStart_" + QString::number(i);
                QLabel * label = secondWindow::findChild <QLabel *>(labelName);
                label->setVisible(true);

                labelName = "label_koniec_" + QString::number(i);
                label = secondWindow::findChild <QLabel *>(labelName);
                label->setVisible(true);

                labelName = "label_wysokosc_" + QString::number(i);
                label = secondWindow::findChild <QLabel *>(labelName);
                label->setVisible(true);

                labelName = "timeEdit_start_" + QString::number(i);
                QTimeEdit * TimeEditlabel = secondWindow::findChild <QTimeEdit *>(labelName);
                TimeEditlabel->setVisible(true);
                tempString = QString::fromStdString(daneR->getGodzina(vector[i-1]));
                TimeEditlabel->setTime(QTime::fromString(tempString, "HH:mm:ss"));

                labelName = "timeEdit_koniec_" + QString::number(i);
                TimeEditlabel = secondWindow::findChild <QTimeEdit *>(labelName);
                TimeEditlabel->setVisible(true);
                tempString = QString::fromStdString(daneR->getGodzina(vector[i]));
                TimeEditlabel->setTime(QTime::fromString(tempString,"HH:mm:ss"));

                labelName = "lineEdit_" + QString::number(i);
                QLineEdit * LineEditlabel = secondWindow::findChild <QLineEdit *>(labelName);
                LineEditlabel->setVisible(true);
                tempString = QString::number(obliczenia.average(*daneR,vector[i-1],vector[i],"wysokosc"));
                LineEditlabel->setText(tempString);
            }
    }

    ui->pushButton_4->setVisible(true);

    noweParametry = *parametry;
    tempString = ui->lineEdit_stdAm->text();
    noweParametry.setStdAm(tempString.toDouble());
    tempString = ui->lineEdit_stdCs->text();
    noweParametry.setStdCs(tempString.toDouble());
    tempString = ui->lineEdit_stdMoc->text();
    noweParametry.setStdMoc(tempString.toDouble());
    noweParametry.setPStdAm(obliczenia.calculatePAm(parametry,noweParametry.getStdAm(),noweParametry.getStdCs()));
    noweParametry.setPStdCs(obliczenia.calculatePCs(parametry,noweParametry.getStdAm(),noweParametry.getStdCs()));
}

void secondWindow::on_pushButton_4_clicked()
{
    thirdWindow *e = new thirdWindow(daneR, parametry, &noweParametry, vector);
    hide();
    e->exec();
}



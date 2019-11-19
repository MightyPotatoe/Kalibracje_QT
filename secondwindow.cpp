#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "fstream"
#include "rdata.h"
#include "errorpopup.h"
#include "calculations.h"
#include "thirdwindow.h"

secondWindow::secondWindow(QWidget *parent, std::string patch, std::string devicePass, std::string rName) :
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
                parameters->setWspH(tempString.toDouble());
                ui->label_parWspH->setText(QString::number(parameters->getWspH(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "DT_Cs=", 6);
            if(tempString.compare("")!=0){
                parameters->setDtCs(tempString.toDouble());
                ui->label_dtCs->setText(QString::number(parameters->getDtCs(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "DT_Am=", 6);
            if(tempString.compare("")!=0){
                parameters->setDtAm(tempString.toDouble());
                ui->label_dtAm->setText(QString::number(parameters->getDtAm(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "Overlap=", 8);
            if(tempString.compare("")!=0){
                parameters->setOverlap(tempString.toDouble());
                ui->label_overlap->setText(QString::number(parameters->getOverlap(),'t',2));
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
                parameters->setA0(tempString.toDouble());
                ui->label_wspA0->setText(QString::number(parameters->getA0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspA1=", 6);
            if(tempString.compare("")!=0){
                parameters->setA1(tempString.toDouble());
                ui->label_wspA1->setText(QString::number(parameters->getA1(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspA2=", 6);
            if(tempString.compare("")!=0){
                parameters->setA2(tempString.toDouble());
                ui->label_wspA2->setText(QString::number(parameters->getA2(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQ0=", 6);
            if(tempString.compare("")!=0){
                parameters->setQ0(tempString.toDouble());
                ui->label_wspQ0->setText(QString::number(parameters->getQ0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQA=", 6);
            if(tempString.compare("")!=0){
                parameters->setQA(tempString.toDouble());
                ui->label_wspQA->setText(QString::number(parameters->getQA(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspQM=", 6);
            if(tempString.compare("")!=0){
                parameters->setQM(tempString.toDouble());
                ui->label_wspQM->setText(QString::number(parameters->getQM(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspM0=", 6);
            if(tempString.compare("")!=0){
                parameters->setMM0(tempString.toDouble());
                ui->label_wspMM0->setText(QString::number(parameters->getMM0(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspMM1=", 7);
            if(tempString.compare("")!=0){
                parameters->setMM1(tempString.toDouble());
                ui->label_wspMM1->setText(QString::number(parameters->getMM1(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspMM2=", 7);
            if(tempString.compare("")!=0){
                parameters->setMM2(tempString.toDouble());
                ui->label_wspMM2->setText(QString::number(parameters->getMM2(),'t',1));
            }
            tempString = findInTextLine(lineOfText, "wspP0=", 6);
            if(tempString.compare("")!=0){
                parameters->setP0(tempString.toDouble());
            }
            tempString = findInTextLine(lineOfText, "wspP1=", 6);
            if(tempString.compare("")!=0){
                parameters->setP1(tempString.toDouble());

            }
            tempString = findInTextLine(lineOfText, "wspP2=", 6);
            if(tempString.compare("")!=0){
                parameters->setP2(tempString.toDouble());
            }
            tempString = findInTextLine(lineOfText, "wspP3=", 6);
            if(tempString.compare("")!=0){
                parameters->setP3(tempString.toDouble());
            }

        }
    }
    file.close();

    parameters->setDevice(devicePass);
    RData *initR = new RData(patch,rName,parameters->getDevice());
    rData = initR;

    QString tempString;
    tempString = QString::number(rData->getStdAm(0));
    parameters->setStdAm(tempString.toDouble());
    ui->label_parStdAm->setText(QString::number(parameters->getStdAm(),'t',0));

    tempString = QString::number(rData->getStdCs(0));
    parameters->setStdCs(tempString.toDouble());
    ui->label_parStdCs->setText(QString::number(parameters->getStdCs(),'t',0));

    tempString = QString::number(rData->getStdPower(0));
    parameters->setStdMoc(tempString.toDouble());
    ui->label_parStdMoc->setText(QString::number(parameters->getStdMoc(),'t',0));

    Calculations obliczenia(device);
    parameters->setPStdAm(obliczenia.calculatePAm(parameters, parameters->getStdAm(),parameters->getStdCs()));
    parameters->setPStdCs(obliczenia.calculatePCs(parameters, parameters->getStdAm(),parameters->getStdCs()));

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
        emptyBeltStart = rData->findTimeIndex(time1);
        emptyBeltStop = rData->findTimeIndex(time2);
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

        Calculations calculations(parameters->getDevice());
        QString string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"am"));
        ui->lineEdit_stdAm->setText(string);
        string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"cs"));
        ui->lineEdit_stdCs->setText(string);
        string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"moc"));
        ui->lineEdit_stdMoc->setText(string);
        ui->pushButton_3->setVisible(true);

    }
}

void secondWindow::on_pushButton_clicked()
{
    Calculations calculations(parameters->getDevice());
    std::vector <size_t> indexVector = calculations.findEmptyBelt(*rData);
    emptyBeltStart = indexVector[0];
    emptyBeltStop = indexVector[1];
    QString tempQstring = QString::fromStdString(rData->getHour(indexVector[0]));
    QTime time = QTime::fromString(tempQstring,"HH:mm:ss");
    ui->timeEdit->setTime(time);
    tempQstring = QString::fromStdString(rData->getHour(indexVector[1]));
    time = QTime::fromString(tempQstring,"HH:mm:ss");
    ui->timeEdit_2->setTime(time);
}

void secondWindow::on_radioButton_1_clicked()
{
    Calculations calculations(parameters->getDevice());
    QString string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"am"));
    ui->lineEdit_stdAm->setText(string);
    ui->lineEdit_stdAm->setReadOnly(true);
}

void secondWindow::on_radioButton_4_clicked()
{
    Calculations calculations(parameters->getDevice());
    QString string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"cs"));
    ui->lineEdit_stdCs->setText(string);
    ui->lineEdit_stdCs->setReadOnly(true);
}

void secondWindow::on_radioButton_7_clicked()
{
    Calculations calculations(parameters->getDevice());
    QString string = QString::number(calculations.standard(*rData, emptyBeltStart,emptyBeltStop,"moc"));
    ui->lineEdit_stdMoc->setText(string);
    ui->lineEdit_stdMoc->setReadOnly(true);
}

void secondWindow::on_radioButton_2_clicked()
{
    QString string = QString::number(rData->getStdAm(1));
    ui->lineEdit_stdAm->setText(string);
    ui->lineEdit_stdAm->setReadOnly(true);
}

void secondWindow::on_radioButton_5_clicked()
{
    QString string = QString::number(rData->getStdCs(1));
    ui->lineEdit_stdCs->setText(string);
    ui->lineEdit_stdCs->setReadOnly(true);
}

void secondWindow::on_radioButton_8_clicked()
{
    QString string = QString::number(rData->getStdPower(1));
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
    Calculations calculations(parameters->getDevice());
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
    vector = calculations.findDifferentHeight(*rData, parameters->getDevice());
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
                tempString = QString::fromStdString(rData->getHour(vector[i-1]));
                TimeEditlabel->setTime(QTime::fromString(tempString, "HH:mm:ss"));

                labelName = "timeEdit_koniec_" + QString::number(i);
                TimeEditlabel = secondWindow::findChild <QTimeEdit *>(labelName);
                TimeEditlabel->setVisible(true);
                tempString = QString::fromStdString(rData->getHour(vector[i]));
                TimeEditlabel->setTime(QTime::fromString(tempString,"HH:mm:ss"));

                labelName = "lineEdit_" + QString::number(i);
                QLineEdit * LineEditlabel = secondWindow::findChild <QLineEdit *>(labelName);
                LineEditlabel->setVisible(true);
                tempString = QString::number(calculations.average(*rData,vector[i-1],vector[i],"wysokosc"));
                LineEditlabel->setText(tempString);
            }
    }

    ui->pushButton_4->setVisible(true);

    newParameters = *parameters;
    tempString = ui->lineEdit_stdAm->text();
    newParameters.setStdAm(tempString.toDouble());
    tempString = ui->lineEdit_stdCs->text();
    newParameters.setStdCs(tempString.toDouble());
    tempString = ui->lineEdit_stdMoc->text();
    newParameters.setStdMoc(tempString.toDouble());
    newParameters.setPStdAm(calculations.calculatePAm(parameters,newParameters.getStdAm(),newParameters.getStdCs()));
    newParameters.setPStdCs(calculations.calculatePCs(parameters,newParameters.getStdAm(),newParameters.getStdCs()));
}

void secondWindow::on_pushButton_4_clicked()
{
    thirdWindow *e = new thirdWindow(rData, parameters, &newParameters, vector);
    hide();
    e->exec();
}



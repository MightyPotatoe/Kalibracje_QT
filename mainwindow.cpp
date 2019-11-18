#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDateEdit"
#include "secondwindow.h"
#include "errorpopup.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    whichStep = 0;
    ui->calendarWidget->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->proceed_button->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
/*Button 1)
 * step0: select bogdanka45;
 * step1: open file browser;
 * step2: open calender;
 * step3: proceed;
 */
{
    switch(whichStep){
        //STEP 0 - Choosing bogdanka45 as active device
        case 0:{
            urzadzenie = "bogdanka15";
            port = "12223";
            ip = "213.17.176.90";
            ui->textEdit->setText(QString::fromUtf8("Wybierz katalog w którym chcesz zapisać niezbędne do analizy dane (pliki R-ek oraz pliki z parametrami)"));
            ui->pushButton->setText(QString::fromUtf8("Wybierz katalog:"));
            ui->pushButton_bog45->setVisible(false);
            ui->pushButton_sil390->setVisible(false);
            whichStep++;
            break;
        }
        //STEP 1 - Choosing catalogue to save parameters
        case 1:{
            dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            std::string ip = "213.17.176.90";
            ui->textEdit->setText(QString::fromUtf8("Następnie wybierz dzień z którego chciałbyś pobrać pierwszą R-kę"));
            ui->pushButton->setText(QString::fromUtf8("Otwórz kalendarz:"));
            whichStep++;
            break;
        }
        //STEP 2 - Opening callender
        case 2:{
            ui->textEdit->setVisible(false);
            ui->calendarWidget->setVisible(true);
            ui->calendarWidget->setEnabled(true);
            ui->pushButton->setText(QString::fromUtf8("Wybierz datę:"));
            whichStep++;
            break;
        }
        //STEP 3 - Select date from callender and show results
        case 3:{
            date = ui->calendarWidget->selectedDate().toString("yyMMdd");

            ui->calendarWidget->setEnabled(false);
            ui->calendarWidget->setVisible(false);
            ui->textEdit->setVisible(true);
            ui->textEdit_2->setVisible(true);

            ui->textEdit->setText(QString::fromUtf8("Wybornie!! \nTeraz skopiuj poniższe linie do swojej konsoli w celu pobrania odpowiednich danych:"));

            if(port.compare("0") == 0){
                ui->textEdit_2->setText(QString::fromUtf8("scp root@") + QString::fromStdString(ip) + ":/SYSKON/etc/Wspolczynniki.txt " + dir
                        + QString::fromUtf8("\n\nscp root@") + QString::fromStdString(ip) + ":/SYSKON/etc/Parametry.txt " + dir
                        + QString::fromUtf8("\n\nscp root@") + QString::fromStdString(ip) + ":/SYSKON/DANE/R" + date + QString::fromUtf8(".txt ") + dir);
            }
            else{
                ui->textEdit_2->setText(QString::fromUtf8("scp -P ") + QString::fromStdString(port) + " root@" + QString::fromStdString(ip) + ":/SYSKON/etc/Wspolczynniki.txt " + dir
                        + QString::fromUtf8("\n\nscp -P ") + QString::fromStdString(port) + " root@" + QString::fromStdString(ip) + ":/SYSKON/etc/Parametry.txt " + dir
                        + QString::fromUtf8("\n\nscp -P ") + QString::fromStdString(port) + " root@213.17.176.90:/SYSKON/DANE/R" + date + QString::fromUtf8(".txt ") + dir);
            }

            ui->proceed_button->setVisible(true);
            ui->pushButton->setVisible(false);
            break;
        }
    }
}

void MainWindow::on_proceed_button_clicked()
{
   std::string patch = dir.toStdString();
   std::string patchParametry = patch + "/Parametry.txt";
   std::string patchWspolczyniki = patch + "/Wspolczynniki.txt";
   std::string patchRka = patch + "/R" + date.toStdString() + ".txt";
   parametersFile.open(patchParametry, std::ios::in);
   plikWspolczyniki.open(patchWspolczyniki, std::ios::in);
   plikRka.open(patchRka, std::ios::in);

   if(!parametersFile.is_open()){
       QString errorMessage = QString::fromUtf8("Nie udalo się odnaleźć pliku: ") + QString::fromStdString(patchParametry) + QString::fromUtf8("\n\nUpewnij się, że podany plik został pobrany z urządzenia lub czy znajduje się w odpowiednim katalogu, a następnie sprubój ponownie");
       ErrorPopUp * w = new ErrorPopUp(this, errorMessage);
       w->exec();
   }
   else if(!plikWspolczyniki.is_open()){
       QString errorMessage = QString::fromUtf8("Nie udalo się odnaleźć pliku: ") + QString::fromStdString(patchWspolczyniki) + QString::fromUtf8("\n\nUpewnij się, że podany plik został pobrany z urządzenia lub czy znajduje się w odpowiednim katalogu, a następnie sprubój ponownie");
       ErrorPopUp * w = new ErrorPopUp(this, errorMessage);
       w->exec();
   }
   if(!plikRka.is_open()){
       QString errorMessage = QString::fromUtf8("Nie udalo się odnaleźć pliku: ") + QString::fromStdString(patchRka) + QString::fromUtf8("\n\nUpewnij się, że podany plik został pobrany z urządzenia lub czy znajduje się w odpowiednim katalogu, a następnie sprubój ponownie");
       ErrorPopUp * w = new ErrorPopUp(this, errorMessage);
       w->exec();
   }
   else {
       std::string rName = "R" + date.toStdString() + ".txt";
       secondWindow * w = new secondWindow(this, patch, urzadzenie, rName);
       hide();
       w->show();
   }
}

void MainWindow::on_pushButton_bog45_clicked()
{
    urzadzenie = "bogdanka45";
    port = "12229";
    ip = "213.17.176.90";

    ui->textEdit->setText(QString::fromUtf8("Wybierz katalog w którym chcesz zapisać niezbędne do analizy dane (pliki R-ek oraz pliki z parametrami)"));
    ui->pushButton->setText(QString::fromUtf8("Wybierz katalog:"));
    whichStep++;

    ui->pushButton_bog45->setVisible(false);
    ui->pushButton_bog45->setEnabled(false);
    ui->pushButton_sil390->setVisible(false);
    ui->pushButton_sil390->setVisible(false);
}

void MainWindow::on_pushButton_sil390_clicked()
{
    urzadzenie = "silesia390";
    port = "0";
    ip = "10.91.16.3";

    ui->textEdit->setText(QString::fromUtf8("Wybierz katalog w którym chcesz zapisać niezbędne do analizy dane (pliki R-ek oraz pliki z parametrami)"));
    ui->pushButton->setText(QString::fromUtf8("Wybierz katalog:"));
    whichStep++;

    ui->pushButton_bog45->setVisible(false);
    ui->pushButton_bog45->setEnabled(false);
    ui->pushButton_sil390->setVisible(false);
    ui->pushButton_sil390->setVisible(false);
}

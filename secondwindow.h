#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "rka.h"
#include "parametry.h"

namespace Ui {
class secondWindow;
}

class secondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr, std::string patch = "", std::string urzadzenie_pass = "", std::string rName = "");
    ~secondWindow();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_9_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_radioButton_1_clicked();

private:
    std::vector <std::string> settings;
    Rka *daneR = new Rka("","","");
    std::string urzadzenie;
    Parametry *parametry = new Parametry(urzadzenie);
    Parametry noweParametry = Parametry(urzadzenie);

    Ui::secondWindow *ui;
    size_t pustaTasmaStart = 0;
    size_t pustaTasmaStop = 0;
    std::vector <size_t> vector;

    QString findInTextLine(std::string lineOfText, std::string whatToFind, unsigned long stringLength);

};

#endif // SECONDWINDOW_H

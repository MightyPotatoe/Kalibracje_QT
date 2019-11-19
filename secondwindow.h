#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "rdata.h"
#include "parameters.h"

namespace Ui {
class secondWindow;
}

class secondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr, std::string patch = "", std::string device_pass = "", std::string rName = "");
    ~secondWindow();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

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
    RData *rData = new RData("","","");
    std::string device;
    Parameters *parameters = new Parameters(device);
    Parameters newParameters = Parameters(device);

    Ui::secondWindow *ui;
    size_t emptyBeltStart = 0;
    size_t emptyBeltStop = 0;
    std::vector <size_t> vector;

    QString findInTextLine(std::string lineOfText, std::string whatToFind, unsigned long stringLength);

};

#endif // SECONDWINDOW_H

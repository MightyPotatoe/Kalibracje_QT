#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <rdata.h>
#include "calculations.h"
#include "parameters.h"
#include "vector"

namespace Ui {
class thirdWindow;
}

class thirdWindow : public QDialog
{
    Q_OBJECT

public:
    explicit thirdWindow(RData *rData, Parameters *parameters, Parameters *parametersNew, std::vector <size_t> vector_input, QWidget *parent = nullptr);
    ~thirdWindow();
    RData *rData;
    Parameters *parameters;
    std::vector <size_t> vector;
    Parameters *parametersNew;


private slots:
    void on_pushButton_szczegoly_1_clicked();

    void on_pushButton_szczegoly_2_clicked();

    void on_pushButton_szczegoly_3_clicked();

    void on_pushButton_szczegoly_4_clicked();

    void on_pushButton_szczegoly_5_clicked();

    void on_pushButton_szczegoly_6_clicked();

    void on_pushButton_szczegoly_7_clicked();



private:
    Ui::thirdWindow *ui;
};

#endif // THIRDWINDOW_H

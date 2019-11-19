#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QDialog>

namespace Ui {
class ErrorPopUp;
}

class ErrorPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorPopUp(QWidget *parent = nullptr, QString errorMessage = "");
    ~ErrorPopUp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorPopUp *ui;
};

#endif // ERRORPOPUP_H

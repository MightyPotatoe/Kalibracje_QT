#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include "rdata.h"
#include "vector"

namespace Ui {
class details;
}

class details : public QDialog
{
    Q_OBJECT

public:
    explicit details(RData *rka, size_t poczatek, size_t koniec, QWidget *parent = nullptr);
    ~details();

private:
    Ui::details *ui;
};

#endif // DETAILS_H

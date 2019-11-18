#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int whichStep;

    std::string urzadzenie;

    std::fstream parametersFile;
    std::fstream plikWspolczyniki;
    std::fstream plikRka;
    std::vector <std::string> settings;

    std::string port;
    std::string ip;
    std::string dateString;


    QString dir;
    QString date;

private slots:

    void on_pushButton_clicked();
    void on_proceed_button_clicked();
    void on_pushButton_bog45_clicked();
    void on_pushButton_sil390_clicked();
};

#endif // MAINWINDOW_H

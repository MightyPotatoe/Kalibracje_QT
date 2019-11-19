#ifndef RKA_H
#define RKA_H
#include <vector>
#include <string>
#include "QTime"


class RData
{
public:
    RData(std::string patch, std::string rName, std::string device);

    std::string getHour(size_t index);
    double getAshes(size_t index);
    double getHumidity(size_t index);
    double getCalorific(size_t index);
    double getHeight(size_t index);
    double getAm(size_t index);
    double getCs(size_t index);
    double getPower(size_t index);
    double getStdAm(size_t index);
    double getStdPower(size_t index);
    double getStdCs(size_t index);
    double getRunning(size_t index);
    double getPosition(size_t index);
    size_t sizeOfData();
    size_t findTimeIndex(QTime time);

private:
    std::vector <std::string> hour;
    std::vector <double> ashes;
    std::vector <double> humidity;
    std::vector <double> calorific;
    std::vector <double> height;
    std::vector <double> am;
    std::vector <double> cs;
    std::vector <double> power;
    std::vector <double> stdPower;
    std::vector <double> stdAm;
    std::vector <double> stdCs;
    std::vector <double> running;
    std::vector <double> position;
};

#endif // RKA_H

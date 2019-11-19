#ifndef OBLICZENIA_H
#define OBLICZENIA_H
#include "rdata.h"
#include "math.h"
#include "parameters.h"


class Calculations
{
public:
    Calculations(std::string deviceString);
    std::vector <size_t> findEmptyBelt(RData rData);
    double standard(RData rData, size_t indexStart, size_t indexStop, std::string whichCalculations);
    std::vector <size_t> findDifferentHeight(RData rData, std::string device);
    double average(RData rData, size_t indexBegin, size_t indexEnd, std::string whichCalculations);
    double calculateAmPos(Parameters *parameters, double Am, double Cs);
    double calculatePAm(Parameters *parameters, double Am, double Cs);
    double calculatePCs(Parameters *parameters,double Am, double Cs);
    double calculateHeight(Parameters *parameters, double Am, double Cs);
    double calculateAshes(Parameters *parameters, double Am, double Cs);
    void calculateCorrections(RData *rData,Parameters *parametersOld, Parameters *parameters, std::vector<size_t> indexVector);
    double calculateHumidity(Parameters *parameters, double Am, double Cs, double power);
    double calculateCalorific(Parameters *parameters, double Am, double Cs, double power);

private:
    std::string device;
};

#endif // OBLICZENIA_H

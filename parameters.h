#ifndef PARAMETRY_H
#define PARAMETRY_H
#include "QString"

class Parameters
{
public:
    Parameters(std::string deviceString);
    double getDtAm();
    double getDtCs();
    double getOverlap();
    double getA0();
    double getA1();
    double getA2();
    double getQ0();
    double getQA();
    double getQM();
    double getMM0();
    double getMM1();
    double getMM2();
    double getWspH();
    double getStdAm();
    double getStdCs();
    double getStdMoc();
    double getPStdAm();
    double getPStdCs();
    double getP0();
    double getP1();
    double getP2();
    double getP3();
    std::string getDevice();


    void setDtAm(double val);
    void setDtCs(double val);
    void setOverlap(double val);
    void setA0(double val);
    void setA1(double val);
    void setA2(double val);
    void setQ0(double val);
    void setQA(double val);
    void setQM(double val);
    void setMM0(double val);
    void setMM1(double val);
    void setMM2(double val);
    void setWspH(double val);
    void setStdAm(double val);
    void setStdCs(double val);
    void setPStdAm(double val);
    void setPStdCs(double val);
    void setStdMoc(double val);
    void setP0(double val);
    void setP1(double val);
    void setP2(double val);
    void setP3(double val);
    void setUrzadzenie(std::string value);


private:
    double dtAm;
    double dtCs;
    double overlap;
    double A0;
    double A1;
    double A2;
    double Q0;
    double QA;
    double QM;
    double MM0;
    double MM1;
    double MM2;
    double wspH;
    double stdAm;
    double stdCs;
    double stdMoc;
    double pStdAm = 0;
    double pStdCs = 0;
    double P0 = 0;
    double P1 = 0;
    double P2 = 0;
    double P3 = 0;
    std::string device;

};

#endif // PARAMETRY_H

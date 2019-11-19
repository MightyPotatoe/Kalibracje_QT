#include "parameters.h"
#include "calculations.h"

Parameters::Parameters(std::string deviceString)
{
    dtAm = 0;
    dtCs = 0;
    overlap = 0;
    A0 = 0;
    A1 = 0;
    A2 = 0;
    Q0 = 0;
    QA = 0;
    QM = 0;
    MM0 = 0;
    MM1 = 0;
    MM2 = 0;
    wspH = 0;
    stdAm = 0;
    stdCs = 0;
    stdMoc = 0;
    device = deviceString;
}


   double Parameters::getDtAm(){
       return dtAm;
   }

   double Parameters::getDtCs(){
       return dtCs;
   }

   double Parameters::getOverlap(){
       return overlap;
   }

   double Parameters::getA0(){
       return A0;
   }

   double Parameters::getA1(){
       return A1;
   }

   double Parameters::getA2(){
       return A2;
   }

   double Parameters::getQ0(){
       return Q0;
   }

   double Parameters::getQA(){
       return QA;
   }

   double Parameters::getQM(){
       return QM;
   }

   double Parameters::getMM0(){
       return MM0;
   }

   double Parameters::getMM1(){
       return MM1;
   }

   double Parameters::getMM2(){
       return MM2;
   }

   double Parameters::getWspH(){
       return wspH;
   }

   double Parameters::getStdAm(){
       return stdAm;
   }

   double Parameters::getStdCs(){
       return stdCs;
   }

   double Parameters::getStdMoc(){
       return stdMoc;
   }

   double Parameters::getPStdAm(){
       return pStdAm;
   }

   double Parameters::getPStdCs(){
       return pStdCs;
   }

   double Parameters::getP0(){
       return P0;
   }

   double Parameters::getP1(){
       return P1;
   }

   double Parameters::getP2(){
       return P2;
   }

   double Parameters::getP3(){
       return P3;
   }

   std::string Parameters::getDevice(){
       return device;
   }



   void Parameters::setDtAm(double val){
       dtAm = val;
   }
   void Parameters::setDtCs(double val){
       dtCs = val;
   }
   void Parameters::setOverlap(double val){
       overlap = val;
   }
   void Parameters::setA0(double val){
       A0 = val;
   }
   void Parameters::setA1(double val){
       A1 = val;
   }
   void Parameters::setA2(double val){
       A2 = val;
   }
   void Parameters::setQ0(double val){
       Q0 = val;
   }
   void Parameters::setQA(double val){
       QA = val;
   }
   void Parameters::setQM(double val){
       QM = val;
   }
   void Parameters::setMM0(double val){
       MM0 = val;
   }
   void Parameters::setMM1(double val){
       MM1 = val;
   }
   void Parameters::setMM2(double val){
       MM2 = val;
   }
   void Parameters::setWspH(double val){
       wspH  = val;
   }
   void Parameters::setStdAm(double val){
       stdAm = val;
   }
   void Parameters::setStdCs(double val){
       stdCs = val;
   }
   void Parameters::setStdMoc(double val){
        stdMoc = val;
   }
   void Parameters::setPStdAm(double val){
       pStdAm = val - 30; //-30 jest dla silesii
   }
   void Parameters::setPStdCs(double val){
       pStdCs = val;
   }

   void Parameters::setP0(double val){
       P0 = val;
   }

   void Parameters::setP1(double val){
       P1 = val;
   }

   void Parameters::setP2(double val){
       P2 = val;
   }

   void Parameters::setP3(double val){
       P3 = val;
   }


   void Parameters::setUrzadzenie(std::string value){
       device = value;
   }

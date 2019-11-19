#include "calculations.h"

Calculations::Calculations(std::string deviceString)
{
    device = deviceString;
}

std::vector <size_t> Calculations::findEmptyBelt(RData rData){
    std::vector <size_t> result;
    size_t counter = 0;
    size_t maxCounter = 0;
    size_t startingIndex = 0;
    size_t finishigIndex = 0;
    //for RFile
    for(size_t i = 0; i<rData.sizeOfData(); i++){
        if(rData.getHeight(i) < 2 && rData.getRunning(i) > 0){ //If belt is running and it is empty
            counter ++;
            if(counter > maxCounter){ //if counter is higher than previous highest value
                maxCounter = counter;
                finishigIndex = i;
                startingIndex = i - counter;
            }
        }
        else {
            counter = 0;
        }
    }
    result.push_back(startingIndex);
    result.push_back(finishigIndex);
    return result;
}

double Calculations::standard(RData rData, size_t indexStart, size_t indexStop, std::string whichCalculations){
    double sum = 0;
    for(size_t i = indexStart; i<=indexStop; i++){
        if(whichCalculations == "am"){
            sum += rData.getAm(i);
        }
        else if (whichCalculations == "cs") {
            sum += rData.getCs(i);
        }
        else if(whichCalculations == "moc"){
            sum += rData.getPower(i);
        }
    }
    return sum/(indexStop-indexStart+1);
}

std::vector <size_t> Calculations::findDifferentHeight(RData rData,std::string device){
    std::vector <double> heightList;
    heightList.push_back(0);
    double minHeight = 0;
    double differenceBetweenHeights = 0;
    double minLength = 0;
    double maxHeight = INFINITY;
    bool counting = false;
    size_t indexBegin = 0;
    double actualHeight = 0;
    int counter = 0;
    std::vector <size_t> result;
    bool was = false;
    int howManyProbes = 0;

    if(device.compare("bogdanka15") == 0 || device.compare("silesia390")){
        minHeight = 7;
        differenceBetweenHeights = 2;
        minLength = 20; // always +1
    }
    else if (device == "bogdanka45") {
        minHeight = 15;
        differenceBetweenHeights = 2;
        minLength = 20; // always + 1
    }

    //Goinjg through RFile
    for(size_t i = 0; i < rData.sizeOfData(); i++){
        was=false;
        if(!counting){   //jeżeli nie zliczam rekordow
            for(size_t j =0; j<heightList.size(); j++){ //przeczesuje liste uzytych wysokosci
                if((rData.getHeight(i)>minHeight && rData.getHeight(i)< maxHeight) && abs(rData.getHeight(i)-heightList[j])>differenceBetweenHeights){ //jezeli nie jestem w trakcie zliczania i jeżeli różnica pomiędzy aktualną wysokością a wysokościami już przeczesanymi jest większa niz minimalna zalezna od urzadzenia
                    if(!was){
                        counting = true;//ustawiam flage zliczania rekordow
                        indexBegin = i;//zapisuje bierzacy index rki jako poczatek ciagu nowej wysokosci
                        actualHeight = rData.getHeight(i);
                    }
                }
                else{
                    was = true;
                    counting = false;
                }
            }
        }
        else{   //jeżeli zliczam rekordy
            if(abs(actualHeight-rData.getHeight(i))<3){ //jeżeli aktualna wysokosc z Rki nie rozni sie od zliczanej o wiecej niz 2
                counter++; //inkrementuj counter
            }
            else {  //jezeli aktualna wysokosc rozni sie od zliczanej o wiecej niz dwa przestan zliczac i resetuj counter
                counting = false;
                counter = 0;
            }
            if(counter > minLength){  //jeżeli naliczono wiecej niz zadana ilosc rekordow o podobnych wysokosciach
                counter = 0;    //zresetuj dlugosc ciagu
                counting = false; //przestan zliczac
                heightList.push_back(actualHeight); //dodaj aktualnie mierzona wysokosc do listy juz zmierzonych
                result.push_back(indexBegin); //dodaj do wyniku poczatek ciagu
                result.push_back(i); //dodaj do wyniku koniec mierzonego ciagu
                howManyProbes++;
                if(howManyProbes >=7){
                    return result;
                }
            }
            else {
            }
        }

    }
    return result;
}

double Calculations::average(RData rData, size_t indexBegin, size_t indexEnd, std::string whichCalculations){
    double sum=0;
    for(size_t i=indexBegin;i<=indexEnd;i++){
        if(whichCalculations == "wysokosc"){
            sum += rData.getHeight(i);
        }
        else if(whichCalculations == "popiol"){
            sum += rData.getAshes(i);
        }
        else if(whichCalculations == "wilgotnosc"){
            sum += rData.getHumidity(i);
        }
        else if(whichCalculations == "kalorycznosc"){
            sum += rData.getCalorific(i);
        }
    }
    return sum/(indexEnd-indexBegin+1);
}

double Calculations::calculateAmPos( Parameters *parameters, double Am, double Cs){
    double overlap = parameters->getOverlap();
    return Am-(Cs*overlap);
}

double Calculations::calculatePAm(Parameters *parameters, double Am, double Cs){
    double dtAm = parameters->getDtAm();
    device = parameters->getDevice();

    if(device.compare("bogdanka15") == 0){
        double pAm = calculateAmPos(parameters, Am, Cs);
        return pAm/(1-(((Am+Cs))/1000000));
    }
    else if(device.compare("bogdanka45") == 0){
        double overlap = parameters->getOverlap();
        return (Am-(overlap*Cs))/(1-(((Am-(overlap*Cs))*dtAm)/1000000));
    }
    else if(device.compare("silesia390") == 0){
        double deadtime = 3.2;
        double stalDoAm = 30;
        double pAm = calculateAmPos(parameters, Am, Cs);
        return pAm/(1-(((Am+Cs)*deadtime)/1000000))+stalDoAm;
    }
    return -1;
}

double Calculations::calculatePCs(Parameters *parameters,double Am, double Cs){
    double dtCs = parameters->getDtCs();
    device = parameters->getDevice();
    if(device.compare("bogdanka15") == 0){
       return Cs/(1-(((Am+Cs)*dtCs)/1000000));
    }
    else if(device.compare("bogdanka45") == 0){
        return Cs/(1-((Cs*dtCs)/1000000));
    }
    else if(device.compare("silesia390") == 0){
        return Cs/(1-((Am+Cs)*3.2)/1000000);    }
    return -1;
}

double Calculations::calculateHeight(Parameters *parameters, double Am, double Cs){
    double pCs = calculatePCs(parameters, Am, Cs);
    double pStdCs = parameters->getPStdCs();
    double wspH = parameters->getWspH();
    double lnCs = log(pStdCs/pCs);
    return lnCs * wspH;
}

double Calculations::calculateAshes(Parameters *parameters, double Am, double Cs){
    double pStdCs = parameters->getPStdCs();
    double pStdAm = parameters->getPStdAm();
    double A0 = parameters->getA0();
    double A1 = parameters->getA1();
    double pCs = calculatePCs(parameters,Am,Cs);
    double lnCs = log(pStdCs/pCs);
    double pAm = calculatePAm(parameters, Am,Cs);
    double lnAm = log(pStdAm/pAm);
    double popiol0 = A0 + A1*(lnAm/lnCs);
    double wysokosc = calculateHeight(parameters,Am,Cs);
    if(device == "bogdanka15"){
        if(wysokosc>22){
            return popiol0 + 0.91*(wysokosc-20);
        }
        else{
            return popiol0;
        }
    }
    else if (device.compare("bogdanka45") == 0 || device.compare("silesia390") == 0 ) {
        double poprawka = parameters->getP0() + parameters->getP1()*wysokosc + parameters->getP2()*pow(wysokosc,2) + parameters->getP3()*pow(wysokosc,3);
        return popiol0 - poprawka;

    }
    else {
        return 0;
    }
}


void Calculations::calculateCorrections(RData *daneR,Parameters *parametersOld, Parameters *parameters, std::vector<size_t> indexVector){
    //utworz vektor ze sprawdzanymi wspoczynnikami A1: (bazowe A1 +- 50 -> krok co 0.1)
    double A1 = parameters->getA1();
    double A0 = parameters->getA0();
    int elementsCount = 5001; //nieparzysta liczba probek zeby A0 bylo dokladnie po srodku
    double firstElement = A1 - (((elementsCount-1)/2)*0.1); //pierwszy sprawdzany element
    double minError = INFINITY;
    std::vector <double> differences;
    double newA0 = 0;
    for(int i=0;i<elementsCount;i++){ //nieparzysta liczba probek zeby A0 bylo dokladnie po srodku i wertujemy cala liste
        double tempA1 = firstElement + i*0.1;
        parameters->setA1(tempA1);
        double maxError = 0;
        for(size_t j = 0; j<indexVector.size();j+=2){//przeskakujemy po wektorze wysokosci co 2 wpisy
            double sumAshes = 0;
            double sumAshesOld = 0;
            for(size_t k = indexVector[j]; k<indexVector[j+1];k++){ //przeczesujemy dany zakres wysokosci i dodajemy obliczony popiol do sumy
                double Am = daneR->getAm(k);
                double Cs = daneR->getCs(k);
                sumAshes += calculateAshes(parameters,Am,Cs);
                sumAshesOld += calculateAshes(parametersOld,Am,Cs);
            }
            double sumNew = sumAshes/(indexVector[j+1]-indexVector[j]+1);
            double sumOld = sumAshesOld/(indexVector[j+1]-indexVector[j]+1);
            double dif = abs(sumOld - sumNew);
            if(dif>maxError){
                maxError = dif;
            }
        }
        if(maxError<minError){
            minError = maxError;
            newA0 = tempA1;
        }
    }
     parameters->setA1(newA0);

    //przeliczanie A0
    double sumAll = 0;
    double sumAllOld = 0;
    for(size_t i = 0; i<indexVector.size();i+=2){//przeskakujemy po wektorze wysokosci co 2 wpisy
        double sum = 0;
        double sumOld = 0;
        for(size_t j = indexVector[i]; j<=indexVector[i+1];j++){ //przeczesujemy dany zakres wysokosci i dodajemy obliczony popiol do sumy
            double Am = daneR->getAm(j);
            double Cs = daneR->getCs(j);
            std::string urzadzenie = parameters->getDevice();
            sum += calculateAshes(parameters,Am,Cs);
            sumOld += calculateAshes(parametersOld,Am,Cs);
        }
        sumAll += sum/(indexVector[i+1]-indexVector[i]+1);
        sumAllOld += sumOld/(indexVector[i+1]-indexVector[i]+1);
    }
    std::vector <double> result;
    double averageForMasurements = sumAll/(indexVector.size()/2);
    double averageOld = sumAllOld/(indexVector.size()/2);
    double noweA0 = A0 + (averageOld - averageForMasurements);
    parameters->setA0(noweA0);
}

double Calculations::calculateHumidity(Parameters *parameters, double Am, double Cs, double power){
    double stdPower = parameters->getStdMoc();
    double wspH = parameters->getWspH();
    double lnPower = log(stdPower/power);
    double height = calculateHeight(parameters,Am,Cs);
    double MM0 = parameters->getMM0();
    double MM1 = parameters->getMM1();
    double MM2 = parameters->getMM2();
    //return MM0 + MM1*(lnMoc/(wysokosc/wspH));
    return MM0 + MM1*(lnPower/(height/wspH))+ MM2/(height/wspH);

}

double Calculations::calculateCalorific(Parameters *parameters, double Am, double Cs, double power){
    double Q0 = parameters->getQ0();
    double QA = parameters->getQA();
    double QM = parameters->getQM();
    double ashes = calculateAshes(parameters,Am,Cs);
    double humidity = calculateHumidity(parameters,Am,Cs,power);
    return Q0 + (QA*ashes) + (QM*humidity);
}

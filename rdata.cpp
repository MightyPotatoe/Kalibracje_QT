#include "rdata.h"
#include <fstream>
#include <QString>

RData::RData(std::string patch, std::string rName, std::string device)
{
    std::string fileName = patch + "/" + rName;
    std::fstream file;
    file.open(fileName);
    if(file.is_open()){
        //How many titles in file
        std::string getFile;
        QString readData;
        int columsCount;
        if(device.compare("bogdanka15") == 0 || device.compare("silesia390") == 0){
            columsCount = 18;
        }
        else if (device.compare("bogdanka45") == 0){
            columsCount = 17;
        }
        else {
            columsCount = 0;
        }
        //skip titles
        for(int i = 0; i<columsCount; i++){
            file >> getFile;
        }
        //getting data
        while(!file.eof()){
            file >> getFile;
            readData = QString::fromStdString(getFile);
            hour.push_back(readData.toStdString());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            ashes.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            humidity.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            calorific.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            height.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            am.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            cs.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            power.push_back(readData.toDouble());
            file >> getFile;
            file >> getFile;
            file >> getFile;
            file >> getFile;
            file >> getFile;
            file >> getFile;
            readData = QString::fromStdString(getFile);
            stdAm.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            stdCs.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            stdPower.push_back(readData.toDouble());
            file >> getFile;
            readData = QString::fromStdString(getFile);
            running.push_back(readData.toDouble());
            if(device.compare("bogdanka15") == 0 || device.compare("silesia390") == 0){
                file >> getFile;
                readData = QString::fromStdString(getFile);
                position.push_back(readData.toDouble());
            }

        }

    }
}


std::string RData::getHour(size_t index){
    size_t size = hour.size();
    if(index<size){
    return hour[index];
    }
    else {
        return "";
    }
}

double RData::getAshes(size_t index){
    size_t size = ashes.size();
    if(index<size){
    return ashes[index];
    }
    else {
        return 0;
    }
}

double RData::getHumidity(size_t index)
{
    size_t size = humidity.size();
    if(index<size){
    return humidity[index];
    }
    else {
        return 0;
    }
}

double RData::getCalorific(size_t index){
    size_t size = calorific.size();
    if(index<size){
    return calorific[index];
    }
    else {
        return 0;
    }
}

double RData::getHeight(size_t index){
    size_t size = height.size();
    if(index<size){
    return height[index];
    }
    else {
        return 0;
    }
}

double RData::getAm(size_t index)
{
    size_t size = am.size();
    if(index<size){
    return am[index];
    }
    else {
        return 0;
    }
}

double RData::getCs(size_t index){
    size_t size = cs.size();
    if(index<size){
    return cs[index];
    }
    else {
        return 0;
    }
}

double RData::getPower(size_t index)
{
    size_t size = power.size();
    if(index<size){
    return power[index];
    }
    else {
        return 0;
    }
}

double RData::getStdAm(size_t index)
{
    size_t size = stdAm.size();
    if(index<size){
    return stdAm[index];
    }
    else {
        return 0;
    }
}

double RData::getStdPower(size_t index){
    size_t size = stdPower.size();
    if(index<size){
    return stdPower[index];
    }
    else {
        return 0;
    }
}

double RData::getStdCs(size_t index){
    size_t size = stdCs.size();
    if(index<size){
    return stdCs[index];
    }
    else {
        return 0;
    }
}

double RData::getRunning(size_t index){
    size_t size = running.size();
    if(index<size){
    return running[index];
    }
    else {
        return 0;
    }
}

double RData::getPosition(size_t index){
    {
        size_t size = position.size();
        if(index<size){
        return position[index];
        }
        else {
            return 0;
        }
    }
}

size_t RData::sizeOfData(){
    size_t isLower = ashes.size();
    size_t result = ashes.size();
    if(humidity.size()<isLower){
        result = humidity.size();
        if(calorific.size()<isLower){
            result = calorific.size();
            if(height.size()<isLower){
                result = height.size();
                if(am.size()<isLower){
                    result = am.size();
                    if(cs.size()<isLower){
                        result = cs.size();
                        if(power.size()<isLower){
                            result = power.size();
                            if(stdCs.size()<isLower){
                                result = stdCs.size();
                                if(stdAm.size()<isLower){
                                    result = stdAm.size();
                                    if(stdPower.size()<isLower){
                                        result = stdPower.size();
                                        if(running.size()<isLower){
                                            result = running.size();
                                            if(position.size()<isLower){
                                                result = position.size();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    return result;
}

size_t RData::findTimeIndex(QTime time){
   return time.hour()*60*60 + time.minute()*60 + time.second();
}

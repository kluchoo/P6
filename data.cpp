#include "data.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Data::Data() {
    this->time = "";
    this->autoconsumption = "";
    this->eksport = "";
    this->import = "";
    this->conscription = "";
    this->production = "";
}

Data::Data(std::string time, std::string autoconsumption, std::string eksport, std::string import, std::string conscription, std::string production) {
    this->time = time;
    this->autoconsumption = autoconsumption;
    this->eksport = eksport;
    this->import = import;
    this->conscription = conscription;
    this->production = production;
}

Data::~Data() {
    std::cout << "Data object destroyed" << std::endl;
}

void Data::setParameters(std::string time, std::string autoconsumption, std::string eksport, std::string import, std::string conscription, std::string production) {
    this->time = time;
    this->autoconsumption = autoconsumption;
    this->eksport = eksport;
    this->import = import;
    this->conscription = conscription;
    this->production = production;
}

void Data::printData() {
    std::cout << "Time: " << this->time << ", "
        << "Autoconsumption: " << this->autoconsumption << ", "
        << "Eksport: " << this->eksport << ", "
        << "Import: " << this->import << ", "
        << "Conscription: " << this->conscription << ", "
        << "Production: " << this->production << std::endl;
}

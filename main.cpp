#include <iostream>
#include <fstream>
#include "data.hpp"
#include <sstream>

using namespace std;

int main() {
    std::ifstream file("Chart Export.csv");
    std::string line;
    std::string time;
    double autoconsumption;
    double eksport;
    double import;
    double conscription;
    double production;
    Data data;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string time;
        std::string autoconsumption;
        std::string eksport;
        std::string import;
        std::string conscription;
        std::string production;
        std::getline(ss, time, ',');
        std::getline(ss, autoconsumption, ',');
        std::getline(ss, eksport, ',');
        std::getline(ss, import, ',');
        std::getline(ss, conscription, ',');
        std::getline(ss, production, ',');

        data.setParameters(time, autoconsumption, eksport, import, conscription, production);

        data.printData();
    }
    return 0;
}
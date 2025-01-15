#include <iostream>
#include <fstream>
#include "data.hpp"
#include <sstream>
#include <vector>

using namespace std;

int main() {
    std::ifstream file("Chart Export.csv");
    std::string line;
    std::vector<Data*> dataVector;
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

        Data* data = new Data();
        data->setParameters(time, autoconsumption, eksport, import, conscription, production);
        dataVector.push_back(data);
    }

    // Clean up allocated memory
    for (Data* data : dataVector) {
        delete data;
    }

    return 0;
}
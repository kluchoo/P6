#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data {
    private:
    std::string time;
    std::string autoconsumption;
    std::string eksport;
    std::string import;
    std::string conscription;
    std::string production;
    /* data */
    public:
    Data();
    Data(std::string time, std::string autoconsumption, std::string eksport, std::string import, std::string conscription, std::string production);
    ~Data();

    void setParameters(std::string time, std::string autoconsumption, std::string eksport, std::string import, std::string conscription, std::string production);

    void printData();

};

#endif // DATA_HPP

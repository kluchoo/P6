#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <fstream>

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

    // Dodane funkcje
    std::string getTime() const;
    float getAutokonsumpcja() const;
    float getEksport() const;
    float getImport() const;
    float getPobor() const;
    float getProdukcja() const;
    void serialize(std::ofstream& out) const;
};

#endif // DATA_HPP

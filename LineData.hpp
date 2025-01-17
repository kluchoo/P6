#ifndef LINEDATA_HPP
#define LINEDATA_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "logger.hpp" // Dodanie brakującego nagłówka

using namespace std;

/**
 * @class LineData
 * @brief Klasa reprezentująca dane jednego wiersza z pliku CSV.
 *
 * Klasa umożliwia wczytywanie, wyświetlanie oraz serializację danych wiersza.
 */
class LineData {
    public:
  
    explicit LineData(const string& line);


    LineData(ifstream& in);

   
    void print() const;

    void printData() const;

   
    string printString();

  
    void serialize(ofstream& out) const;

   
    void deserialize(ifstream& in);

    string getDate() const { return date; }

  
    float getAutokonsumpcja() const { return autokonsumpcja; }

    float getEksport() const { return eksport; }


    float getImport() const { return import; }

  
    float getPobor() const { return pobor; }

    float getProdukcja() const { return produkcja; }

    private:
    string date;
    float autokonsumpcja;
    float eksport;
    float import;
    float pobor;
    float produkcja;
};

#endif /* LINEDATA_HPP */

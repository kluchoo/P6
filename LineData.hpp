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
    /**
     * @brief Konstruktor przetwarzający wiersz danych z formatu CSV.
     * @param line Wiersz danych wejściowych w formacie tekstowym (CSV).
     */
    explicit LineData(const string& line);

    /**
    * @brief Konstruktor odczytujący dane z pliku binarnego.
    * @param in Strumień wejściowy pliku binarnego.
    */
    LineData(ifstream& in);

    /**
     * @brief Wypisuje wszystkie dane (wraz z datą) na standardowe wyjście.
     */
    void print() const;

    /**
     * @brief Wypisuje tylko dane liczbowe (bez daty) na standardowe wyjście.
     */
    void printData() const;

    /**
     * @brief Zwraca wszystkie dane jako łańcuch znaków.
     * @return Dane w formacie tekstowym (data + wartości liczbowe).
     */
    string printString();

    /**
    * @brief Serializuje obiekt do pliku binarnego.
    * @param out Strumień wyjściowy pliku binarnego.
    */
    void serialize(ofstream& out) const;

    /**
    * @brief Deserializuje obiekt z pliku binarnego.
    * @param in Strumień wejściowy pliku binarnego.
    */
    void deserialize(ifstream& in);

    /**
    * @brief Zwraca datę z wiersza.
    * @return Data w formacie tekstowym.
    */
    string getDate() const { return date; }

    /**
    * @brief Zwraca wartość autokonsumpcji.
    * @return Wartość autokonsumpcji jako liczba zmiennoprzecinkowa.
    */
    float getAutokonsumpcja() const { return autokonsumpcja; }

    /**
    * @brief Zwraca wartość eksportu.
    * @return Wartość eksportu jako liczba zmiennoprzecinkowa.
    */
    float getEksport() const { return eksport; }

    /**
    * @brief Zwraca wartość importu.
    * @return Wartość importu jako liczba zmiennoprzecinkowa.
    */
    float getImport() const { return import; }

    /**
    * @brief Zwraca wartość poboru.
    * @return Wartość poboru jako liczba zmiennoprzecinkowa.
    */
    float getPobor() const { return pobor; }

    /**
     * @brief Zwraca wartość produkcji.
     * @return Wartość produkcji jako liczba zmiennoprzecinkowa.
     */
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

#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>

#include "lineData.hpp"

/**
 * @class TreeData
 * @brief Klasa obsługująca hierarchiczną strukturę danych z pliku CSV.
 */
class DataTree {
    public:
    /**
     * @struct QuarterNode
     * @brief Reprezentuje dane z podziałem na kwartały dnia.
     */
    struct QuarterNode {
        int quarter;
        int hour;
        int minute;
        std::vector<LineData> data;
    };

    /**
     * @struct DayNode
     * @brief Reprezentuje dane dzienne.
     */
    struct DayNode {
        int day;
        std::map<int, QuarterNode> quarters;
    };

    /**
     * @struct MonthNode
     * @brief Reprezentuje dane miesięczne.
     */
    struct MonthNode {
        int month;
        std::map<int, DayNode> days;
    };

    /**
    * @struct YearNode
    * @brief Reprezentuje dane roczne.
    */
    struct YearNode {
        int year;
        std::map<int, MonthNode> months;
    };

    /**
     * @brief Dodaje dane do struktury drzewa.
     * @param lineData Obiekt LineData reprezentujący wiersz danych.
     */
    void addData(const LineData& lineData);

    /**
     * @brief Wyświetla całą strukturę drzewa.
     */
    void print() const;

    /**
     * @brief Pobiera dane w podanym przedziale czasowym.
     * @param startDate Data początkowa w formacie dd.mm.yyyy hh:mm.
     * @param endDate Data końcowa w formacie dd.mm.yyyy hh:mm.
     * @return Wektor obiektów LineData w podanym zakresie czasowym.
     */
    std::vector<LineData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;

    /**
    * @brief Oblicza sumy danych w podanym przedziale czasowym.
    * @param startDate Data początkowa w formacie dd.mm.yyyy hh:mm.
    * @param endDate Data końcowa w formacie dd.mm.yyyy hh:mm.
    * @param[out] autokonsumpcjaSum Suma autokonsumpcji.
    * @param[out] eksportSum Suma eksportu.
    * @param[out] importSum Suma importu.
    * @param[out] poborSum Suma poboru.
    * @param[out] produkcjaSum Suma produkcji.
    */
    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const;

    /**
    * @brief Oblicza średnie dane w podanym przedziale czasowym.
    * @param startDate Data początkowa w formacie dd.mm.yyyy hh:mm.
    * @param endDate Data końcowa w formacie dd.mm.yyyy hh:mm.
    * @param[out] autokonsumpcjaAvg Średnia autokonsumpcji.
    * @param[out] eksportAvg Średnia eksportu.
    * @param[out] importAvg Średnia importu.
    * @param[out] poborAvg Średnia poboru.
    * @param[out] produkcjaAvg Średnia produkcji.
    */
    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const;

    /**
   * @brief Porównuje dane między dwoma zakresami czasowymi.
   * @param startDate1 Data początkowa pierwszego zakresu.
   * @param endDate1 Data końcowa pierwszego zakresu.
   * @param startDate2 Data początkowa drugiego zakresu.
   * @param endDate2 Data końcowa drugiego zakresu.
   * @param[out] autokonsumpcjaDiff Różnica autokonsumpcji.
   * @param[out] eksportDiff Różnica eksportu.
   * @param[out] importDiff Różnica importu.
   * @param[out] poborDiff Różnica poboru.
   * @param[out] produkcjaDiff Różnica produkcji.
   */
    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const;

    /**
     * @brief Serializuje strukturę drzewa do strumienia wyjściowego.
     * @param out Strumień wyjściowy.
     */
    void serialize(std::ofstream& out) const;

    /**
      * @brief Wyszukuje rekordy w podanym zakresie czasowym z uwzględnieniem tolerancji.
      * @param startDate Data początkowa w formacie dd.mm.yyyy hh:mm.
      * @param endDate Data końcowa w formacie dd.mm.yyyy hh:mm.
      * @param value Wartość wyszukiwana.
      * @param tolerance Tolerancja dla wartości.
      * @return Wektor obiektów LineData spełniających kryteria wyszukiwania.
      */
    std::vector<LineData> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const;

    private:
    /**
     * @brief Mapa przechowująca dane w hierarchii lat.
     *
     * Kluczami mapy są lata, a wartościami struktury YearNode, które zawierają dane
     * dla poszczególnych lat. Struktura ta umożliwia przechowywanie i zarządzanie
     * danymi w podziale na lata, miesiące, dni i kwartały.
     */
    std::map<int, YearNode> years;
};

#endif // TREEDATA_H
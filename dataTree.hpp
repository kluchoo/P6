#ifndef DATATREE_HPP
#define DATATREE_HPP

#include <string>
#include <map>
#include <vector>
#include "data.hpp"

class DataTree {
    public:
    struct Quarter {
        int quarter;
        int hour;
        int minute;
        std::vector<Data*> data;
    };

    struct Day {
        int day;
        std::map<int, Quarter> quarters; // 0: 00:00-5:45, 1: 6:00-11:45, 2: 12:00-17:45, 3: 18:00-23:45
    };

    struct Month {
        int month;
        std::map<int, Day> days;
    };

    struct Year {
        int year;
        std::map<int, Month> months;
    };

    void addData(const std::string& time, Data* data);
    void clear();
    void print() const;
    std::vector<Data*> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;
    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const;
    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const;
    void serialize(std::ofstream& out) const;
    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const;
    std::vector<Data*> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const;

    private:
    std::map<int, Year> years;
};

#endif // DATATREE_HPP

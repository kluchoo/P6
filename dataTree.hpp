#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>

#include "lineData.hpp"


class DataTree {
    public:

    struct QuarterNode {
        int quarter;
        int hour;
        int minute;
        std::vector<LineData> data;
    };

    struct DayNode {
        int day;
        std::map<int, QuarterNode> quarters;
    };

 
    struct MonthNode {
        int month;
        std::map<int, DayNode> days;
    };

   
    struct YearNode {
        int year;
        std::map<int, MonthNode> months;
    };

   
    void addData(const LineData& lineData);

  
    void print() const;


    std::vector<LineData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;


    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const;

    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const;

    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const;

    void serialize(std::ofstream& out) const;

    std::vector<LineData> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const;

    private:

    std::map<int, YearNode> years;
};

#endif // TREEDATA_H
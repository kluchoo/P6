#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "dataTree.hpp"

using namespace std;

void DataTree::addData(const LineData& lineData) {
    stringstream ss(lineData.getDate());
    string token;
    vector<int> dateParts;

    while (getline(ss, token, '.')) {
        dateParts.push_back(stoi(token));
    }

    int year = dateParts[2];
    int month = dateParts[1];
    int day = dateParts[0];
    int hour = stoi(lineData.getDate().substr(11, 2));
    int minute = stoi(lineData.getDate().substr(14, 2));
    int quarter = (hour * 60 + minute) / 360;

    years[year].year = year;
    years[year].months[month].month = month;
    years[year].months[month].days[day].day = day;
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;
    years[year].months[month].days[day].quarters[quarter].hour = hour;
    years[year].months[month].days[day].quarters[quarter].minute = minute;
    years[year].months[month].days[day].quarters[quarter].data.push_back(lineData);
}

void DataTree::print() const {
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        cout << "Year: " << yearNode.year << endl;

        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            cout << "\tMonth: " << monthNode.month << endl;

            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                cout << "\t\tDay: " << dayNode.day << endl;

                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    cout << "\t\t\tQuarter: " << quarterNode.quarter
                        << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << endl;

                    for (const auto& lineData : quarterNode.data) {
                        lineData.printData();
                    }
                }
            }
        }
    }
}

std::vector<LineData> DataTree::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<LineData> result;

    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t start = mktime(&tm);

    ss.clear();
    ss.str(endDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t end = mktime(&tm);

    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    for (const auto& lineData : quarterNode.data) {
                        std::tm tm = {};
                        std::istringstream ss(lineData.getDate());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
                        time_t dataTime = mktime(&tm);

                        if (dataTime >= start && dataTime <= end) {
                            result.push_back(lineData);
                        }
                    }
                }
            }
        }
    }

    return result;
}

void DataTree::calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const {
    autokonsumpcjaSum = 0.0f;
    eksportSum = 0.0f;
    importSum = 0.0f;
    poborSum = 0.0f;
    produkcjaSum = 0.0f;

    std::vector<LineData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& lineData : data) {
        autokonsumpcjaSum += lineData.getAutokonsumpcja();
        eksportSum += lineData.getEksport();
        importSum += lineData.getImport();
        poborSum += lineData.getPobor();
        produkcjaSum += lineData.getProdukcja();
    }
}

void DataTree::calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const {
    float autokonsumpcjaSum = 0.0f, eksportSum = 0.0f, importSum = 0.0f, poborSum = 0.0f, produkcjaSum = 0.0f;
    int count = 0;

    std::vector<LineData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& lineData : data) {
        autokonsumpcjaSum += lineData.getAutokonsumpcja();
        eksportSum += lineData.getEksport();
        importSum += lineData.getImport();
        poborSum += lineData.getPobor();
        produkcjaSum += lineData.getProdukcja();
        count++;
    }

    if (count > 0) {
        autokonsumpcjaAvg = autokonsumpcjaSum / count;
        eksportAvg = eksportSum / count;
        importAvg = importSum / count;
        poborAvg = poborSum / count;
        produkcjaAvg = produkcjaSum / count;
    } else {
        autokonsumpcjaAvg = eksportAvg = importAvg = poborAvg = produkcjaAvg = 0.0f;
    }
}

void DataTree::serialize(std::ofstream& out) const {
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    for (const auto& lineData : quarterNode.data) {
                        lineData.serialize(out);
                    }
                }
            }
        }
    }
}

void DataTree::compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const {
    std::vector<LineData> data1 = getDataBetweenDates(startDate1, endDate1);
    std::vector<LineData> data2 = getDataBetweenDates(startDate2, endDate2);

    float autokonsumpcjaSum1 = 0.0f, eksportSum1 = 0.0f, importSum1 = 0.0f, poborSum1 = 0.0f, produkcjaSum1 = 0.0f;
    for (const auto& lineData : data1) {
        autokonsumpcjaSum1 += lineData.getAutokonsumpcja();
        eksportSum1 += lineData.getEksport();
        importSum1 += lineData.getImport();
        poborSum1 += lineData.getPobor();
        produkcjaSum1 += lineData.getProdukcja();
    }

    float autokonsumpcjaSum2 = 0.0f, eksportSum2 = 0.0f, importSum2 = 0.0f, poborSum2 = 0.0f, produkcjaSum2 = 0.0f;
    for (const auto& lineData : data2) {
        autokonsumpcjaSum2 += lineData.getAutokonsumpcja();
        eksportSum2 += lineData.getEksport();
        importSum2 += lineData.getImport();
        poborSum2 += lineData.getPobor();
        produkcjaSum2 += lineData.getProdukcja();
    }

    autokonsumpcjaDiff = autokonsumpcjaSum2 - autokonsumpcjaSum1;
    eksportDiff = eksportSum2 - eksportSum1;
    importDiff = importSum2 - importSum1;
    poborDiff = poborSum2 - poborSum1;
    produkcjaDiff = produkcjaSum2 - produkcjaSum1;
}

std::vector<LineData> DataTree::searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const {
    std::vector<LineData> result;

    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");

    ss.clear();
    ss.str(endDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");

    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    for (const auto& lineData : quarterNode.data) {
                        if (lineData.getAutokonsumpcja() >= value - tolerance && lineData.getAutokonsumpcja() <= value + tolerance) {
                            result.push_back(lineData);
                        }
                    }
                }
            }
        }
    }

    return result;
}
#include "dataTree.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

void DataTree::addData(const std::string& time, Data* data) {
    std::tm tm = {};
    std::istringstream ss(time);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");

    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int minute = tm.tm_min;
    int quarter = (hour * 60 + minute) / 360;

    years[year].year = year;
    years[year].months[month].month = month;
    years[year].months[month].days[day].day = day;
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;
    years[year].months[month].days[day].quarters[quarter].hour = hour;
    years[year].months[month].days[day].quarters[quarter].minute = minute;
    years[year].months[month].days[day].quarters[quarter].data.push_back(data);
}

void DataTree::clear() {
    for (auto& year : years) {
        for (auto& month : year.second.months) {
            for (auto& day : month.second.days) {
                for (auto& quarter : day.second.quarters) {
                    for (Data* data : quarter.second.data) {
                        delete data;
                    }
                }
            }
        }
    }
    years.clear();
}

void DataTree::print() const {
    for (const auto& yearPair : years) {
        const Year& yearNode = yearPair.second;
        std::cout << "Year: " << yearNode.year << std::endl;

        for (const auto& monthPair : yearNode.months) {
            const Month& monthNode = monthPair.second;
            std::cout << "\tMonth: " << monthNode.month << std::endl;

            for (const auto& dayPair : monthNode.days) {
                const Day& dayNode = dayPair.second;
                std::cout << "\t\tDay: " << dayNode.day << std::endl;

                for (const auto& quarterPair : dayNode.quarters) {
                    const Quarter& quarterNode = quarterPair.second;
                    std::cout << "\t\t\tQuarter: " << quarterNode.quarter
                        << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << std::endl;

                    for (const auto& data : quarterNode.data) {
                        data->printData();
                    }
                }
            }
        }
    }
}

std::vector<Data*> DataTree::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<Data*> result;

    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t start = mktime(&tm);

    ss.clear();
    ss.str(endDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t end = mktime(&tm);

    for (const auto& yearPair : years) {
        const Year& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const Month& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const Day& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const Quarter& quarterNode = quarterPair.second;
                    for (const auto& data : quarterNode.data) {
                        std::tm tm = {};
                        std::istringstream ss(data->getTime());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
                        time_t dataTime = mktime(&tm);

                        if (dataTime >= start && dataTime <= end) {
                            result.push_back(data);
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

    std::vector<Data*> data = getDataBetweenDates(startDate, endDate);
    for (const auto& dataItem : data) {
        autokonsumpcjaSum += dataItem->getAutokonsumpcja();
        eksportSum += dataItem->getEksport();
        importSum += dataItem->getImport();
        poborSum += dataItem->getPobor();
        produkcjaSum += dataItem->getProdukcja();
    }
}

void DataTree::calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const {
    float autokonsumpcjaSum = 0.0f, eksportSum = 0.0f, importSum = 0.0f, poborSum = 0.0f, produkcjaSum = 0.0f;
    int count = 0;

    std::vector<Data*> data = getDataBetweenDates(startDate, endDate);
    for (const auto& dataItem : data) {
        autokonsumpcjaSum += dataItem->getAutokonsumpcja();
        eksportSum += dataItem->getEksport();
        importSum += dataItem->getImport();
        poborSum += dataItem->getPobor();
        produkcjaSum += dataItem->getProdukcja();
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
        const Year& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const Month& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const Day& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const Quarter& quarterNode = quarterPair.second;
                    for (const auto& data : quarterNode.data) {
                        data->serialize(out);
                    }
                }
            }
        }
    }
}

void DataTree::compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const {
    std::vector<Data*> data1 = getDataBetweenDates(startDate1, endDate1);
    std::vector<Data*> data2 = getDataBetweenDates(startDate2, endDate2);

    float autokonsumpcjaSum1 = 0.0f, eksportSum1 = 0.0f, importSum1 = 0.0f, poborSum1 = 0.0f, produkcjaSum1 = 0.0f;
    for (const auto& dataItem : data1) {
        autokonsumpcjaSum1 += dataItem->getAutokonsumpcja();
        eksportSum1 += dataItem->getEksport();
        importSum1 += dataItem->getImport();
        poborSum1 += dataItem->getPobor();
        produkcjaSum1 += dataItem->getProdukcja();
    }

    float autokonsumpcjaSum2 = 0.0f, eksportSum2 = 0.0f, importSum2 = 0.0f, poborSum2 = 0.0f, produkcjaSum2 = 0.0f;
    for (const auto& dataItem : data2) {
        autokonsumpcjaSum2 += dataItem->getAutokonsumpcja();
        eksportSum2 += dataItem->getEksport();
        importSum2 += dataItem->getImport();
        poborSum2 += dataItem->getPobor();
        produkcjaSum2 += dataItem->getProdukcja();
    }

    autokonsumpcjaDiff = autokonsumpcjaSum2 - autokonsumpcjaSum1;
    eksportDiff = eksportSum2 - eksportSum1;
    importDiff = importSum2 - importSum1;
    poborDiff = poborSum2 - poborSum1;
    produkcjaDiff = produkcjaSum2 - produkcjaSum1;
}

std::vector<Data*> DataTree::searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const {
    std::vector<Data*> result;

    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");

    ss.clear();
    ss.str(endDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");

    for (const auto& yearPair : years) {
        const Year& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const Month& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const Day& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const Quarter& quarterNode = quarterPair.second;
                    for (const auto& data : quarterNode.data) {
                        if (data->getAutokonsumpcja() >= value - tolerance && data->getAutokonsumpcja() <= value + tolerance) {
                            result.push_back(data);
                        }
                    }
                }
            }
        }
    }

    return result;
}

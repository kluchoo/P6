#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <vector>
#include "dataTree.hpp"

enum MenuOption {
    LOAD_DATA_FROM_FILE = 1,
    DISPLAY_TREE_STRUCTURE,
    GET_DATA_BETWEEN_DATES,
    CALCULATE_SUMS_BETWEEN_DATES,
    CALCULATE_AVERAGES_BETWEEN_DATES,
    COMPARE_DATA_BETWEEN_DATES,
    SEARCH_RECORDS_WITH_TOLERANCE,
    SAVE_DATA_TO_BINARY_FILE,
    LOAD_DATA_FROM_BINARY_FILE,
    EXIT
};

std::istream& operator>>(std::istream& iStream, MenuOption& menuOption);

class App {
    private:
    static DataTree treeData;

    App() = delete;
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    static int mainMenu();
    static int handleLoadDataFromFile();
    static int handleDisplayTreeStructure();
    static int handleGetDataBetweenDates();
    static int handleCalculateSumsBetweenDates();
    static int handleCalculateAveragesBetweenDates();
    static int handleCompareDataBetweenDates();
    static int handleSearchRecordsWithTolerance();
    static int handleSaveDataToBinaryFile();
    static int handleLoadDataFromBinaryFile();
    static int handleExit();

    public:
    static int run();
};

#endif // APP_HPP
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "app.hpp"
#include "lineData.hpp"
#include "lineValidation.hpp"
#include "DataTree.hpp"
#include "logger.hpp"

std::istream& operator>>(std::istream& iStream, MenuOption& menuOption) {
    int num;
    iStream >> num;
    menuOption = static_cast<MenuOption>(num);

    return iStream;
}

DataTree App::treeData;

int App::mainMenu() {
    while (true) {
        std::cout << "MENU:\n\n";

        std::cout << "1. Załaduj dane z pliku\n";
        std::cout << "2. Wyświetl strukturę drzewa\n";
        std::cout << "3. Pobierz dane w określonym przedziale czasowym\n";
        std::cout << "4. Oblicz sumy w określonym przedziale czasowym\n";
        std::cout << "5. Oblicz średnią wartość w określonym przedziale czasowym\n";
        std::cout << "6. Porównaj dane między dwoma zakresami czasowymi\n";
        std::cout << "7. Wyszukaj dane w określonym przedziale czasowym z tolerancją\n";
        std::cout << "8. Zapisz dane do pliku binarnego\n";
        std::cout << "9. Wczytaj dane z pliku binarnego\n";

        std::cout << "10. Wyjdź\n\n";

        std::cout << "Wybierz działanie: ";

        MenuOption selectedOption;

        std::cin >> selectedOption;

        if (selectedOption > EXIT) {
            std::cout << "Nieprawidłowa opcja, spróbuj ponownie\n\n";
            continue;
        }

        std::cout << std::endl;

        switch (selectedOption) {
        case LOAD_DATA_FROM_FILE:
            handleLoadDataFromFile();
            break;
        case DISPLAY_TREE_STRUCTURE:
            handleDisplayTreeStructure();
            break;
        case GET_DATA_BETWEEN_DATES:
            handleGetDataBetweenDates();
            break;
        case CALCULATE_SUMS_BETWEEN_DATES:
            handleCalculateSumsBetweenDates();
            break;
        case CALCULATE_AVERAGES_BETWEEN_DATES:
            handleCalculateAveragesBetweenDates();
            break;
        case COMPARE_DATA_BETWEEN_DATES:
            handleCompareDataBetweenDates();
            break;
        case SEARCH_RECORDS_WITH_TOLERANCE:
            handleSearchRecordsWithTolerance();
            break;
        case SAVE_DATA_TO_BINARY_FILE:
            handleSaveDataToBinaryFile();
            break;
        case LOAD_DATA_FROM_BINARY_FILE:
            handleLoadDataFromBinaryFile();
            break;
        case EXIT:
            {
                return handleExit();
            }
        default:
            std::cout << "Nieprawidłowa opcja, spróbuj ponownie\n";
        }

        std::cout << "\n";
    }
}


int App::run() {
#ifdef _WIN32
    // enable utf-8 printing on windows
    SetConsoleOutputCP(CP_UTF8);
#endif

    int exitCode = mainMenu();
    return exitCode;
}

int App::handleLoadDataFromFile() {
    std::ifstream file;

    file.open("Chart Export.csv");
    if (!file.is_open()) {
        std::cerr << "Podczas otwierania pliku wystąpił błąd" << std::endl;
        return -1;
    }

    vector<LineData> data;
    std::string line;

    while (std::getline(file, line)) {
        if (lineValidation(line)) {
            LineData ld(line);
            data.push_back(ld);
            treeData.addData(ld);
        }
    }

    file.close();
    cout << "Dane zostały załadowane pomyślnie." << endl;
    cout << "Załadowano " << data.size() << " linii" << endl;
    cout << "Znaleziono " << loggerErrorCount << " niepoprawnych linii" << endl;
    cout << "Sprawdź pliki log i log_error, aby uzyskać więcej informacji" << endl;

    return 0;
}

int App::handleDisplayTreeStructure() {
    treeData.print();

    return 0;
}

int App::handleGetDataBetweenDates() {
    std::string startDate, endDate;
    std::vector<LineData> filteredData;

    std::cout << "Podaj datę początkową (dd.mm.yyyy hh:mm): ";
    std::cin.ignore();
    std::getline(std::cin, startDate);
    std::cout << "Podaj datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate);

    filteredData = treeData.getDataBetweenDates(startDate, endDate);
    std::cout << "Dane pomiędzy " << startDate << " a " << endDate << ":" << std::endl;
    for (const auto& ld : filteredData) {
        ld.print();
    }

    return 0;
}

int App::handleCalculateSumsBetweenDates() {
    std::string startDate, endDate;
    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;

    std::cout << "Podaj datę początkową (dd.mm.yyyy hh:mm): ";
    std::cin.ignore();
    std::getline(std::cin, startDate);
    std::cout << "Podaj datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate);

    treeData.calculateSumsBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
    std::cout << "Suma pomiędzy " << startDate << " and " << endDate << ":" << std::endl;
    std::cout << "Autokonsumpcja: " << autokonsumpcjaSum << std::endl;
    std::cout << "Eksport: " << eksportSum << std::endl;
    std::cout << "Import: " << importSum << std::endl;
    std::cout << "Pobór: " << poborSum << std::endl;
    std::cout << "Produkcja: " << produkcjaSum << std::endl;

    return 0;
}

int App::handleCalculateAveragesBetweenDates() {
    std::string startDate, endDate;
    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;

    std::cout << "Podaj datę początkową (dd.mm.yyyy hh:mm): ";
    std::cin.ignore();
    std::getline(std::cin, startDate);
    std::cout << "Podaj datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate);

    treeData.calculateAveragesBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
    std::cout << "Średnie wartości pomiędzy " << startDate << " a " << endDate << ":" << std::endl;
    std::cout << "Autokonsumpcja: " << autokonsumpcjaSum << std::endl;
    std::cout << "Eksport: " << eksportSum << std::endl;
    std::cout << "Import: " << importSum << std::endl;
    std::cout << "Pobór: " << poborSum << std::endl;
    std::cout << "Produkcja: " << produkcjaSum << std::endl;

    return 0;
}

int App::handleCompareDataBetweenDates() {
    std::string startDate1, endDate1, startDate2, endDate2;
    float autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff;

    std::cout << "Podaj pierwszą datę początkową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, startDate1);
    std::cout << "Podaj pierwszą datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate1);
    std::cout << "Podaj drugą datę początkową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, startDate2);
    std::cout << "Podaj drugą datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate2);

    treeData.compareDataBetweenDates(startDate1, endDate1, startDate2, endDate2, autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff);
    std::cout << "Różnicę pomiędzy " << startDate1 << " a " << endDate1 << " a " << startDate2 << " a " << endDate2 << ":" << std::endl;
    std::cout << "Autokonsumpcja: " << autokonsumpcjaDiff << std::endl;
    std::cout << "Eksport: " << eksportDiff << std::endl;
    std::cout << "Import: " << importDiff << std::endl;
    std::cout << "Pobór: " << poborDiff << std::endl;
    std::cout << "Produkcja: " << produkcjaDiff << std::endl;

    return 0;
}

int App::handleSearchRecordsWithTolerance() {
    std::string startDate, endDate;
    float searchValue, tolerance;
    std::vector<LineData> recordsWithTolerance;

    std::cout << "Podaj datę początkową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, startDate);
    std::cout << "Podaj datę końcową (dd.mm.yyyy hh:mm): ";
    std::getline(std::cin, endDate);
    std::cout << "Podaj wartość wyszukiwaną: ";
    std::cin >> searchValue;
    std::cout << "Podaj tolerancję: ";
    std::cin >> tolerance;

    recordsWithTolerance = treeData.searchRecordsWithTolerance(startDate, endDate, searchValue, tolerance);
    std::cout << "Znalezione rekordy w zakresie tolerancji:" << std::endl;
    for (const auto& ld : recordsWithTolerance) {
        ld.print();
    }

    return 0;
}

int App::handleSaveDataToBinaryFile() {
    std::ofstream file;
    file.open("data.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Wystąpił błąd podczas otwierania pliku" << std::endl;
        return -1;
    }

    treeData.serialize(file);
    file.close();
    std::cout << "Dane zostały pomyślnie zapisane." << std::endl;

    return 0;
}

int App::handleLoadDataFromBinaryFile() {
    std::ifstream file;
    file.open("data.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Wystąpił błąd podczas otwierania pliku" << std::endl;
        return -1;
    }

    while (file.peek() != EOF) {
        LineData ld(file);
    }

    file.close();
    std::cout << "Dane zostały pomyślnie zapisane." << std::endl;

    return 0;
}

int App::handleExit() {
    std::cout << "Dziękujemy za korzystanie z programu\n";

    return 0;
}
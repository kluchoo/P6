#include "logger.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>

Logger::Logger(const std::string& filename) {
    // Generowanie nazwy pliku na podstawie aktualnej daty i godziny
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    std::string fullFilename = filename + "_" + buf + ".log";

    // Otwarcie pliku logu
    logFile.open(fullFilename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku logu: " + fullFilename);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
// otwieranie oraz zamykanie pliku
void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        // Dodanie daty i godziny do komunikatu
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        logFile << "[" << buf << "] " << message << std::endl;
    }
}

// Definicje globalnych loggerów
Logger logger("log");
Logger loggerError("error_log");
int loggerErrorCount = 0;

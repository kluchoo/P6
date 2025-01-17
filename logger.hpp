#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

/**
 * @class Logger
 * @brief Klasa obsługująca logowanie komunikatów do plików tekstowych.
 *
 * Klasa umożliwia zapisywanie komunikatów do pliku z automatycznym nadaniem nazwy pliku
 * na podstawie bieżącej daty i godziny. Używana do rejestrowania zdarzeń i komunikatów.
 */
class Logger {
    public:
    /**
     * @brief Konstruktor klasy Logger.
     *
     * Tworzy plik logu z unikalną nazwą opartą na aktualnej dacie i godzinie.
     * Jeśli plik nie może zostać otwarty, rzuca wyjątek.
     *
     * @param filename Nazwa podstawowa pliku logu (bez daty i rozszerzenia).
     * @throws std::runtime_error Jeśli plik logu nie może zostać otwarty.
     */
    Logger(const std::string& filename);

    /**
    * @brief Destruktor klasy Logger.
    *
    * Zamyka otwarty plik logu, jeśli jest otwarty.
    */
    ~Logger();

    /**
     * @brief Zapisuje komunikat do pliku logu.
     *
     * Dodaje datę i godzinę do komunikatu przed zapisaniem.
     *
     * @param message Komunikat do zapisania w pliku logu.
     */
    void log(const std::string& message);

    private:
    std::ofstream logFile;
};

/**
 * @var logger
 * @brief Globalny logger dla standardowych komunikatów.
 *
 * Instancja klasy Logger przeznaczona do rejestrowania ogólnych komunikatów programu.
 */
extern Logger logger;

/**
 * @var loggerError
 * @brief Globalny logger dla komunikatów błędów.
 *
 * Instancja klasy Logger przeznaczona do rejestrowania komunikatów błędów programu.
 */
extern Logger loggerError;

//eeror count


/**
 * @var loggerErrorCount
 * @brief Licznik wystąpień błędów logowanych przez loggerError.
 *
 * Przechowuje liczbę komunikatów błędów zapisanych do loggerError.
 */
extern int loggerErrorCount;

#endif /* LOGGER_HPP */

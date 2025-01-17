#ifndef LINEVALIDATION_HPP
#define LINEVALIDATION_HPP

#include <string>
#include <cctype>
#include <algorithm>
#include "logger.hpp"

/**
 * @brief Funkcja sprawdzająca poprawność wiersza danych.
 *
 * @details Sprawdza, czy wiersz:
 * - Nie jest pusty.
 * - Nie zawiera nagłówka (np. słowo "Time").
 * - Nie zawiera liter.
 * - Zawiera dokładnie 5 przecinków, co odpowiada oczekiwanej liczbie parametrów.
 *
 * W przypadku błędu odpowiedni komunikat zostaje zapisany w logach.
 *
 * @param line Wiersz danych wejściowych jako ciąg znaków.
 * @return true, jeśli wiersz jest poprawny, false w przeciwnym razie.
 */
bool lineValidation(const std::string& line) {
    if (line.empty()) {
        loggerError.log("Pusta linia");
        return false;
    } else if (line.find("Time") != std::string::npos) {
        loggerError.log("Znaleziono nagłówek: " + line);
        return false;
    } else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); })) {
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    } else if (std::count(line.begin(), line.end(), ',') != 5) {
        loggerError.log("Nieprawidłowa liczba parametrów: " + line);
        return false;
    } else {
        return true;
    }
}

#endif /* LINEVALIDATION_HPP */

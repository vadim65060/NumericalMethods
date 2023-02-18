//
// Created by vadim on 17.02.2023.
//

#ifndef NUMERICALMETHODS_LOGGER_H
#define NUMERICALMETHODS_LOGGER_H

#include <iostream>
#include <tuple>
#include <vector>
#include "Root.h"

enum LogLevel {
    ALL,
    IMPORTANT,
    ANSWER,
    NOTHING
};

class Logger {
public:
    Logger() {
        logLevel = ALL;
    }

    explicit Logger(LogLevel logLevel) {
        this->logLevel = logLevel;
    }

    void Log(const std::string &funcName, double x, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << ":: x: " << x << std::endl;
    }

    void Log(const std::string &funcName, std::pair<double, double> pair, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << ":: [a,b]: [" << pair.first << ',' << pair.second << ']' << std::endl;
    }

    void Log(const std::string &funcName, Root root, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << ":: root:" << root.root << "; delta:" << root.delta << "; k:" << root.k << std::endl;
    }

    void Log(const std::string &funcName, const std::vector<std::pair<double, double>> &roots, LogLevel level) {
        if (level < logLevel) return;
        for (auto root: roots) {
            Log(funcName, root, level);
        }
    }

private:
    LogLevel logLevel;
};

#endif //NUMERICALMETHODS_LOGGER_H
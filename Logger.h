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

    void Log(const std::string &funcName, const double &x, LogLevel level, const std::string &text = "x") {
        if (level < logLevel) return;
        std::cout << funcName << ":: " + text + ": " << x << std::endl;
    }

    void Log(const std::string &funcName, const std::pair<double, double> &pair, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << ":: [a,b]: [" << pair.first << ',' << pair.second << ']' << std::endl;
    }

    void Log(const std::string &funcName, const Root &root, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << ":: root:" << root.root << "; delta:" << root.delta;
        if (root.k != 0)
            std::cout << "; k:" << root.k;
        std::cout << std::endl;
    }

    void Log(const std::string &funcName, const std::vector<std::pair<double, double>> &roots, LogLevel level) {
        if (level < logLevel) return;
        for (auto root: roots) {
            Log(funcName, root, level);
        }
    }

    void Log(const std::string &funcName, const std::vector<double> &vector, LogLevel level) {
        if (level < logLevel) return;
        if (!funcName.empty())
            std::cout << funcName << ":: ";
        for (auto el: vector) {
            std::cout << el << ' ';
        }
        std::cout << std::endl;
    }

    void Log(const std::string &funcName, const std::vector<std::vector<double>> &vector, LogLevel level) {
        if (level < logLevel) return;
        std::cout << funcName << "\n";
        for (int i = 0; i < vector.size(); ++i) {
            Log(std::to_string(i), vector[i], level);
        }
    }

private:
    LogLevel logLevel;
};

#endif //NUMERICALMETHODS_LOGGER_H
//
// Created by vadim on 17.02.2023.
//

#ifndef NUMERICALMETHODS_NUMERICALMETHODS_H
#define NUMERICALMETHODS_NUMERICALMETHODS_H

#include <utility>
#include <tuple>
#include <vector>
#include "Logger.h"
#include "Root.h"

class NumericalMethods {
public:
    NumericalMethods(double (*func)(double), LogLevel logLevel) {
        this->func = func;
        logger = Logger(logLevel);
    }

    Root Bisection(double a, double b, double eps = 1e-8);

    Root NewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root ModifiedNewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root TangentsMethod(double a, double b, double eps = 1e-8, double p = 1);

    std::vector<std::pair<double, double>> RootSeparation(double a, double b, int n);

private:
    double (*func)(double);

    Logger logger;

    Root GetRoot(const std::string &methodName, double x1, double x2, int counter);
};

#endif //NUMERICALMETHODS_NUMERICALMETHODS_H
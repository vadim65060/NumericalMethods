//
// Created by vadim on 17.02.2023.
//

#ifndef NUMERICALMETHODS_NUMERICALMETHODS_H
#define NUMERICALMETHODS_NUMERICALMETHODS_H

#include <utility>
#include <tuple>
#include <vector>
#include <valarray>
#include "Logger.h"
#include "Root.h"

using std::vector;
using std::pair;

class NumericalMethods {
public:
    NumericalMethods(std::function<double(double)> func, LogLevel logLevel) {
        this->func = std::move(func);
        logger = Logger(logLevel);
    }

    Root Bisection(double a, double b, double eps = 1e-8);

    Root NewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root ModifiedNewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root TangentsMethod(double a, double b, double eps = 1e-8, double p = 1);

    vector<pair<double, double>> RootSeparation(double a, double b, int n);

    vector<pair<double, double>> GetFuncValueTable(double a, double b, int n);

    vector<pair<double, double>> SortTableForDX(vector<pair<double, double>> &table, double x);

    Root InterpolationLagrangeMethod(const vector<pair<double, double>> &sortedTable, double x, int n);

    Root InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, double x, int n);

    Root InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, const vector<double> &coefficients,
                                   double x);

    vector<double> InterpolationNewtonCoefficients(const vector<pair<double, double>> &sortedTable, int n);

    std::function<double(double)>
    Polynomial(vector<pair<double, double>> &sortedTable, vector<double> &coefficients, double diff);

private:
    std::function<double(double)> func;

    static double cmpX;

    Logger logger;

    Root GetRoot(const std::string &methodName, double x1, double x2, int counter);

    static bool cmpDX(pair<double, double> a, pair<double, double> b);
};

#endif //NUMERICALMETHODS_NUMERICALMETHODS_H
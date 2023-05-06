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

    //lab1
    Root Bisection(double a, double b, double eps = 1e-8);

    Root NewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root ModifiedNewtonMethod(double a, double b, double (*df)(double), double eps = 1e-8, double p = 1);

    Root TangentsMethod(double a, double b, double eps = 1e-8, double p = 1);

    vector<pair<double, double>> RootSeparation(double a, double b, int n);

    //lab2
    vector<pair<double, double>> GetFuncValueTable(double a, double b, int n);

    vector<pair<double, double>> SortTableForDX(vector<pair<double, double>> &table, double x);

    Root InterpolationLagrangeMethod(const vector<pair<double, double>> &sortedTable, double x, int n);

    Root InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, double x, int n);

    Root InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, const vector<double> &coefficients,
                                   double x);

    vector<double> InterpolationNewtonCoefficients(const vector<pair<double, double>> &sortedTable, int n);

    //lab3
    std::function<double(double)>
    Polynomial(vector<pair<double, double>> &sortedTable, vector<double> &coefficients, double diff);

    double df(double x, double h);

    double ddf(double x, double h);

    double d4f(double x, double h);

    double TableDf(const vector<pair<double, double>> &table, int i);

    vector<double> TableDf(const vector<pair<double, double>> &table);

    double TableDdf(const vector<pair<double, double>> &table, int i);

    vector<double> TableDdf(const vector<pair<double, double>> &table);

    //lab4
    Root RightRectangleArea(double a, double b, int n);

    Root LeftRectangleArea(double a, double b, int n);

    Root MediumRectangleArea(double a, double b, int n);

    Root TrapezoidArea(double a, double b, int n);

    Root SimpsonArea(double a, double b, int n);

    Root ThreeEighthsArea(double a, double b, int n);

private:
    std::function<double(double)> func;

    static double cmpX;

    Logger logger;

    Root GetRoot(const std::string &methodName, double x1, double x2, int counter);

    static bool cmpDX(pair<double, double> a, pair<double, double> b);

    double SearchMaximumDerivative(double a, double b, int power);

    double (NumericalMethods::*derivativeFunc)(double, double);
};

#endif //NUMERICALMETHODS_NUMERICALMETHODS_H
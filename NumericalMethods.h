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

enum AreaFunc {
    LEFT_RECTANGLE_AREA,
    RIGHT_RECTANGLE_AREA,
    MEDIUM_RECTANGLE_AREA,
    TRAPEZOID_AREA,
    SIMPSON_AREA,
    THREE_EIGHTHS_AREA
};

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

    Root CalculateArea(AreaFunc areaFunc, double a, double b, int n);

    double RungeArea(AreaFunc, double a, double b, int n, int l);

private:
    std::function<double(double)> func;

    Logger logger;

    static double _cmpX;

    double (NumericalMethods::*_derivativeFunc)(double, double);

    const vector<Root (NumericalMethods::*)(double, double, int)> _areaFuncSelector = {
            &NumericalMethods::LeftRectangleArea,
            &NumericalMethods::RightRectangleArea,
            &NumericalMethods::MediumRectangleArea,
            &NumericalMethods::TrapezoidArea,
            &NumericalMethods::SimpsonArea,
            &NumericalMethods::ThreeEighthsArea
    };

    const int _areaDerivativeIndex[6] = {1, 1, 2, 2, 4, 0};

    Root GetRoot(const std::string &methodName, double x1, double x2, int counter);

    static bool cmpDX(pair<double, double> a, pair<double, double> b);

    double SearchMaximumDerivative(double a, double b, int power);
};

#endif //NUMERICALMETHODS_NUMERICALMETHODS_H
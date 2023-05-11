//
// Created by vadim on 03.05.2023.
//
#include <cassert>
#include "NumericalMethods.h"

Root NumericalMethods::CalculateArea(AreaFunc areaFunc, double a, double b, int n) {
    return (this->*_areaFuncSelector[areaFunc])(a, b, n);
}

double NumericalMethods::RungeArea(AreaFunc areaFunc, double a, double b, int n, int l) {
    Root areaN = CalculateArea(areaFunc, a, b, n);
    Root areaNL = CalculateArea(areaFunc, a, b, n * l);
    double temp = std::pow(l, _areaDerivativeIndex[areaFunc]);
    return (temp * areaNL.root - areaN.root) / (temp - 1);
}

Root NumericalMethods::LeftRectangleArea(double a, double b, int n) {
    std::string methodName = "LeftRectangleArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + h * i;
        area += func(x) * h;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");

    double delta = (b - a) * (b - a) / 2 / n * SearchMaximumDerivative(a, b, 1);
    return {area, delta, 0};
}

Root NumericalMethods::RightRectangleArea(double a, double b, int n) {
    std::string methodName = "RightRectangleArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + h * (i + 1);
        area += func(x) * h;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return {area, (b - a) * (b - a) / 2 / n * SearchMaximumDerivative(a, b, 1), 0};
}

Root NumericalMethods::MediumRectangleArea(double a, double b, int n) {
    std::string methodName = "MediumRectangleArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + h * (i + 0.5);
        area += func(x) * h;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return {area, pow((b - a), 3) / (24 * n * n) * SearchMaximumDerivative(a, b, 2), 0};
}

Root NumericalMethods::TrapezoidArea(double a, double b, int n) {
    std::string methodName = "TrapezoidArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    double x1 = a;
    for (int i = 0; i < n; ++i) {
        double x2 = a + h * (i + 1);
        area += (x2 - x1) / 2 * (func(x1) + func(x2));
        x1 = x2;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return {area, pow((b - a), 3) / (12 * n * n) * SearchMaximumDerivative(a, b, 2), 0};
}

Root NumericalMethods::SimpsonArea(double a, double b, int n) {
    std::string methodName = "SimpsonArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    double x1 = a;
    for (int i = 0; i < n; ++i) {
        double x2 = a + h * (i + 0.5);
        double x3 = a + h * (i + 1);
        area += (x3 - x1) / 6 * (func(x1) + 4 * func(x2) + func(x3));
        x1 = x3;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    double mx = SearchMaximumDerivative(a, b, 4);
    return {area, pow((b - a), 5) / (2880 * pow(n, 4)) * mx, 0};
}

Root NumericalMethods::ThreeEighthsArea(double a, double b, int n) {
    std::string methodName = "ThreeEighthsArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double h2 = h / 3;
    double area = 0;
    double x1 = a;
    for (int i = 0; i < n; ++i) {
        double x2 = a + h * (i + 1);
        area += (x2 - x1) / 8 * (func(x1) + 3 * func(x1 + h2) + 3 * func(x1 + 2 * h2) + func(x2));
        x1 = x2;
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return {area, 0, 0};
}

double NumericalMethods::SearchMaximumDerivative(double a, double b, int power) {
    int n = 1e5;
    double h = (b - a) / n;
    double derivativeH = 1e-3;
    double mx = -1;
    switch (power) {
        case 1:
            _derivativeFunc = &NumericalMethods::df;
            break;
        case 2:
            _derivativeFunc = &NumericalMethods::ddf;
            break;
        case 4:
            _derivativeFunc = &NumericalMethods::d4f;
            break;
        default:
            assert(false && "missing power");
    }
    for (int i = 0; i < n; ++i) {
        double x = a + h * i;
        double df = (this->*_derivativeFunc)(x, derivativeH);
        mx = std::max(mx, df);
    }
    return mx;
}
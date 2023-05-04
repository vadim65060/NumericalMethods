//
// Created by vadim on 03.05.2023.
//
#include "NumericalMethods.h"

double NumericalMethods::LeftRectangleArea(double a, double b, int n) {
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
    return area;
}

double NumericalMethods::RightRectangleArea(double a, double b, int n) {
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
    return area;
}

double NumericalMethods::MediumRectangleArea(double a, double b, int n) {
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
    return area;
}

double NumericalMethods::TrapezoidArea(double a, double b, int n) {
    std::string methodName = "TrapezoidArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x1 = a + h * i;
        double x2 = a + h * (i + 1);
        area += (x2 - x1) / 2 * (func(x1) + func(x2));
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return area;
}

double NumericalMethods::SimpsonArea(double a, double b, int n) {
    std::string methodName = "SimpsonArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x1 = a + h * i;
        double x2 = a + h * (i + 0.5);
        double x3 = a + h * (i + 1);
        area += (x3 - x1) / 6 * (func(x1) + 4 * func(x2) + func(x3));
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return area;
}

double NumericalMethods::ThreeEighthsArea(double a, double b, int n) {
    std::string methodName = "ThreeEighthsArea";
    logger.Log(methodName, vector{a, b, n * 1.0}, IMPORTANT);
    double h = (b - a) / n;
    double h2 = h / 3;
    double area = 0;
    for (int i = 0; i < n; ++i) {
        double x1 = a + h * i;
        double x2 = a + h * (i + 1);
        area += (x2 - x1) / 8 * (func(x1) + 3 * func(x1 + h2) + 3 * func(x1 + 2 * h2) + func(x2));
        logger.Log(methodName, area, ALL, "area");
    }
    logger.Log(methodName, area, ANSWER, "Area");
    return area;
}
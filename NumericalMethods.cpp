//
// Created by vadim on 17.02.2023.
//

#include "NumericalMethods.h"

Root NumericalMethods::Bisection(double a, double b, double eps) {
    std::string methodName = "Bisection";
    int counter = 0;
    logger.Log(methodName, {a, b}, IMPORTANT);
    do {
        counter++;
        double c = (a + b) / 2;
        if (func(a) * func(c) <= 0)
            b = c;
        else
            a = c;
        logger.Log(methodName, {a, b}, ALL);
    } while (b - a > eps);
    return GetRoot(methodName, a, b, counter);
}

std::vector<std::pair<double, double>> NumericalMethods::RootSeparation(double a, double b, int n) {
    logger.Log("RootSeparation", {a, b}, IMPORTANT);
    std::vector<std::pair<double, double>> rootsNeighborhood;
    double h = (b - a) / n;
    double x1 = a, x2 = a + h;
    double y1 = func(x1);
    while (x2 <= b) {
        double y2 = func(x2);
        if (y1 * y2 <= 0) {
            rootsNeighborhood.emplace_back(x1, x2);
        }
        x1 = x2;
        x2 += h;
        y1 = y2;
        logger.Log("RootSeparation", {x1, x2}, ALL);
    }
    logger.Log("RootSeparation", rootsNeighborhood, ANSWER);
    return rootsNeighborhood;
}

Root
NumericalMethods::NewtonMethod(double a, double b, double (*df)(double), double eps, double p) {
    std::string methodName = "NewtonMethod";
    logger.Log(methodName, {a, b}, IMPORTANT);
    double x2 = (a + b) / 2, x1 = a;
    int counter = 0;
    while (std::abs(x2 - x1) > eps) {
        counter++;
        x1 = x2 - p * func(x2) / df(x2);
        logger.Log(methodName, x1, ALL);
        std::swap(x1, x2);
    }
    return GetRoot(methodName, x1, x2, counter);
}

Root
NumericalMethods::ModifiedNewtonMethod(double a, double b, double (*df)(double), double eps, double p) {
    std::string methodName = "ModifiedNewtonMethod";
    logger.Log(methodName, {a, b}, IMPORTANT);
    double x2 = (a + b) / 2, x1 = a;
    double dfx0 = df(x2);
    int counter = 0;
    while (std::abs(x2 - x1) > eps) {
        counter++;
        x1 = x2 - p * func(x2) / dfx0;
        logger.Log(methodName, x1, ALL);
        std::swap(x1, x2);
    }
    return GetRoot(methodName, x1, x2, counter);
}

Root NumericalMethods::TangentsMethod(double a, double b, double eps, double p) {
    std::string methodName = "TangentsMethod";
    logger.Log(methodName, {a, b}, IMPORTANT);
    double x2 = a, x1 = b;
    int counter = 0;
    while (std::abs(x2 - x1) > eps) {
        counter++;
        x1 = x2 - p * func(x2) * (x2 - x1) / (func(x2) - func(x1));
        logger.Log(methodName, x1, ALL);
        std::swap(x1, x2);
    }
    return GetRoot(methodName, x1, x2, counter);
}

Root NumericalMethods::GetRoot(const std::string &methodName, double x1, double x2, int counter) {
    double x = (x1 + x2) / 2;
    double delta = std::abs(x1 - x2) / 2;
    logger.Log(methodName, Root(x, delta, counter), ANSWER);
    return {x, delta, counter};
}
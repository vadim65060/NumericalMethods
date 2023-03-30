//
// Created by vadim on 29.03.2023.
//

#include "lab1.h"

#include <cmath>
#include "../NumericalMethods.h"
#include "../Reader.h"

double func1(double x) {
    return 2 * x * x - pow(2, x) - 5;
}

double df(double x) {
    return 4 * x - pow(2, x) * std::log(2);
}

[[maybe_unused]] void lab1() {
    auto reader = Reader<double>(true);
    double a = reader.Read("a=", -3), b = reader.Read("b=", 7);
    double eps = reader.Read("eps=", 1e-5);
    int n = 100;
    std::cout << "func1(x)=2x^2-2^x-5\n";
    std::cout << "a=" << a << "; b=" << b << "; eps=" << eps << std::endl;

    auto logger = Logger(ALL);
    auto methods = NumericalMethods(func1, ANSWER);
    std::vector<std::pair<double, double>> rootsNeighborhood = methods.RootSeparation(a, b, n);
    std::cout << std::endl;

    for (auto el: rootsNeighborhood) {
        logger.Log("main", el, ALL);

        Root root = methods.Bisection(el.first, el.second, eps);
        logger.Log("main", std::abs(func1(root.root)), ALL, "|func1(x)|");

        root = methods.NewtonMethod(el.first, el.second, df, eps);
        logger.Log("main", std::abs(func1(root.root)), ALL, "|func1(x)|");

        root = methods.ModifiedNewtonMethod(el.first, el.second, df, eps);
        logger.Log("main", std::abs(func1(root.root)), ALL, "|func1(x)|");

        root = methods.TangentsMethod(el.first, el.second, eps);
        logger.Log("main", std::abs(func1(root.root)), ALL, "|func1(x)|");
        std::cout << std::endl;
    }
}
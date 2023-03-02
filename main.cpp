#include <iostream>
#include <valarray>
#include "NumericalMethods.h"

double f(double x) {
    return 2 * x * x - pow(2, x) - 5;
}

double df(double x) {
    return 4 * x - pow(2, x) * std::log(2);
}

int main() {
    double a = -3, b = 7;
    double eps = 1e-5;
    std::cout << "f(x)=2x^2-2^x-5\n";
    std::cout << "a=" << a << "; b=" << b << "; eps=" << eps << std::endl;
    int n = 100;
    auto logger= Logger(ALL);
    auto methods = NumericalMethods(f, ANSWER);
    std::vector<std::pair<double, double>> rootsNeighborhood = methods.RootSeparation(a, b, n);
    std::cout << std::endl;
    for (auto el: rootsNeighborhood) {
        logger.Log("main", el, ALL);

        Root root = methods.Bisection(el.first, el.second, eps);
        logger.Log("main",std::abs(f(root.root)),ALL,"|f(x)|");

        root = methods.NewtonMethod(el.first, el.second, df, eps);
        logger.Log("main",std::abs(f(root.root)),ALL,"|f(x)|");

        root = methods.ModifiedNewtonMethod(el.first, el.second, df, eps);
        logger.Log("main",std::abs(f(root.root)),ALL,"|f(x)|");

        root = methods.TangentsMethod(el.first, el.second, eps);
        logger.Log("main",std::abs(f(root.root)),ALL,"|f(x)|");
        std::cout << std::endl;
    }
}//230 строк
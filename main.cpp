#include <iostream>
#include <valarray>
#include "NumericalMethods.h"
#include "Reader.h"

double f(double x) {
    return 2 * x * x - pow(2, x) - 5;
}

double df(double x) {
    return 4 * x - pow(2, x) * std::log(2);
}

double f2(double x){
    return x*x;
}

void lab1() {
    auto reader = Reader<double>(true);
    double a = reader.Read("a=", -3), b = reader.Read("b=", 7);
    double eps = 1e-5;
    int n = 100;
    std::cout << "f(x)=2x^2-2^x-5\n";
    std::cout << "a=" << a << "; b=" << b << "; eps=" << eps << std::endl;

    auto logger = Logger(ALL);
    auto methods = NumericalMethods(f, ANSWER);
    std::vector<std::pair<double, double>> rootsNeighborhood = methods.RootSeparation(a, b, n);
    std::cout << std::endl;

    for (auto el: rootsNeighborhood) {
        logger.Log("main", el, ALL);

        Root root = methods.Bisection(el.first, el.second, eps);
        logger.Log("main", std::abs(f(root.root)), ALL, "|f(x)|");

        root = methods.NewtonMethod(el.first, el.second, df, eps);
        logger.Log("main", std::abs(f(root.root)), ALL, "|f(x)|");

        root = methods.ModifiedNewtonMethod(el.first, el.second, df, eps);
        logger.Log("main", std::abs(f(root.root)), ALL, "|f(x)|");

        root = methods.TangentsMethod(el.first, el.second, eps);
        logger.Log("main", std::abs(f(root.root)), ALL, "|f(x)|");
        std::cout << std::endl;
    }
}

void lab2() {
    auto reader = Reader<double>(true);
    auto intReader = Reader<int>(true);
    int m = intReader.Read("m+1=", 4) - 1;
    double a = reader.Read("a=", 1), b = reader.Read("b=", 4);
    auto methods = NumericalMethods(f2, ALL);

    std::vector<std::pair<double, double>> table = methods.GetFuncValueTable(a, b, m);
    double x = reader.Read("x=", -1);
    methods.SortTableForDX(table, x);

    int n = intReader.Read("n=", 3);
    methods.InterpolationLagrangeMethod(table, x, n);
    methods.InterpolationNewtonMethod(table, x, n);
}

int main() {
    lab2();
}
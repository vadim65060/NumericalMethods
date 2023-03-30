//
// Created by vadim on 29.03.2023.
//

#include "lab3.h"

#include <cmath>
#include "../NumericalMethods.h"
#include "../Reader.h"

double func3(double x) {
    return std::sin(x) + (x * x) / 2;
}

vector<pair<double, double>> SwapTable(const vector<pair<double, double>> &table) {
    vector<pair<double, double>> swappedTable = table;
    for (auto el: swappedTable) {
        std::swap(el.first, el.second);
    }
    return swappedTable;
}

void lab3() {
    auto reader = Reader<double>(true);
    auto intReader = Reader<int>(true);
    int m = intReader.Read("m+1=", 10) - 1;
    double a = reader.Read("a=", 0), b = reader.Read("b=", 1);
    auto methods = NumericalMethods(func3, NOTHING);
    Logger logger = Logger();
    vector<pair<double, double>> table = methods.GetFuncValueTable(a, b, m);
    vector<pair<double, double>> swappedTable = SwapTable(table);
    logger.Log("main", table, ANSWER);

    while (true) {
        double x = reader.Read("x=", 0.81);
        methods.SortTableForDX(table, x);
        methods.SortTableForDX(swappedTable, x);

        int n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 10);
        while (n > m) {
            n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 7);
        }

        Root root = methods.InterpolationNewtonMethod(swappedTable, x, n);
        std::cout << "|f(x)-F|=" << std::abs(func3(root.root) - x) << std::endl;
        std::cout << "X=" << root.root << std::endl;

        auto coefficients = methods.InterpolationNewtonCoefficients(table, n);
        auto func = methods.Polynomial(table, coefficients, x);
        auto methods2 = NumericalMethods(func, ANSWER);
        root = methods2.TangentsMethod(a, b);
        std::cout << "|f(x)-F|=" << std::abs(func3(root.root) - x) << std::endl;
        std::cout << "X=" << root.root << std::endl;
        break;
    }
}
//
// Created by vadim on 29.03.2023.
//

#include "lab2.h"

#include <cmath>
#include "../NumericalMethods.h"
#include "../Reader.h"

double func2(double x) {
    return std::sin(x) + (x * x) / 2;
}

[[maybe_unused]] void lab2() {
    auto reader = Reader<double>(true);
    auto intReader = Reader<int>(true);
    int m = intReader.Read("m+1=", 21) - 1;
    double a = reader.Read("a=", 0.4), b = reader.Read("b=", 0.9);
    auto methods = NumericalMethods(func2, IMPORTANT);

    vector<pair<double, double>> table = methods.GetFuncValueTable(a, b, m);
    while (true) {
        double x = reader.Read("x=", 0);
        methods.SortTableForDX(table, x);

        int n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 7);
        while (n > m) {
            n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 7);
        }
        methods.InterpolationLagrangeMethod(table, x, n);
        methods.InterpolationNewtonMethod(table, x, n);
        break;
    }
}
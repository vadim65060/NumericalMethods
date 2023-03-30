//
// Created by vadim on 29.03.2023.
//
#include "NumericalMethods.h"

std::function<double(double)>
NumericalMethods::Polynomial(vector<pair<double, double>> &sortedTable, vector<double> &coefficients, double diff) {

    std::function<double(double)> glambda = [=](double x) -> double {
        return InterpolationNewtonMethod(sortedTable, coefficients, x).root - diff;
    };
    return glambda;
}

double NumericalMethods::df(double x, double h, int index) {
    if (index >= 1) {
        return (func(x + h) - func(x - h)) / (2.0 * h); // Погрешность = f'''(e)/6(-h^2)
    } else {
        if (index == 0) {
            return (-3 * func(x) + 4 * func(x + h) - func(x + 2 * h)) / (2.0 * h); // Погрешность = f'''(e)/3(h^2)
        } else {
            return (3 * func(x) - 4 * func(x - h) + func(x - 2 * h)) / (2.0 * h); // Погрешность = f'''(e)/3(h^2)
        }
    }
}

double NumericalMethods::ddf(double x, double h, int index) {
    if (index < 0) {
        return 0.0 / 0.0;
    } else {
        return (func(x + h) - 2 * func(x) + func(x - h)) / (h * h);// Погрешность = h^2/12 * f^(4)(e)
    }
}
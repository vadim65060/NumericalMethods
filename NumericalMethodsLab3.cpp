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
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
        return NAN;
    } else {
        return (func(x + h) - 2 * func(x) + func(x - h)) / (h * h);// Погрешность = h^2/12 * f^(4)(e)
    }
}

double NumericalMethods::TableDf(const vector<pair<double, double>> &table, int i) {
    if (i >= 1 && i < table.size() - 1) {
        return (table[i + 1].second - table[i - 1].second) /
               (table[i + 1].first - table[i - 1].first); // Погрешность = f'''(e)/6(-h^2)
    } else {
        if (i == 0) {
            return (-3 * table[i].second + 4 * table[i + 1].second - table[i + 2].second) /
                   (table[i + 2].first - table[i].first); // Погрешность = f'''(e)/3(h^2)
        } else {
            return (3 * table[i].second - 4 * table[i - 1].second +
                    table[i - 2].second) / (table[i].first - table[i - 2].first); // Погрешность = f'''(e)/3(h^2)
        }
    }
}

vector<double> NumericalMethods::TableDf(const vector<pair<double, double>> &table) {
    vector<double> df(table.size());
    for (int i = 0; i < table.size(); ++i) {
        df[i] = TableDf(table, i);
    }
    return df;
}


double NumericalMethods::TableDdf(const vector<pair<double, double>> &table, int i) {
    if (i == 0 || i == table.size() - 1) {
        return NAN;
    } else {
        return (table[i + 1].second - 2 * table[i].second + table[i - 1].second) /
               (std::pow(table[i + 1].first - table[i].first, 2));// Погрешность = h^2/12 * f^(4)(e)
    }
}

vector<double> NumericalMethods::TableDdf(const vector<pair<double, double>> &table) {
    vector<double> ddf(table.size());
    for (int i = 0; i < table.size(); ++i) {
        ddf[i] = TableDdf(table, i);
    }
    return ddf;
}
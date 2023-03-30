//
// Created by vadim on 07.03.2023.
//
#include <algorithm>
#include "NumericalMethods.h"

double NumericalMethods::cmpX;

vector<pair<double, double>> NumericalMethods::GetFuncValueTable(double a, double b, int n) {
    vector<pair<double, double>> table;
    double h = (b - a) / n;
    for (int i = 0; i <= n; ++i) {
        double x = a + i * h;
        table.emplace_back(x, func(x));
    }
    logger.Log("GetFuncValueTable", table, IMPORTANT);
    return table;
}

vector<pair<double, double>> NumericalMethods::SortTableForDX(vector<pair<double, double>> &table, double x) {
    cmpX = x;
    std::sort(table.begin(), table.end(), cmpDX);
    logger.Log("SortTableForDX", table, IMPORTANT);
    return table;
}

bool NumericalMethods::cmpDX(pair<double, double> a, pair<double, double> b) {
    return std::abs(a.first - cmpX) <= std::abs(b.first - cmpX);
}

Root NumericalMethods::InterpolationLagrangeMethod(const vector<pair<double, double>> &sortedTable, double x, int n) {
    std::string methodName = "InterpolationLagrange";
    double P = 0;
    for (int i = 0; i <= n; ++i) {
        double a_n = 1;
        for (int j = 0; j <= n; ++j) {
            if (i == j)
                continue;
            a_n *= (x - sortedTable[j].first) / (sortedTable[i].first - sortedTable[j].first);
        }
        logger.Log(methodName, a_n, ALL);
        P += a_n * sortedTable[i].second;
    }
    double delta = std::abs(P - func(x));
    Root answer = {P, delta, 0};
    logger.Log(methodName, answer, ANSWER);
    return answer;
}

vector<double>
NumericalMethods::InterpolationNewtonCoefficients(const vector<pair<double, double>> &sortedTable, int n) {
    std::string methodName = "InterpolationNewtonCoefficients";
    vector<vector<double>> A(n + 1);
    for (int i = 0; i <= n; ++i) {
        A[i].push_back(sortedTable[i].first);
        A[i].push_back(sortedTable[i].second);
    }
    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 0; j < n - i + 2; ++j) {
            A[j].push_back((A[j + 1][i - 1] - A[j][i - 1]) / (A[j + i - 2 + 1][0] - A[j][0]));
        }
    }
    logger.Log(methodName, A, ALL);
    vector<double> coefficients(n);
    for (int i = 0; i < n; ++i) {
        coefficients[i] = A[0][i + 2];
    }
    logger.Log(methodName, coefficients, IMPORTANT);
    return coefficients;
}

Root NumericalMethods::InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable,
                                                 const vector<double> &coefficients, double x) {
    std::string methodName = "InterpolationNewton";
    double P = sortedTable[0].second;
    double dx = 1;
    for (int i = 0; i < coefficients.size(); ++i) {
        dx *= (x - sortedTable[i].first);
        P += coefficients[i] * dx;
    }
    double delta = std::abs(P - func(x));
    Root answer = {P, delta, 0};
    logger.Log(methodName, answer, ANSWER);
    return answer;
}

Root NumericalMethods::InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, double x, int n) {
    vector<double> coefficients = InterpolationNewtonCoefficients(sortedTable, n);
    return InterpolationNewtonMethod(sortedTable, coefficients, x);
}

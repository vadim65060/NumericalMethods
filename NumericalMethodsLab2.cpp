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
    logger.Log("GetFuncValueTable", table, ANSWER);
    return table;
}

vector<pair<double, double>> NumericalMethods::SortTableForDX(vector<pair<double, double>> &table, double x) {
    cmpX = x;
    std::sort(table.begin(), table.end(), cmpDX);
    logger.Log("SortTableForDX", table, ANSWER);
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

Root NumericalMethods::InterpolationNewtonMethod(const vector<pair<double, double>> &sortedTable, double x, int n) {
    std::string methodName = "InterpolationNewton";
    vector<vector<double>> A(n + 1);
    for (int i = 0; i <= n; ++i) {
        A[i].push_back(sortedTable[i].first);
        A[i].push_back(sortedTable[i].second);
    }
    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 0; j < n - i + 2; ++j) {
            A[j].push_back((A[j + 1][i - 1] - A[j][i - 1]) / (A[j + 1][0] - A[j][0]));
        }
    }
    logger.Log(methodName, A, IMPORTANT);
    double P = 0;
    double dx = 1;
    for (int i = 1; i <= n + 1; ++i) {
        dx *= (x - sortedTable[i - 1].first);
        logger.Log(methodName, dx, ALL);
        P += A[0][i] * dx;
    }
    double delta = std::abs(P - func(x));
    Root answer = {P, delta, 0};
    logger.Log(methodName, answer, ANSWER);
    return answer;
}
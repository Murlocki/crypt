//
// Created by kirill on 07.04.2025.
//

#include "library/polynoms/PolynomialSolver.h"
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include<iostream>
#include<vector>
#include<gmpxx.h>

PolynomialSolver::PolynomialSolver(const std::string &gf, const std::string &module) {
    this->gf = mpz_class(gf);
};

std::vector<mpz_class> PolynomialSolver::parsePolynomial(const std::string &polynomialStr) {
    std::string polynomialStr_modified = polynomialStr + '+';

    // Разбиваем строку полинома на слагаемые
    std::vector<std::string> elems = {};
    std::string currentElem;
    for (char s: polynomialStr_modified) {
        if (s == '-') {
            elems.emplace_back(currentElem);
            currentElem = "-";
        } else if (s == '+') {
            elems.emplace_back(currentElem);
            currentElem = "";
        } else currentElem += s;
    }

    std::vector<mpz_class> coefs = {};
    std::vector<int> degrees = {};
    for (const std::string &elem: elems) {
        std::vector<std::string> comp = split_by_string(elem, "x");
        mpz_class coef;
        int degree;
        if (comp.size() == 2) {
            coef = !comp[0].empty() ? mpz_class(comp[0]) : mpz_class(1);
            degree = !comp[1].empty() ? std::stoi(comp[1].substr(1)) : 1;
        } else {
            coef = mpz_class(comp[0]);
            degree = 0;
        }
        coefs.emplace_back(coef);
        degrees.emplace_back(degree);
    }

    std::vector<mpz_class> result;
    result.resize(degrees[0] + 1, mpz_class(0));
    for (int i = 0; i < degrees.size(); i++) {
        result[degrees[i]] = gmp_module(coefs[i], this->gf);
    }
    std::reverse(result.begin(), result.end());
    return result;
}
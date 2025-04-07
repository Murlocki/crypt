//
// Created by kirill on 07.04.2025.
//

#ifndef CRYPTO_POLYNOMIALSOLVER_H
#define CRYPTO_POLYNOMIALSOLVER_H

#include<iostream>
#include<vector>
#include<gmpxx.h>

class PolynomialSolver {
public:
    mpz_class gf;
    std::vector<mpz_class> module;
    explicit PolynomialSolver(const std::string &gf = "2", const std::string &module = "1");
    std::vector<mpz_class> parsePolynomial(const std::string &polynomialStr);
};

#endif //CRYPTO_POLYNOMIALSOLVER_H

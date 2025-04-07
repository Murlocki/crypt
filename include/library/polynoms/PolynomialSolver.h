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

    std::vector<mpz_class> parse_polynomial(const std::string &polynomial_str) const;

    std::string add_polynomial(const std::string &polynomial_first, const std::string &polynomial_second);

    std::string mult_polynomial(const std::string &polynomial_first, const std::string &polynomial_second);

private:
    std::vector<mpz_class> sum_vector_pols(const std::vector<mpz_class> &polynomial_first_vector,
                                           const std::vector<mpz_class> &polynomial_second_vector) const;

    static std::string vector_to_str(const std::vector<mpz_class> &polynomial_vector);

    static std::vector<mpz_class> calculate_deliter(const std::vector<mpz_class> &result,
                                                    const std::vector<mpz_class> &antiDelVector,
                                                    int i);

    static bool greater_vector(std::vector<mpz_class> vector_first, std::vector<mpz_class> vector_second);

    std::vector<mpz_class>
    del_vector_pols(const std::vector<mpz_class> &polynomial_vector,
                    const std::vector<mpz_class> &polynomial_del_vector);

    std::vector<mpz_class> mult_vector_pols(const std::vector<mpz_class> &polynomial_vector1,
                                            const std::vector<mpz_class> &polynomial_vector2);

};

#endif //CRYPTO_POLYNOMIALSOLVER_H

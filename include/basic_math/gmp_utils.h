//
// Created by kirill on 29.03.2025.
//

#ifndef PYBIND_EXAMPLE_GMP_UTILS_H
#define PYBIND_EXAMPLE_GMP_UTILS_H
#include <string>
mpz_class gmp_multiply(const mpz_class &a, const mpz_class &b, const mpz_class &module);
mpz_class gmp_add(const mpz_class &a, const mpz_class &b, const mpz_class &module);
mpz_class gmp_module(const mpz_class &a, const mpz_class &module);
std::string gmp_binary(const mpz_class & number);
#endif //PYBIND_EXAMPLE_GMP_UTILS_H

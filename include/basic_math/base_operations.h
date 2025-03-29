//
// Created by kirill on 29.03.2025.
//

#ifndef CRYPTO_BASE_OPERATIONS_H
#define CRYPTO_BASE_OPERATIONS_H
#include<iostream>
#include<gmpxx.h>
mpz_class fast_degree(const mpz_class &number,const mpz_class &degree,const mpz_class &module);
std::string fast_degree(const std::string& number,const std::string& degree,const std::string& module);
mpz_class euler(const mpz_class &number);
std::string euler(const std::string &number);
#endif //CRYPTO_BASE_OPERATIONS_H

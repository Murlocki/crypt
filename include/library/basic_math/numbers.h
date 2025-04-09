//
// Created by kirill on 09.04.2025.
//

#ifndef CRYPTO_NUMBERS_H
#define CRYPTO_NUMBERS_H
#include<gmpxx.h>
#include<vector>
#include<string>
using std::string, std::vector;
string generate_mersenne_prime(const string& number);
mpz_class generate_mersenne_prime(const mpz_class& number);
bool is_prime(const mpz_class& n);
mpz_class generate_fermat_prime(const mpz_class& number);
string generate_fermat_prime(const string& number);
#endif //CRYPTO_NUMBERS_H

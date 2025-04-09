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
bool fermat_test(const mpz_class& n, const mpz_class& iterations = 5);
bool fermat_test(const string& n, const string& iterations = "5");
bool trial_division_test(const mpz_class& n);
bool trial_division_test(const string& n);
bool miller_rabin_test(const string& n,  const string& k = "5");
bool miller_rabin_test(const mpz_class& n, const mpz_class &k = 5);
#endif //CRYPTO_NUMBERS_H

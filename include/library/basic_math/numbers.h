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
vector<string> fermat_factorization(const string& n);
vector<mpz_class> fermat_factorization(const mpz_class& n);
vector<string> pollard_p_minus_1(const string& n, const string& B);
vector<mpz_class> pollard_p_minus_1(const mpz_class& n, const mpz_class& B);
vector<mpz_class> pollard_rho(const mpz_class& n);
vector<string> pollard_rho(const string& n);
#endif //CRYPTO_NUMBERS_H

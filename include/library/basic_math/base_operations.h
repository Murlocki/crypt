#ifndef CRYPTO_BASE_OPERATIONS_H
#define CRYPTO_BASE_OPERATIONS_H
#include<iostream>
#include"gmpxx.h"
#include<vector>
#include <set>

mpz_class fast_degree(const mpz_class &number,const mpz_class &degree,const mpz_class &module);
std::string fast_degree(const std::string& number,const std::string& degree,const std::string& module);


mpz_class euler(const mpz_class &number);
std::string euler(const std::string &number);

mpz_class euler_def(const mpz_class &number);
std::string euler_def(const std::string &number);

std::vector<mpz_class> extended_gcd(const mpz_class &a, const mpz_class &b, const bool &printing);
std::vector<std::string> extended_gcd(const std::string &a, const std::string &b, const bool &printing);

std::string inverse_element(const std::string &number, const std::string &module);
mpz_class inverse_element(const mpz_class &number, const mpz_class &module);

std::vector<mpz_class> solve_linear_congruence(const mpz_class &a, const mpz_class &b, const mpz_class &module);
std::vector<std::string> solve_linear_congruence(const std::string &a, const std::string &b, const std::string &module);


bool check_coprime_coefs(const std::vector<std::vector<mpz_class>> &coefs);
std::vector<mpz_class> solve_lefts_coprime(const std::vector<std::vector<mpz_class>> &coefs);
bool check_no_coprime_coefs(const std::vector<std::vector<mpz_class>> &coefs);
std::vector<mpz_class> solve_lefts_not_coprime(const std::vector<std::vector<mpz_class>> &coefs);
std::vector<mpz_class> solve_lefts(const std::vector<std::vector<mpz_class>> &coefs);
std::vector<std::string> solve_lefts(const std::vector<std::vector<std::string>> &coefs);


std::vector<std::vector<mpz_class>> solve_diofant_equation(const mpz_class &a, const mpz_class &b, const mpz_class& d);
std::vector<std::vector<std::string>> solve_diofant_equation(const std::string &a, const std::string &b, const std::string& d);

std::vector<mpz_class> find_prime_dels(const mpz_class &number);
std::vector<std::string> find_prime_roots(const std::string &module);
std::vector<mpz_class> find_prime_roots(const mpz_class &module);


mpz_class legendre_symbol(const mpz_class& a, const mpz_class &p);
std::vector<mpz_class> tonelli_shanks(const mpz_class& a, const mpz_class& p);
std::vector<std::pair<mpz_class, mpz_class>> factorize(mpz_class n);
std::vector<mpz_class> solve_quadratic_congruence(const mpz_class& a, const mpz_class& m);
std::vector<std::string> solve_quadratic_congruence(const std::string &a, const std::string &m);

std::pair<std::vector<mpz_class>,std::vector<mpz_class>> find_quadratic_residues_nonresidues(const mpz_class &module);
std::pair<std::vector<std::string>,std::vector<std::string>> find_quadratic_residues_nonresidues(const std::string &module);

#endif //CRYPTO_BASE_OPERATIONS_H

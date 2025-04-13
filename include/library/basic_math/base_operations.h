#ifndef CRYPTO_BASE_OPERATIONS_H
#define CRYPTO_BASE_OPERATIONS_H
#include<iostream>
#include"gmpxx.h"
#include<vector>
#include <set>
#include <unordered_map>

mpz_class fast_degree(const mpz_class &number,const mpz_class &degree,const mpz_class &module = 1);
std::string fast_degree(const std::string& number,const std::string& degree,const std::string& module ="1");


mpz_class euler(const mpz_class &number);
std::string euler(const std::string &number);

mpz_class euler_def(const mpz_class &number);
std::string euler_def(const std::string &number);

std::vector<mpz_class> extended_gcd(const mpz_class &a, const mpz_class &b);
std::vector<std::string> extended_gcd(const std::string &a, const std::string &b);

std::string inverse_element(const std::string &number, const std::string &module);
mpz_class inverse_element(const mpz_class &number, const mpz_class &module);


std::vector<mpz_class> find_prime_dels(const mpz_class &number);
std::vector<std::string> find_prime_roots(const std::string &module);
std::vector<mpz_class> find_prime_roots(const mpz_class &module);

std::unordered_map<std::string,std::vector<std::string>> create_circle_classes(const std::string & degree,const std::string & multiplyer);
std::unordered_map<std::string,std::vector<mpz_class>> create_circle_classes(const mpz_class& degree,const mpz_class& multiplyer);

std::unordered_map<std::string, std::string> return_polynomoms_for_cycle_classes(const mpz_class& degree,const mpz_class& multiplyer);
std::unordered_map<std::string, std::string> return_polynomoms_for_cycle_classes(const std::string & degree,const std::string & multiplyer);
#endif //CRYPTO_BASE_OPERATIONS_H

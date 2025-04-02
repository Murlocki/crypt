#include "gmpxx.h"
#include<string>
#include<iostream>
using namespace std;
mpz_class gmp_module(const mpz_class &a, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class mod = 1;
    mpz_mmod(mod.get_mpz_t(),a.get_mpz_t(),module.get_mpz_t());
    return mod;
}
mpz_class gmp_multiply(const mpz_class &a, const mpz_class &b, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class product = a * b;
    if(module>1) product = gmp_module(product,module);

    return product;
}

mpz_class gmp_add(const mpz_class &a, const mpz_class &b, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class sum = a + b;
    if(module>1) sum = gmp_module(sum,module);
    return sum;
}

mpz_class gmp_div(const mpz_class &a, const mpz_class &b) {
    mpz_class result = 1;
    mpz_mdiv(result.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return result;
}


std::string gmp_binary(const mpz_class & number) {
    if(number<1) throw std::invalid_argument("Number cannot be lesser than 1");
    return number.get_str(2); // Base 2 (binary) representation
}
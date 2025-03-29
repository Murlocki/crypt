//
// Created by kirill on 29.03.2025.
//
#include<iostream>
#include "gmpxx.h"
#include<string>
using namespace std;

std::string gmp_multiply(const std::string& a, const std::string& b, const std::string& module) {
    mpz_class x(a), y(b), m(module);
    if(m<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class product = x * y;
    if(m>1) product = product % m;

    // Возвращаем строку, так как результат может быть большим
    return product.get_str();
}

std::string gmp_add(const std::string& a, const std::string& b, const std::string& module) {
    mpz_class x(a), y(b), m(module);
    if(m<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class sum = x + y;
    if(m>1) sum = sum % m;

    // Возвращаем строку, так как результат может быть большим
    return sum.get_str();
}

std::string gmp_module(const std::string& a, const std::string& module) {
    mpz_class x(a), m(module);
    if(m<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class mod = x % m;
    // Возвращаем строку, так как результат может быть большим
    return mod.get_str();
}
std::string gmp_binary(const std::string& number) {
    mpz_class num(number);
    if(num<1) throw std::invalid_argument("Number cannot be lesser than 1");
    return num.get_str(2); // Base 2 (binary) representation
}
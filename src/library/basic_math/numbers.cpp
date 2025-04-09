//
// Created by kirill on 09.04.2025.
//

#include "library/basic_math/numbers.h"
#include "library/basic_math/base_operations.h"
#include<gmpxx.h>
#include<vector>
#include<string>
using std::string, std::vector;

// Функция проверки числа на простоту (упрощенная)
bool is_prime(const mpz_class& n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (mpz_class i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Функция для генерации чисел Мерсенна
mpz_class generate_mersenne_prime(const mpz_class& number) {
    mpz_class p = 2;
    if(!is_prime(number)) throw std::invalid_argument("Number must be prime");
    return fast_degree(2,number)-1;
}
// Функция для генерации чисел Мерсенна
string generate_mersenne_prime(const string& number) {
    return generate_mersenne_prime(mpz_class(number)).get_str();
}


// Функция для генерации чисел Ферма
mpz_class generate_fermat_prime(const mpz_class& number) {
    mpz_class p = 2;
    return fast_degree(2,fast_degree(2,number))+1;
}
// Функция для генерации чисел Мерсенна
string generate_fermat_prime(const string& number) {
    return generate_fermat_prime(mpz_class(number)).get_str();
}
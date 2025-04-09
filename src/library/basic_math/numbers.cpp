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

// Тест Ферма (возвращает true, если число вероятно простое)
bool fermat_test(const mpz_class& n, const mpz_class& iterations) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    for (int i = 0; i < iterations; ++i) {
        mpz_class a = 2 + rand() % (n - 3); // Случайное основание 2 ≤ a ≤ n-2
        if (fast_degree(a, n - 1, n) != 1) {
            return false; // Число составное
        }
    }
    return true; // Вероятно простое
}
bool fermat_test(const string& n, const string& iterations) {
    return fermat_test(mpz_class(n),mpz_class(iterations));
}

// Тест квадратным корнем
bool trial_division_test(const mpz_class& n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for(mpz_class i = 1;i<n;i++) {
        if(fast_degree(i,2,n) == 1 && i != 1 && i != n - 1) return false;
    }
    return true;
}
bool trial_division_test(const string& n){
    return trial_division_test(mpz_class(n));
}


bool miller_rabin_test(const string& n, const string& k) {
    return miller_rabin_test(mpz_class(n),mpz_class(k));
}
bool miller_rabin_test(const mpz_class& n, const mpz_class &k) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    // Представим n-1 как d * 2^s
    mpz_class d = n - 1;
    mpz_class s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s += 1;
    }

    for (int i = 0; i < k; ++i) {
        mpz_class a = 2 + rand() % (n - 3);
        mpz_class x = fast_degree(a, d, n);

        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (mpz_class j = 0; j < s - 1; ++j) {
            x = fast_degree(x, 2, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
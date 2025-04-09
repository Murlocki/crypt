//
// Created by kirill on 09.04.2025.
//

#include "library/basic_math/numbers.h"
#include "library/basic_math/base_operations.h"
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
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


vector<mpz_class> fermat_factorization(const mpz_class& n) {
    if(gmp_module(n,2)==0)throw std::invalid_argument("N must be odd");
    mpz_class a, b, b2;
    mpz_sqrt(a.get_mpz_t(), n.get_mpz_t());
    a += 1;
    b2 = a * a - n;

    while (mpz_perfect_square_p(b2.get_mpz_t()) == 0) {
        a += 1;
        b2 = a * a - n;
    }

    mpz_sqrt(b.get_mpz_t(), b2.get_mpz_t());
    return {(a - b), (a + b)};
}
vector<string> fermat_factorization(const string& n){
    return mpz_to_strings(fermat_factorization(mpz_class(n)));
}


vector<mpz_class> pollard_p_minus_1(const mpz_class& n, const mpz_class& B) {
    mpz_class a = 2;
    mpz_class d;

    for (mpz_class p = 2; p <= B; mpz_nextprime(p.get_mpz_t(), p.get_mpz_t())) {
        mpz_pow_ui(a.get_mpz_t(), a.get_mpz_t(), mpz_get_ui(p.get_mpz_t()));
        a %= n;
    }

    mpz_sub_ui(d.get_mpz_t(), a.get_mpz_t(), 1);
    mpz_gcd(d.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

    if (d > 1 && d < n) return {d,n/d};
    return {1,n};
}

vector<string> pollard_p_minus_1(const string& n, const string& B){
    return mpz_to_strings(pollard_p_minus_1(mpz_class(n),mpz_class(B)));
}


vector<mpz_class> pollard_rho(const mpz_class& n) {
    if (n % 2 == 0) return {2,n/2};

    mpz_class x = 2, y = 2, d = 1;
    mpz_class c = 1;

    auto f = [&](const mpz_class& val) { return gmp_add(val * val,c, n); };

    while (d == 1) {
        x = f(x);
        y = f(f(y));
        mpz_sub(d.get_mpz_t(), x.get_mpz_t(), y.get_mpz_t());
        mpz_abs(d.get_mpz_t(), d.get_mpz_t());
        mpz_gcd(d.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    }

    return {d,n/d};
}
vector<string> pollard_rho(const string& n){
    return mpz_to_strings(pollard_rho(mpz_class(n)));
}
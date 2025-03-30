#include "gmpxx.h"
#include<string>
using namespace std;
mpz_class gmp_module(const mpz_class &a, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class mod = 1;
    mpz_mmod(mod.get_mpz_t(),a.get_mpz_t(),module.get_mpz_t());
    // Возвращаем строку, так как результат может быть большим
    return mod;
}
mpz_class gmp_multiply(const mpz_class &a, const mpz_class &b, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class product = a * b;
    if(module>1) product = gmp_module(product,module);

    // Возвращаем строку, так как результат может быть большим
    return product;
}

mpz_class gmp_add(const mpz_class &a, const mpz_class &b, const mpz_class &module) {
    if(module<1) throw std::invalid_argument("Module cannot be lesser than 1");
    // Умножаем и берем по модулю
    mpz_class sum = a + b;
    if(module>1) sum = gmp_module(sum,module);

    // Возвращаем строку, так как результат может быть большим
    return sum;
}
std::string gmp_binary(const mpz_class & number) {
    if(number<1) throw std::invalid_argument("Number cannot be lesser than 1");
    return number.get_str(2); // Base 2 (binary) representation
}
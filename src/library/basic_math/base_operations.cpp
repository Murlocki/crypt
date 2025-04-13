#include<gmpxx.h>
#include<library/basic_math/gmp_utils.h>
#include<library/basic_math/base_operations.h>
#include<library/extra_functions/convertions.h>
#include<vector>
#include <format>
#include <set>
#include <functional>
#include "library/basic_math/chinese_lefts.h"

using namespace std;

// Function for fast degree alg
mpz_class fast_degree(const mpz_class &number, const mpz_class &degree, const mpz_class &module) {
    if (degree < 0) throw std::invalid_argument("Degree cannot be lesser than 1");
    else if (degree == 0) return 1;
    // Get degree in binary
    const std::string binary_degree = gmp_binary(degree);

    // Main cycle of alg
    mpz_class result = mpz_class("1");
    for (int i = 0; i < binary_degree.size(); i++) {
        if (binary_degree[i] == '1') {
            result = gmp_multiply(result, number, module);
        }
        if (i != binary_degree.size() - 1) result = gmp_multiply(result, result, module);
    }
    return result;
}

// Function for call fast degree alg from python
std::string fast_degree(const std::string &number, const std::string &degree, const std::string &module) {
    mpz_class number_int = mpz_class(number);
    mpz_class degree_int = mpz_class(degree);
    mpz_class module_int = mpz_class(module);
    return fast_degree(number_int, degree_int, module_int).get_str();
}


// Function for slow calc euler function
mpz_class euler(const mpz_class &number) {
    mpz_class result = 0;
    for (mpz_class i = 1; i < number; i++) {
        mpz_class gcd_int = 1;
        mpz_gcd(gcd_int.get_mpz_t(), i.get_mpz_t(), number.get_mpz_t());
        if (gcd_int == 1) {
            result += 1;
        }
    }
    return result;
}

// Function for call euler func from python
std::string euler(const std::string &number) {
    mpz_class number_int = mpz_class(number);
    return euler(number_int).get_str();
}

// Function for calc euler function vid definition
mpz_class euler_def(const mpz_class &number) {
    mpz_class result = number;
    std::vector<mpz_class> prime_dels = find_prime_dels(number);
    prime_dels.push_back(number);
    for (const mpz_class &del: prime_dels) {
        result = result * (del - 1) / del;
    }
    return result;
}

// Function for call euler func from python
std::string euler_def(const std::string &number) {
    mpz_class number_int = mpz_class(number);
    return euler_def(number_int).get_str();
}

//Extended gcd
std::vector<mpz_class> extended_gcd(const mpz_class &a, const mpz_class &b) {
    // Получаем модули чисел
    mpz_class a_abs;
    mpz_class b_abs;
    mpz_abs(a_abs.get_mpz_t(), a.get_mpz_t());
    mpz_abs(b_abs.get_mpz_t(), b.get_mpz_t());

    mpz_class first = a_abs > b_abs ? a_abs : b_abs;
    mpz_class second = a_abs < b_abs ? a_abs : b_abs;
    mpz_class s1 = 1;
    mpz_class s2 = 0;
    mpz_class t1 = 0;
    mpz_class t2 = 1;
    vector<mpz_class> result = {first, s1, t1};
    while (second != 0) {
        mpz_class q = 1;
        mpz_tdiv_q(q.get_mpz_t(), first.get_mpz_t(), second.get_mpz_t());
        mpz_class r = 1;
        mpz_mmod(r.get_mpz_t(), first.get_mpz_t(), second.get_mpz_t());
        mpz_class s = s1 - q * s2;
        mpz_class t = t1 - q * t2;
        result = {second, s2, t2};
        first = second, second = r, s1 = s2, s2 = s, t1 = t2, t2 = t;

    }
    if (a_abs < b_abs) {
        mpz_class temp = result[1];
        result[1] = result[2];
        result[2] = temp;
    }
    result[1] *= mpz_sgn(a.get_mpz_t());
    result[2] *= mpz_sgn(b.get_mpz_t());
    return result;
}

//Function for call extended gcd from python
std::vector<std::string> extended_gcd(const std::string &a, const std::string &b) {
    mpz_class first = mpz_class(a);
    mpz_class second = mpz_class(b);
    std::vector<mpz_class> result = extended_gcd(first, second);
    return mpz_to_strings(result);
}

// Calc inverse of number in module m
mpz_class inverse_element(const mpz_class &number, const mpz_class &module) {
    // Find number mod module
    mpz_class number_mod = gmp_module(number, module);

    // Get extended gcd coefs
    std::vector<mpz_class> extend_gcd = extended_gcd(number_mod, module);
    if (extend_gcd[0] != 1) throw std::invalid_argument("Number and module must be co-prime");
    return gmp_module(extend_gcd[1], module);
}

// Func for call of inverse elem calculation from python
std::string inverse_element(const std::string &number, const std::string &module) {
    mpz_class number_int = mpz_class(number);
    mpz_class module_int = mpz_class(module);
    if (module_int < 0) throw std::invalid_argument("Module must be positive");
    return inverse_element(number_int, module_int).get_str();
}


// Function for finding prime roots of module field
std::vector<mpz_class> find_prime_roots(const mpz_class &module) {
    std::vector<mpz_class> result = {};

    mpz_class euler_value = euler(module);
    std::vector<mpz_class> prime_dels = find_prime_dels(euler_value);
    mpz_class root = 2;
    while (root != module) {
        bool ok = true;
        for (const mpz_class &del: prime_dels) {
            if (fast_degree(root, gmp_div(euler_value, del), module) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) break;
        root += 1;
    }
    if (root == module) return result;
    result.push_back(root);
    for (mpz_class i = 2; i < euler_value; i++) {
        mpz_class gcd = 1;
        mpz_gcd(gcd.get_mpz_t(), i.get_mpz_t(), euler_value.get_mpz_t());
        if (gcd == 1) result.push_back(fast_degree(root, i, module));
    }
    return result;

}

// Function for calling finding of prime roots from python
std::vector<string> find_prime_roots(const string &module) {
    return mpz_to_strings(find_prime_roots(mpz_class(module)));
}

// Function for finding all prime dels of number
std::vector<mpz_class> find_prime_dels(const mpz_class &number) {
    std::vector<mpz_class> result = {};
    mpz_class current_number = number;
    for (mpz_class i = 2; i <= current_number / 2; i++) {
        if (gmp_module(current_number, i) == 0) {
            result.push_back(i);
            while (gmp_module(current_number, i) == 0) {
                current_number = gmp_div(current_number, i);
            }
        }
    }
    return result;
}



std::unordered_map<string,std::vector<mpz_class>> create_circle_classes(const mpz_class& degree,const mpz_class& multiplyer) {
    std::set<mpz_class> seen = {0};
    std::unordered_map<string,std::vector<mpz_class>> circle_classes;
    circle_classes["0"]={};
    for(mpz_class i = 1; i< fast_degree(multiplyer,degree) - 1;i++){
        mpz_class current_degree = i;
        if(seen.contains(current_degree)) continue;
        std::set<mpz_class> current_cycle = {};
        while(!current_cycle.contains(current_degree)){
            current_cycle.insert(current_degree);
            seen.insert(current_degree);
            current_degree = gmp_module(current_degree * multiplyer,fast_degree(multiplyer,degree) - 1);
        }
        std::vector<mpz_class> cycle_vector(current_cycle.begin(), current_cycle.end());
        circle_classes[i.get_str()] = cycle_vector;
    }
    return circle_classes;
}

std::unordered_map<string,std::vector<string>> create_circle_classes(const string & degree,const string & multiplyer) {
    mpz_class degree_int = mpz_class(degree);
    mpz_class multiplyer_int = mpz_class(multiplyer);

    std::unordered_map<string,std::vector<mpz_class>> cycles = create_circle_classes(degree_int,multiplyer_int);
    std::unordered_map<string,std::vector<string>> result;
    for (const auto& [key, vals] : cycles) {
        result[key] = mpz_to_strings(vals);
    }

    return result;
}

std::unordered_map<string, string> return_polynomoms_for_cycle_classes(const mpz_class& degree,const mpz_class& multiplyer) {
    std::unordered_map<string, vector<mpz_class>> cycles = create_circle_classes(degree, multiplyer);
    std::unordered_map<string, string> result;
    mpz_class root = find_prime_roots(fast_degree(multiplyer,degree))[0];
    result["0"] = "M(g)=0";
    for (const auto &[start, cycle]: cycles) {
        if (start == "0") continue;
        string pol = std::format("M{:}(g)=", start);
        for (const auto& element: cycles[start]) {
            mpz_class current_el = element;
            pol += std::format("(g+{:})", current_el.get_str());
        }
        result[start] = pol;
    }
    return result;
}
std::unordered_map<string, string> return_polynomoms_for_cycle_classes(const string & degree,const string & multiplyer) {
    mpz_class degree_int = mpz_class(degree);
    mpz_class multuplyer_int = mpz_class(multiplyer);
    std::unordered_map<string, string> result = return_polynomoms_for_cycle_classes(degree_int,multuplyer_int);
    return result;
}
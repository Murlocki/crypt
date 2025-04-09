//
// Created by kirill on 07.04.2025.
//

#ifndef CRYPTO_POLYNOMIALSOLVER_H
#define CRYPTO_POLYNOMIALSOLVER_H

#include<iostream>
#include<vector>
#include<gmpxx.h>
#include<unordered_map>
using std::vector,std::string,std::cout,std::endl;

class PolynomialSolver {
public:
    mpz_class gf;
    vector<mpz_class> module;

    explicit PolynomialSolver(const string &gf = "2", const string &module = "1");

    static vector<mpz_class> parse_polynomial(const string &polynomial_str, const mpz_class &gf);

    string add_polynomial(const string &polynomial_first, const string &polynomial_second);

    string mult_polynomial(const string &polynomial_first, const string &polynomial_second);

    static std::unordered_map<int,vector<vector<mpz_class>>> create_not_priv_pol_list(int degree, mpz_class gf);

    static bool prove_priv_polynomial(const string& pol,const string& gf);

    static bool check_if_prime_pol(const string& pol, const string& gf);

    vector<vector<mpz_class>> create_galue_elems();

    bool check_if_prim_elem(const string &elem);

    std::unordered_map<string, string> return_polynomoms_for_cycle_classes();
private:
    [[nodiscard]] vector<mpz_class> sum_vector_pols(const vector<mpz_class> &polynomial_first_vector,
                                           const vector<mpz_class> &polynomial_second_vector) const;

    static string vector_to_str(const vector<mpz_class> &polynomial_vector);

    static vector<mpz_class> calculate_deliter(const vector<mpz_class> &result,
                                                    const vector<mpz_class> &antiDelVector,
                                                    int i);

    static bool greater_vector(vector<mpz_class> vector_first, vector<mpz_class> vector_second);

    vector<mpz_class>
    del_vector_pols(const vector<mpz_class> &polynomial_vector,
                    const vector<mpz_class> &polynomial_del_vector);

    vector<mpz_class> mult_vector_pols(const vector<mpz_class> &polynomial_vector1,
                                            const vector<mpz_class> &polynomial_vector2);

    vector<mpz_class> number_to_base(const mpz_class& num);

    static bool check_if_priv_pol(const vector<mpz_class>& pol_vector, const mpz_class &gf);

    bool check_if_prim_elem(vector<mpz_class> elem);
};

#endif //CRYPTO_POLYNOMIALSOLVER_H

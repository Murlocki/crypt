#include<library/basic_math/base_operations.h>
#include<iostream>
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include "library/polynoms/PolynomialSolver.h"
#include "library/basic_math/numbers.h"
#include "library/codes/DES.h"

int main() {
    auto a = PolynomialSolver("2", "x^3+x+1");
    cout << a.add_polynomial("x^2+1", "1") << endl;
    PolynomialSolver::create_not_priv_pol_list(4, 2);
    //cout<<PolynomialSolver::prove_priv_polynomial("x^2+x+1","2")<<endl;
    //cout<<PolynomialSolver::check_if_prime_pol("x^4+x^3+x^2+x+1","2")<<endl;
    for (auto [degree, elem]: create_circle_classes("3", "2")) {
        for (auto x: elem) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    cout << a.check_if_prim_elem("x") << endl;
    for (const auto &[degree, pol]: return_polynomoms_for_cycle_classes("3", "2")) {
        cout << degree << " " << pol << endl;
    }
    cout << generate_mersenne_prime(5);
    cout << fermat_test(22);
    cout << trial_division_test(23) << endl;
    cout << miller_rabin_test(23) << endl;

    for (auto x: fermat_factorization(45))cout << x << " ";
    cout << endl;
    for (auto x: pollard_p_minus_1(45, 4))cout << x << " ";
    cout << endl;
    for (auto x: pollard_rho(45))cout << x << " ";
    cout << endl;
    try {
        DES d("1010101010111011000010010001100000100111001101101100110011011101");
        std::string result1 = d.encrypt("0001001000110100010101101010110000010011000100110010010100110110");
        std::cout << "Encrypted: " << result1 << std::endl;

        std::string result = d.decrypt("0010000100101000101010011101100000100111001000100001100011111001");
        std::cout << "Decrypted: " << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}


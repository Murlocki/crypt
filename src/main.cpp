#include<library/basic_math/base_operations.h>
#include<iostream>
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include "library/polynoms/PolynomialSolver.h"
int main() {
    auto a = PolynomialSolver("2","x^2+x+1");
    cout<<a.add_polynomial("x^2+1","1")<<endl;
    PolynomialSolver::create_not_priv_pol_list(4,2);
    cout<<PolynomialSolver::prove_priv_polynomial("x^2+x+1","2")<<endl;
    cout<<PolynomialSolver::check_if_prime_pol("x^4+x^3+x^2+x+1","2")<<endl;
    return 0;
}

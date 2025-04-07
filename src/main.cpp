#include<library/basic_math/base_operations.h>
#include<iostream>
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include "library/polynoms/PolynomialSolver.h"
int main() {
    auto a = PolynomialSolver("2","x^3+3x+1");
    for(auto x: a.parsePolynomial("x")){
        std::cout<<x<<" ";
    }
    return 0;
}

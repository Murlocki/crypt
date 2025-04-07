#include<library/basic_math/base_operations.h>
#include<iostream>
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include "library/polynoms/PolynomialSolver.h"
int main() {
    auto a = PolynomialSolver("3","x^4");
//    for(auto x: a.parse_polynomial("x")){
//        std::cout<<x<<" ";
//    }
    std::cout<<a.mult_polynomial("2x^3+1","2x^3+2");
    return 0;
}

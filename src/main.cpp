#include<library/basic_math/base_operations.h>
#include<iostream>
int main() {
    //extended_gcd("2","3",true);
    //std::cout<<inverse_element("2","3");
    //std::cout<<mpz_class(-1) % mpz_class(3);
    //std::cout<<solve_lefts({{2,3},{3,5},{2,7}})[0];
    //std::cout<<solve_lefts({{1,2},{2,3},{3,4}})[0];
    //std::cout<<find_prime_roots(7)[0];
//    auto solutions = tonelli_shanks(4, 5);
//
//    if (solutions.empty()) {
//        std::cout << "No solutions" << std::endl;
//    } else {
//        std::cout << "Solution ";
//        for (auto x : solutions) {
//            std::cout << x << " ";
//        }
//        std::cout << std::endl;
//    }
    auto solutions = solve_quadratic_congruence(5,300);
    if (solutions.empty()) {
        std::cout << "No solutions" << std::endl;
    } else {
        std::cout << "Solution ";
        for (auto x : solutions) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

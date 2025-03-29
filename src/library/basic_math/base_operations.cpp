//
// Created by kirill on 29.03.2025.
//
#include<gmpxx.h>
#include<gmp.h>
#include<basic_math/gmp_utils.h>
#include<basic_math/base_operations.h>
using namespace std;

// Function for fast degree alg
mpz_class fast_degree(const mpz_class &number,const mpz_class &degree,const mpz_class &module){
    // Get degree in binary
    const std::string binary_degree = gmp_binary(degree);

    // Main cycle of alg
    mpz_class result = mpz_class("1");
    for(int i=0;i<binary_degree.size();i++){
        if(binary_degree[i]=='1'){
            result = gmp_multiply(result,number,module);
        }
        if(i!=binary_degree.size()-1) result = gmp_multiply(result,result,module);
    }
    return result;
}
// Function for call fast degree alg
std::string fast_degree(const std::string& number,const std::string& degree,const std::string& module){
    mpz_class number_int = mpz_class(number);
    mpz_class degree_int = mpz_class(degree);
    mpz_class module_int = mpz_class(module);
    return fast_degree(number_int,degree_int,module_int).get_str();
}


// Function for slow calc euler function
mpz_class euler(const mpz_class &number){
   mpz_class result = 0;
   for(mpz_class i = 1;i<number;i++){
       mpz_class gcd_int = 1;
       mpz_gcd(gcd_int.get_mpz_t(), i.get_mpz_t(), number.get_mpz_t());
       if(gcd_int == 1){
           result +=1;
       }
   }
   return result;
}
// Function for call euler func
std::string euler(const std::string &number){
    mpz_class number_int = mpz_class(number);
    return euler(number_int).get_str();
}



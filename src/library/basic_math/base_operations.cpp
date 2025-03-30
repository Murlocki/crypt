#include<gmpxx.h>
#include<gmp.h>
#include<library/basic_math/gmp_utils.h>
#include<library/basic_math/base_operations.h>
#include<library/extra_functions/convertions.h>
#include<vector>
#include <format>

using namespace std;

// Function for fast degree alg
mpz_class fast_degree(const mpz_class &number,const mpz_class &degree,const mpz_class &module){
    if(degree<1) throw std::invalid_argument("Degree cannot be lesser than 1");

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
// Function for call fast degree alg from python
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
// Function for call euler func from python
std::string euler(const std::string &number){
    mpz_class number_int = mpz_class(number);
    return euler(number_int).get_str();
}

//Extended gcd
std::vector<mpz_class> extended_gcd(const mpz_class &a, const mpz_class &b, const bool &printing){
    // Получаем модули чисел
    mpz_class a_abs;
    mpz_class b_abs;
    mpz_abs(a_abs.get_mpz_t(),a.get_mpz_t());
    mpz_abs(b_abs.get_mpz_t(),b.get_mpz_t());

    mpz_class first = a_abs>b_abs? a_abs:b_abs;
    mpz_class second = a_abs<b_abs? a_abs:b_abs;
    mpz_class s1 = 1;
    mpz_class s2 = 0;
    mpz_class t1 = 0;
    mpz_class t2 = 1;
    vector<mpz_class> result = {first, s1, t1};
    while(second!=0){
        mpz_class q = 1;
        mpz_tdiv_q(q.get_mpz_t(), first.get_mpz_t(), second.get_mpz_t());
        mpz_class r = 1;
        mpz_mmod(r.get_mpz_t(), first.get_mpz_t(), second.get_mpz_t());
        mpz_class s = s1 - q * s2;
        mpz_class t = t1 - q * t2;
        if(printing) std::cout << std::format("Euclid coefficients: q:{} r1:{} r2:{} r:{} s1:{} s2:{} s:{} t1:{} t2:{} t:{}\n",
                                 q.get_str(), first.get_str(), second.get_str(), r.get_str(), s1.get_str(),
                                 s2.get_str(), s.get_str(), t1.get_str(), t2.get_str(), t.get_str());
        result = { second, s, t };
        first = second, second = r, s1 = s2, s2 = s, t1 = t2, t2 = t;

    }
    if(a_abs<b_abs){
        mpz_class temp = result[1];
        result[1] = result[2];
        result[2] = temp;
    }
    result[1] *= mpz_sgn(a.get_mpz_t());
    result[2] *= mpz_sgn(b.get_mpz_t());
    return result;
}
//Function for call extended gcd from python
std::vector<std::string> extended_gcd(const std::string &a, const std::string &b,const bool &printing){
    mpz_class first = mpz_class(a);
    mpz_class second = mpz_class(b);
    std::vector<mpz_class > result = extended_gcd(first, second, printing);
    return mpz_to_strings(result);
}



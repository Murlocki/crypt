#include<gmpxx.h>
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
std::vector<mpz_class> extended_gcd(const mpz_class &a, const mpz_class &b, const bool &printing = false){
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
        result = { second, s2, t2 };
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
std::vector<std::string> extended_gcd(const std::string &a, const std::string &b,const bool &printing = false){
    mpz_class first = mpz_class(a);
    mpz_class second = mpz_class(b);
    std::vector<mpz_class > result = extended_gcd(first, second, printing);
    return mpz_to_strings(result);
}

// Calc inverse of number in module m
mpz_class inverse_element(const mpz_class &number, const mpz_class &module){
    // Find number mod module
    mpz_class number_mod = gmp_module(number,module);

    // Get extended gcd coefs
    std::vector<mpz_class> extend_gcd = extended_gcd(number_mod, module);
    if(extend_gcd[0] != 1) throw std::invalid_argument("Number and module must be co-prime");
    return gmp_module(extend_gcd[1],module);
}

// Func for call of inverse elem calculation from python
std::string inverse_element(const std::string &number, const std::string &module){
    mpz_class number_int = mpz_class(number);
    mpz_class module_int = mpz_class(module);
    if(module_int<0) throw std::invalid_argument("Module must be positive");
    return inverse_element(number_int,module_int).get_str();
}

// Solve linear congruence
std::vector<mpz_class> solve_linear_congruence(const mpz_class &a, const mpz_class &b, const mpz_class &module){
    if(module<0) throw std::invalid_argument("Module must be positive");

    //Find mod of all coefs
    mpz_class a_mod = gmp_module(a,module);
    mpz_class b_mod = gmp_module(b,module);

    // Cacl gcd between a and m
    mpz_class d;
    mpz_gcd(d.get_mpz_t(), a_mod.get_mpz_t(), module.get_mpz_t());
    if(gmp_module(b,d) != 0) return {};

    // Find new coefs
    mpz_class a_prime = 1, b_prime = 1, m_prime = 1;
    mpz_tdiv_q(a_prime.get_mpz_t(), a_mod.get_mpz_t(), d.get_mpz_t());
    mpz_tdiv_q(b_prime.get_mpz_t(), b_mod.get_mpz_t(), d.get_mpz_t());
    mpz_tdiv_q(m_prime.get_mpz_t(), module.get_mpz_t(), d.get_mpz_t());


    // Find inverse of a
    mpz_class inv_a = inverse_element(a_prime,m_prime);

    // Find x0 solution
    mpz_class x0 = gmp_multiply(inv_a,b_prime, m_prime);

    // Find all d solutions
    std::vector<mpz_class>solutions = {};
    for(mpz_class k=0;k<d;k++){
        mpz_class sol = gmp_add(x0, k * m_prime, module);
        solutions.push_back(sol);
    }
    return solutions;
}
// Function for calling of lin congr solving
std::vector<std::string> solve_linear_congruence(const std::string &a, const std::string &b, const std::string &module){
    mpz_class a_int = mpz_class(a);
    mpz_class b_int = mpz_class(b);
    mpz_class module_int = mpz_class(module);

    std::vector<mpz_class> solutions = solve_linear_congruence(a_int,b_int,module_int);
    return mpz_to_strings(solutions);
}



std::vector<std::string> solve_lefts(const std::vector<std::vector<string>> &coefs){
    if(coefs.empty()) throw std::invalid_argument("The system must contain at least 1 equation");
    std::vector<std::vector<mpz_class>> mpz_coefs;
    mpz_coefs.reserve(coefs.size());
    std::transform(
            coefs.begin(), coefs.end(),
            std::back_inserter(mpz_coefs),
            [](const std::vector<std::string> &coef) { return strings_to_mpzs(coef); }
    );
    return mpz_to_strings(solve_lefts(mpz_coefs));
}


std::vector<mpz_class> solve_lefts(const std::vector<std::vector<mpz_class>> &coefs){
    if(coefs.empty()) throw std::invalid_argument("The system must contain at least 1 equation");

    std::vector<std::vector<mpz_class>> coefs_mod = {};
    for(const auto & coef : coefs){
        coefs_mod.push_back({gmp_module(coef[0],coef[1]),coef[1]});
    }
    if(check_coprime_coefs((coefs))) return solve_lefts_coprime(coefs);
    return solve_lefts_not_coprime(coefs);
}

bool check_coprime_coefs(const std::vector<std::vector<mpz_class>> &coefs){
    for(int i=0;i<coefs.size()-1;i++){
        for(int j=i+1;j<coefs.size();j++){
            mpz_class gcd = 1;
            mpz_gcd(gcd.get_mpz_t(), coefs[i][1].get_mpz_t(), coefs[j][1].get_mpz_t());
            if(gcd != 1) return false;
        }
    }
    return true;
}

std::vector<mpz_class> solve_lefts_coprime(const std::vector<std::vector<mpz_class>> &coefs){

    // Calc M coef
    mpz_class M_coef = 1;
    for(const auto & coef : coefs){
        M_coef *= coef[1];
    }
    //Calc new a-coefs
    std::vector<mpz_class> new_a_coefs = {};
    for(const auto & coef : coefs){
        new_a_coefs.push_back(gmp_div(M_coef,coef[1]));
    }
    //Calc solutions for every lin congruence
    std::vector<mpz_class> solutions = {};
    for(int i=0;i<coefs.size();i++){
        solutions.push_back(solve_linear_congruence(new_a_coefs[i], coefs[i][0], coefs[i][1])[0]);
    }

    mpz_class result = 0;
    for(int i=0;i<solutions.size();i++){
        result = gmp_add(result, new_a_coefs[i] * solutions[i], M_coef);
    }
    return {result, M_coef};
}


bool check_no_coprime_coefs(const std::vector<std::vector<mpz_class>> &coefs){
    for(int i = 0; i<coefs.size()-1;i++){
        for(int j=i+1;j<coefs.size();j++){
            mpz_class gcd = 1;
            mpz_gcd(gcd.get_mpz_t(),coefs[i][1].get_mpz_t(),coefs[j][1].get_mpz_t());
            if(gmp_module(coefs[i][0],gcd)!= gmp_module(coefs[j][0],gcd)){
                return false;
            }
        }
    }
    return true;
}


std::vector<mpz_class> solve_lefts_not_coprime(const std::vector<std::vector<mpz_class>> &coefs){
    if(!(check_no_coprime_coefs(coefs))) return {};
    std::vector<mpz_class> solution = {coefs[0][0],coefs[0][1]};
    for(int i = 1; i<coefs.size(); i++){
        std::vector<mpz_class> lin_cong_solution = solve_linear_congruence(solution[1],coefs[i][0] - solution[0], coefs[i][1]);
        if(lin_cong_solution.size()>1){
            lin_cong_solution[1] = gmp_add(lin_cong_solution[1], - lin_cong_solution[0], coefs[i][1]);
        }
        else lin_cong_solution.push_back(coefs[i][1]);
        solution[0] = gmp_add(solution[0],solution[1]*lin_cong_solution[0],solution[1]*lin_cong_solution[1]);
        solution[1] = solution[1]*lin_cong_solution[1];
    }
    return solution;
}



std::vector<std::vector<mpz_class>> solve_diofant_equation(const mpz_class &a, const mpz_class &b, const mpz_class& d){
    mpz_class a_b_nod = 1;
    mpz_gcd(a_b_nod.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());

    mpz_class d_mod = 1;
    mpz_mmod(d_mod.get_mpz_t(), d.get_mpz_t(), a_b_nod.get_mpz_t());
    if(d_mod!=0) return {};

    mpz_class a_main, b_main, d_main;
    mpz_div(a_main.get_mpz_t(), a.get_mpz_t(), a_b_nod.get_mpz_t());
    mpz_div(b_main.get_mpz_t(), b.get_mpz_t(), a_b_nod.get_mpz_t());
    mpz_div(d_main.get_mpz_t(), d.get_mpz_t(), a_b_nod.get_mpz_t());

    std::vector<mpz_class> coefs = extended_gcd(a_main,b_main);
    std::vector<std::vector<mpz_class>> result = {{},{}};
    result[0].emplace_back(coefs[1]*d_main);
    result[0].emplace_back(result[0][0]!=0? mpz_sgn(result[0][0].get_mpz_t())*b:b);
    result[1].emplace_back(coefs[2]*d_main);
    result[1].emplace_back(result[1][0]!=0? mpz_sgn(result[1][0].get_mpz_t()) * a: -1 * a);
    return result;
}

std::vector<std::vector<std::string>> solve_diofant_equation(const std::string &a, const std::string &b, const std::string& d){
    mpz_class a_int = mpz_class(a);
    mpz_class b_int = mpz_class(b);
    mpz_class d_int = mpz_class(d);
    if(a_int==0 && b_int==0 && d_int==0) return {{"1","0"},{"1","0"}};
    else if(a_int==0 && b_int==0 && d_int!=0) return {{},{}};

    std::vector<std::vector<std::string>> result;
    std::vector<std::vector<mpz_class>> result_mpz = solve_diofant_equation(a_int,b_int,d_int);
    std::transform(
            result_mpz.begin(), result_mpz.end(),
            std::back_inserter(result),
            [](const std::vector<mpz_class> &coef) { return mpz_to_strings(coef); }
            );
    return result;
}
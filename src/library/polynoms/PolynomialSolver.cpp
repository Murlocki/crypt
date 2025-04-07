#include "library/polynoms/PolynomialSolver.h"
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include<iostream>
#include<vector>


PolynomialSolver::PolynomialSolver(const std::string &gf, const std::string &module) {
    this->gf = mpz_class(gf);

    if (module.empty() || module.size() == 1 && module[0] == 0) throw std::invalid_argument("Polynomial module ");
    this->module = this->parse_polynomial(module);
};

std::vector<mpz_class> PolynomialSolver::parse_polynomial(const std::string &polynomial_str) const {
    std::string polynomialStr_modified = polynomial_str + '+';

    // Разбиваем строку полинома на слагаемые
    std::vector<std::string> elems = {};
    std::string currentElem;
    for (char s: polynomialStr_modified) {
        if (s == '-') {
            elems.emplace_back(currentElem);
            currentElem = "-";
        } else if (s == '+') {
            elems.emplace_back(currentElem);
            currentElem = "";
        } else currentElem += s;
    }

    std::vector<mpz_class> coefs = {};
    std::vector<int> degrees = {};
    for (const std::string &elem: elems) {
        std::vector<std::string> comp = split_by_string(elem, "x");
        mpz_class coef;
        int degree;
        if (comp.size() == 2) {
            coef = !comp[0].empty() ? mpz_class(comp[0]) : mpz_class(1);
            degree = !comp[1].empty() ? std::stoi(comp[1].substr(1)) : 1;
        } else {
            coef = mpz_class(comp[0]);
            degree = 0;
        }
        coefs.emplace_back(coef);
        degrees.emplace_back(degree);
    }

    std::vector<mpz_class> result;
    result.resize(degrees[0] + 1, mpz_class(0));
    for (int i = 0; i < degrees.size(); i++) {
        result[degrees[i]] = gmp_module(coefs[i], this->gf);
    }
    std::reverse(result.begin(), result.end());
    for (const auto& x: result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return result;
}

std::vector<mpz_class> PolynomialSolver::sum_vector_pols(const std::vector<mpz_class> &polynomial_first_vector,
                                                         const std::vector<mpz_class> &polynomial_second_vector) const {
    std::vector<mpz_class> sum_vector;
    if (polynomial_first_vector.size() > polynomial_second_vector.size()) {
        std::copy(polynomial_first_vector.begin(), polynomial_first_vector.end(), std::back_inserter(sum_vector));
    } else std::copy(polynomial_second_vector.begin(), polynomial_second_vector.end(), std::back_inserter(sum_vector));


    unsigned int min_length = std::min(polynomial_first_vector.size(), polynomial_second_vector.size());
    for (int i = 1; i <= min_length; i++) {
        sum_vector[sum_vector.size() - i] = gmp_add(polynomial_first_vector[polynomial_first_vector.size() - i],
                                                    polynomial_second_vector[polynomial_second_vector.size() - i],
                                                    this->gf);
    }
    int i = 0;
    while (i < sum_vector.size() && sum_vector[i] == 0) i = i + 1;

    std::vector<mpz_class> result;
    std::copy(sum_vector.begin() + i, sum_vector.end(), std::back_inserter(result));

    for(auto x:result) std::cout<<x<<" ";
    std::cout<<std::endl;
    return result;
}

std::string PolynomialSolver::vector_to_str(const std::vector<mpz_class> &polynomial_vector) {
    std::string result;
    if (polynomial_vector.empty() || polynomial_vector[0] == 0 && polynomial_vector.size() == 1) return "0";
    for (int i = 0; i < polynomial_vector.size(); i++) {
        if (polynomial_vector[i] > 0) {
            result += (i == polynomial_vector.size() - 1 ||
                       polynomial_vector[i] > 1 && i < polynomial_vector.size() - 1) ? polynomial_vector[i].get_str()
                                                                                     : "";
            if (i < int(polynomial_vector.size()) - 1) result += 'x';
            if (i < int(polynomial_vector.size()) - 2) result += "^" + std::to_string(polynomial_vector.size() - i - 1);
            result += '+';
        }
    }
    return result.empty() ? "0" : result.substr(0, result.size() - 1);
}

std::string
PolynomialSolver::add_polynomial(const std::string &polynomial_first, const std::string &polynomial_second) {
    std::vector<mpz_class> first_vector = this->parse_polynomial(polynomial_first);
    std::vector<mpz_class> second_vector = this->parse_polynomial(polynomial_second);
    std::vector<mpz_class> polSum = this->sum_vector_pols(first_vector, second_vector);
    std::vector<mpz_class> result = this->del_vector_pols(polSum,this->module);
    return PolynomialSolver::vector_to_str(result);
}

std::vector<mpz_class > PolynomialSolver::calculate_deliter(const std::vector<mpz_class>& result,
                                                           const std::vector<mpz_class>& antiDelVector,
                                                           const int i) {
    // Создаем копию antiDelVector
    std::vector<mpz_class> deliter = antiDelVector;

    // Вычисляем количество нулей для добавления
    int zeros_to_add = int(result.size()) - i - int(antiDelVector.size());

    // Добавляем нули в конец вектора
    if (zeros_to_add > 0) {
        deliter.insert(deliter.end(), zeros_to_add, 0);
    }
    return deliter;
}

std::vector<mpz_class>
PolynomialSolver::del_vector_pols(const std::vector<mpz_class>& polynomial_vector, const std::vector<mpz_class>& polynomial_del_vector){
    if(polynomial_vector.size() < polynomial_del_vector.size()) return polynomial_vector;

    std::vector<mpz_class> result;
    std::copy(polynomial_vector.begin(), polynomial_vector.end(), std::back_inserter(result));

    while(true){
        std::vector<mpz_class> anti_del_vector;
        for(const mpz_class& elem:polynomial_del_vector){
            anti_del_vector.emplace_back(gmp_add(this->gf, - elem,this->gf));
        }
        int i = 0;
        while(i< result.size() && result[i] == 0) i = i + 1;
        std::vector<mpz_class> deliter = PolynomialSolver::calculate_deliter(result,anti_del_vector,i);
        result = this->sum_vector_pols(result, deliter);
        if(!PolynomialSolver::greater_vector(result, polynomial_del_vector)) break;
    }

    int i = 0;
    while(i<result.size() && result[i] == 0){
        i = i + 1;
    }
    if(i == result.size()) return {0};
    else{
        std::vector<mpz_class> result_slice;
        std::copy(result.begin() + i, result.end(), std::back_inserter(result_slice));
        return result_slice;
    }
};
bool PolynomialSolver::greater_vector(std::vector<mpz_class> vector_first, std::vector<mpz_class> vector_second){
    if(vector_first.size() == vector_second.size()){
        for(int i=0;i<vector_first.size();i++){
            if(vector_first[i]>vector_second[i]) return true;
            else if(vector_first[i]<vector_second[i]) return false;
        }
    }
    else if(vector_first.size() < vector_second.size()) return false;
    return true;
}

std::vector<mpz_class> PolynomialSolver::mult_vector_pols(const std::vector<mpz_class>& polynomial_vector1,const std::vector<mpz_class>& polynomial_vector2){
    std::vector<mpz_class>second,first;
    if(polynomial_vector1.size() < polynomial_vector2.size()){
        second = polynomial_vector1;
        first = polynomial_vector2;
    }
    else{
        first = polynomial_vector1;
        second = polynomial_vector2;
    }
    std::vector<mpz_class> result;
    for(const auto & i : first){
        //std::cout<<i<<" "<<result.size()<<std::endl;
        result.emplace_back(0);
        std::vector<mpz_class> secondMult;
        std::transform(second.begin(), second.end(), std::back_inserter(secondMult),
                       [first,&i](const mpz_class& x) { return x * i; });
        //std::cout<<123<<std::endl;
        result = this->sum_vector_pols(result,secondMult);
    }
    return result;
}

std::string PolynomialSolver::mult_polynomial(const std::string& polynomial_first,const std::string& polynomial_second) {
    std::vector<mpz_class> first_vector = this->parse_polynomial(polynomial_first);
    std::vector<mpz_class> second_vector = this->parse_polynomial(polynomial_second);

    std::vector<mpz_class> pol_mult_vector = this->mult_vector_pols(first_vector, second_vector);
    std::vector<mpz_class> result = this->del_vector_pols(pol_mult_vector, this->module);
    return this->vector_to_str(result);
}
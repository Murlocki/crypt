#include "library/polynoms/PolynomialSolver.h"
#include "library/extra_functions/convertions.h"
#include "library/basic_math/gmp_utils.h"
#include "library/basic_math/base_operations.h"
#include<iostream>
#include<vector>
#include <unordered_map>
#include <format>

using std::vector, std::string, std::cout, std::endl, std::set;

PolynomialSolver::PolynomialSolver(const string &gf, const string &module) {
    this->gf = mpz_class(gf);

    if (module.empty() || module.size() == 1 && module[0] == 0) throw std::invalid_argument("Polynomial module ");
    this->module = PolynomialSolver::parse_polynomial(module, this->gf);
};

vector<mpz_class> PolynomialSolver::parse_polynomial(const string &polynomial_str, const mpz_class &gf) {
    string polynomialStr_modified = polynomial_str + '+';

    // Разбиваем строку полинома на слагаемые
    vector<string> elems = {};
    string currentElem;
    for (char s: polynomialStr_modified) {
        if (s == '-') {
            elems.emplace_back(currentElem);
            currentElem = "-";
        } else if (s == '+') {
            elems.emplace_back(currentElem);
            currentElem = "";
        } else currentElem += s;
    }

    vector<mpz_class> coefs = {};
    vector<int> degrees = {};
    for (const string &elem: elems) {
        vector<string> comp = split_by_string(elem, "x");
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

    vector<mpz_class> result;
    result.resize(degrees[0] + 1, mpz_class(0));
    for (int i = 0; i < degrees.size(); i++) {
        result[degrees[i]] = gmp_module(coefs[i], gf);
    }
    std::reverse(result.begin(), result.end());
//    for (const auto& x: result) {
//        std::cout << x << " ";
//    }
//    std::cout << std::endl;
    return result;
}

vector<mpz_class> PolynomialSolver::sum_vector_pols(const vector<mpz_class> &polynomial_first_vector,
                                                    const vector<mpz_class> &polynomial_second_vector) const {
    vector<mpz_class> sum_vector;
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

    vector<mpz_class> result;
    std::copy(sum_vector.begin() + i, sum_vector.end(), std::back_inserter(result));

    return result;
}

string PolynomialSolver::vector_to_str(const vector<mpz_class> &polynomial_vector) {
    string result;
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

string
PolynomialSolver::add_polynomial(const string &polynomial_first, const string &polynomial_second) {
    vector<mpz_class> first_vector = PolynomialSolver::parse_polynomial(polynomial_first, this->gf);
    vector<mpz_class> second_vector = PolynomialSolver::parse_polynomial(polynomial_second, this->gf);
    vector<mpz_class> polSum = this->sum_vector_pols(first_vector, second_vector);
    vector<mpz_class> result = this->module.size() == 1 ? polSum : this->del_vector_pols(polSum, this->module);
    return PolynomialSolver::vector_to_str(result);
}

vector<mpz_class> PolynomialSolver::calculate_deliter(const vector<mpz_class> &result,
                                                      const vector<mpz_class> &antiDelVector,
                                                      const int i) {
    // Создаем копию antiDelVector
    vector<mpz_class> deliter = antiDelVector;

    // Вычисляем количество нулей для добавления
    int zeros_to_add = int(result.size()) - i - int(antiDelVector.size());

    // Добавляем нули в конец вектора
    if (zeros_to_add > 0) {
        deliter.insert(deliter.end(), zeros_to_add, 0);
    }
    return deliter;
}

vector<mpz_class>
PolynomialSolver::del_vector_pols(const vector<mpz_class> &polynomial_vector,
                                  const vector<mpz_class> &polynomial_del_vector) {
    if (polynomial_vector.size() < polynomial_del_vector.size()) return polynomial_vector;

    vector<mpz_class> result;
    std::copy(polynomial_vector.begin(), polynomial_vector.end(), std::back_inserter(result));

    while (true) {
        vector<mpz_class> anti_del_vector;
        for (const mpz_class &elem: polynomial_del_vector) {
            anti_del_vector.emplace_back(gmp_add(this->gf, -elem, this->gf));
        }
        int i = 0;
        while (i < result.size() && result[i] == 0) i = i + 1;
        vector<mpz_class> deliter = PolynomialSolver::calculate_deliter(result, anti_del_vector, i);
        result = this->sum_vector_pols(result, deliter);
        if (!PolynomialSolver::greater_vector(result, polynomial_del_vector)) break;
    }

    int i = 0;
    while (i < result.size() && result[i] == 0) {
        i = i + 1;
    }
    if (i == result.size()) return {0};
    else {
        vector<mpz_class> result_slice;
        std::copy(result.begin() + i, result.end(), std::back_inserter(result_slice));
        return result_slice;
    }
};

bool PolynomialSolver::greater_vector(vector<mpz_class> vector_first, vector<mpz_class> vector_second) {
    if (vector_first.size() == vector_second.size()) return true;
    else if (vector_first.size() < vector_second.size()) return false;
    return true;
}

vector<mpz_class> PolynomialSolver::mult_vector_pols(const vector<mpz_class> &polynomial_vector1,
                                                     const vector<mpz_class> &polynomial_vector2) {
    vector<mpz_class> second, first;
    if (polynomial_vector1.size() < polynomial_vector2.size()) {
        second = polynomial_vector1;
        first = polynomial_vector2;
    } else {
        first = polynomial_vector1;
        second = polynomial_vector2;
    }
    vector<mpz_class> result;
    for (const auto &i: first) {
        result.emplace_back(0);
        vector<mpz_class> secondMult;
        std::transform(second.begin(), second.end(), std::back_inserter(secondMult),
                       [first, &i](const mpz_class &x) { return x * i; });
        result = this->sum_vector_pols(result, secondMult);
    }
    return result;
}

string PolynomialSolver::mult_polynomial(const string &polynomial_first, const string &polynomial_second) {
    vector<mpz_class> first_vector = PolynomialSolver::parse_polynomial(polynomial_first, this->gf);
    vector<mpz_class> second_vector = PolynomialSolver::parse_polynomial(polynomial_second, this->gf);

    vector<mpz_class> pol_mult_vector = this->mult_vector_pols(first_vector, second_vector);
    vector<mpz_class> result =
            this->module.size() == 1 ? pol_mult_vector : this->del_vector_pols(pol_mult_vector, this->module);
    return PolynomialSolver::vector_to_str(result);
}

vector<mpz_class> PolynomialSolver::number_to_base(const mpz_class &num) {
    vector<mpz_class> digits;
    mpz_class n = num;
    mpz_class zero(0);
    if (n == zero) {
        digits.push_back(zero);
        return digits;
    }
    mpz_class remainder;
    while (n != zero) {
        mpz_tdiv_qr(n.get_mpz_t(), remainder.get_mpz_t(), n.get_mpz_t(), this->gf.get_mpz_t());
        digits.push_back(remainder);
    }
    // Цифры в обратном порядке, перевернём
    std::reverse(digits.begin(), digits.end());
    return digits;
}


std::unordered_map<int, vector<vector<mpz_class>>>
PolynomialSolver::create_not_priv_pol_list(int degree, mpz_class gf) {
    PolynomialSolver pol_solver = PolynomialSolver(gf.get_str());

    std::unordered_map<int, vector<vector<mpz_class>>> result;
    for (int i = 1; i < degree; i++) {
        mpz_class start = fast_degree(gf, i);
        for (mpz_class j = start; j < start * gf; j++) {
            vector<mpz_class> currentPol = pol_solver.number_to_base(j);
            bool prim = true;
            for (int k = 1; k < i / 2 + 1; k++) {
                for (const vector<mpz_class> &pol: result.at(k)) {
                    vector<mpz_class> del_result = pol_solver.del_vector_pols(currentPol, pol);
                    if (del_result[0] == 0) {
                        prim = false;
                        break;
                    }
                }
                if (!prim) break;
            }
            if (prim) {
                vector<vector<mpz_class>> pol_list = result[i];
                pol_list.emplace_back(currentPol);
                result[i] = pol_list;
            }
        }
    }
    return result;
}

bool PolynomialSolver::check_if_priv_pol(const vector<mpz_class> &pol_vector, const mpz_class &gf) {
    int vector_degree = pol_vector.size() - 1;
    PolynomialSolver pol_solver = PolynomialSolver(gf.get_str());


    std::unordered_map<int, vector<vector<mpz_class>>> not_priv_pol_vectors = PolynomialSolver::create_not_priv_pol_list(
            vector_degree / 2 + 1, gf);
    bool prim = true;
    for (int k = 1; k < vector_degree / 2 + 1; k++) {
        for (const vector<mpz_class> &pol: not_priv_pol_vectors[k]) {
            if (pol_solver.del_vector_pols(pol_vector, pol)[0] == 0) {
                prim = false;
                break;
            }
        }
        if (!prim) break;
    }
    return prim;
}

bool PolynomialSolver::prove_priv_polynomial(const string &pol, const string &gf) {
    vector<mpz_class> pol_vector = PolynomialSolver::parse_polynomial(pol, mpz_class(gf));
    return PolynomialSolver::check_if_priv_pol(pol_vector, mpz_class(gf));
}

bool PolynomialSolver::check_if_prime_pol(const string &pol, const string &gf) {

    mpz_class gf_mpz = mpz_class(gf);

    vector<mpz_class> pol_vector = PolynomialSolver::parse_polynomial(pol, gf_mpz);
    if (pol_vector.size() == 2) return true;
    if (!PolynomialSolver::check_if_priv_pol(pol_vector, gf_mpz)) return false;

    int pol_degree = pol_vector.size() - 1;
    vector<mpz_class> sq = {1, 0};
    vector<mpz_class> current_gf_elem = {1, 0};

    set<vector<mpz_class>> already_was;
    PolynomialSolver prim_solver = PolynomialSolver(gf);
    int i = 1;
    while (i <= fast_degree(gf_mpz, pol_degree) - 1) {
        current_gf_elem = prim_solver.mult_vector_pols(sq, current_gf_elem);
        current_gf_elem = prim_solver.del_vector_pols(current_gf_elem, pol_vector);
        i = i + 1;
        if (current_gf_elem.size() == 1 && current_gf_elem[0] == 1 || already_was.contains(current_gf_elem)) break;
        already_was.insert(current_gf_elem);
    }
    if (i == fast_degree(gf_mpz, pol_degree) - 1) return true;
    return false;
}


vector<vector<mpz_class>> PolynomialSolver::create_galue_elems() {
    vector<vector<mpz_class>> result = {{0}};
    vector<mpz_class> current_pol = {1};
    int count = this->module.size() - 1;
    cout << count << " " << fast_degree(2, count) - 1 << endl;
    for (int i = 1; i < fast_degree(2, count) - 1; i++) {
        current_pol = this->mult_vector_pols(current_pol, {1, 0});
        current_pol = this->del_vector_pols(current_pol, this->module);
        for (auto x: current_pol) cout << x << " ";
        cout << endl;
        result.emplace_back(current_pol);
    }
    result.push_back({1});
    return result;
}

std::unordered_map<string, string> PolynomialSolver::return_polynomoms_for_cycle_classes() {
    int degree = this->module.size() - 1;
    std::unordered_map<string, vector<mpz_class>> cycles = create_circle_classes(degree, this->gf);
    std::unordered_map<string, string> result;
    result["0"] = "M(g)=0";
    for (const auto &[start, cycle]: cycles) {
        if (start == "0") continue;
        string pol = std::format("M{:}(g)=", start);
        for (const auto& element: cycles[start]) {
            string current_pol = this->mult_polynomial(std::format("x^{:}", element.get_str()), "1");
            pol += std::format("(g+{:})", current_pol);
        }
        result[start] = pol;
    }
    return result;
}

bool PolynomialSolver::check_if_prim_elem(const string &elem) {
    vector<mpz_class> elem_vect = PolynomialSolver::parse_polynomial(elem, this->gf);
    return check_if_prim_elem(elem_vect);
}

bool PolynomialSolver::check_if_prim_elem(vector<mpz_class> elem) {
    vector<mpz_class> current_pol(elem.begin(), elem.end());
    int count = this->module.size() - 1;
    for (int i = 1; i < count - 1; i++) {
        if (current_pol.size() == 1 && current_pol[0] == 1) return false;
        current_pol = this->mult_vector_pols(current_pol, elem);
    }
    return true;
}
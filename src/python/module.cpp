//
// Created by kirill on 29.03.2025.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "library/basic_math/base_operations.h"
#include "library/basic_math/linear_congruence.h"
#include "library/basic_math/diofant_equasion.h"
#include "library/basic_math/quadratic_congruence.h"
#include "library/basic_math/numbers.h"
#include "library/codes/DES.h"
#include<library/basic_math/chinese_lefts.h>
#include<python/convertions.h>
#include<vector>
namespace py = pybind11;

py::int_ py_fast_degree(const py::int_ &number, const py::int_ &degree, const py::int_ &module) {
    return string_to_pyint(fast_degree(
            pyint_to_string(number),
            pyint_to_string(degree),
            pyint_to_string(module)
    ));
}

py::int_ py_euler_slow(const py::int_ &number) {
    return string_to_pyint(euler(
            pyint_to_string(number)
    ));
}

py::int_ py_euler_def(const py::int_ &number) {
    return string_to_pyint(euler_def(
            pyint_to_string(number)
    ));
}


std::vector<py::int_> py_extended_gcd(const py::int_ &first, const py::int_ &second) {
    return strings_to_pyints(extended_gcd(
            pyint_to_string(first),
            pyint_to_string(second)
    ));
}

py::int_ py_inverse_element(const py::int_ &number, const py::int_ &module) {
    return string_to_pyint(inverse_element(
            pyint_to_string(number),
            pyint_to_string(module)
    ));
}

std::vector<py::int_> py_linear_congruence(const py::int_ &a, const py::int_ &b, const py::int_ &module) {
    return strings_to_pyints(solve_linear_congruence(
            pyint_to_string(a),
            pyint_to_string(b),
            pyint_to_string(module)
    ));
}

std::vector<py::int_> py_chinese_lefts(const std::vector<std::vector<py::int_>> &coefs) {
    std::vector<std::vector<std::string>> string_coefs = {};
    string_coefs.reserve(coefs.size());
    std::transform(
            coefs.begin(), coefs.end(),
            std::back_inserter(string_coefs),
            [](const std::vector<py::int_>& coef_vect) {
                return pyints_to_strings(coef_vect); }
            );
    return strings_to_pyints(solve_lefts(string_coefs));
}
std::vector<std::vector<py::int_>> py_diofant_equasion(const py::int_ &a, const py::int_ &b, const py::int_ &d) {

    std::vector<std::vector<std::string>> string_result = solve_diofant_equasion(
                    pyint_to_string(a),
                    pyint_to_string(b),
                    pyint_to_string(d)
            );
    std::vector<std::vector<py::int_>> result;
    std::transform(
            string_result.begin(), string_result.end(),
            std::back_inserter(result),
            [](const std::vector<std::string>& coef_vect) {
                return strings_to_pyints(coef_vect); }
            );
    return result;
}

std::vector<py::int_> py_prime_roots(const py::int_ &module) {
    return strings_to_pyints(find_prime_roots(pyint_to_string(module)));
}
std::vector<py::int_> py_quadratic_congruence(const py::int_ &a, const py::int_ &module) {
    return strings_to_pyints(solve_quadratic_congruence(pyint_to_string(a),pyint_to_string(module)));
}

std::pair<std::vector<py::int_>,std::vector<py::int_>> py_quadratic_res_and_non_res(const py::int_ &module) {
    auto result = find_quadratic_residues_nonresidues(pyint_to_string(module));
    return std::pair(strings_to_pyints(result.first),strings_to_pyints(result.second));
}

py::int_ py_generate_mernsenne_prime(const py::int_& number){
    return string_to_pyint(generate_mersenne_prime(pyint_to_string(number)));
}
py::int_ py_generate_ferma_prime(const py::int_& number){
    return string_to_pyint(generate_fermat_prime(pyint_to_string(number)));
}

py::bool_ py_fermat_test(const py::int_& n, const py::int_& iterations){
    return fermat_test(pyint_to_string(n), pyint_to_string(iterations));
}
py::bool_ py_trial_division_test(const py::int_& n){
    return trial_division_test(pyint_to_string(n));
}
py::bool_ py_miller_rabin_test(const py::int_& n,const py::int_& k){
    return miller_rabin_test(pyint_to_string(n), pyint_to_string(k));
}

std::vector<py::int_> py_fermat_factorization(const py::int_&n){
    return strings_to_pyints(fermat_factorization(pyint_to_string(n)));
}
std::vector<py::int_> py_pollard_p_minus_1_factorization(const py::int_&n,const py::int_&B){
    return strings_to_pyints(pollard_p_minus_1(pyint_to_string(n),pyint_to_string(B)));
}
std::vector<py::int_> py_pollard_rho(const py::int_&n){
    return strings_to_pyints(pollard_rho(pyint_to_string(n)));
}

PYBIND11_MODULE(crypto_learn, m) {
    auto factorize_ops = m.def_submodule("Factorize", "Факторизация");
    factorize_ops.def("fermat_factorization", &py_fermat_factorization, py::arg("number"));
    factorize_ops.def("pollard_p_minus_1_factorization", &py_pollard_p_minus_1_factorization,
                      py::arg("number"),
                      py::arg("B")=py::int_(5));
    factorize_ops.def("pollard_rho_factorization", &py_pollard_rho,
                      py::arg("number"));

    auto prime_tests_ops = m.def_submodule("PrimeTests", "Проверки на простоту");
    prime_tests_ops.def("fermat_test", &py_fermat_test, py::arg("number"),py::arg("iter_count")=py::int_(5));
    prime_tests_ops.def("trial_division_test", &py_trial_division_test,
                      py::arg("number"));
    prime_tests_ops.def("miller_rabin_test", &py_miller_rabin_test,
                      py::arg("number"),py::arg("k")=py::int_(5));

    auto prime_generates = m.def_submodule("PrimeGenerates", "Генерация именных простых чисел");
    prime_generates.def("fermat_prime", &py_generate_ferma_prime, py::arg("number"));
    prime_generates.def("mersenne_prime", &py_generate_mernsenne_prime,py::arg("number"));

    auto encodes = m.def_submodule("Encodes", "Алгоритмы шифрования");
    py::class_<DES>(encodes, "DES")
            .def(py::init<string>(),py::arg("key")="1010101010111011000010010001100000100111001101101100110011011101")  // Конструктор
            .def("encrypt", &DES::encrypt, py::arg("string_to_encode"))
            .def("decrypt", &DES::decrypt, py::arg("string_to_decode"));

    auto base_operations = m.def_submodule("BaseOperations", "Базовые операции");
    base_operations.def("fast_degree", &py_fast_degree,
                        py::arg("number"),
                        py::arg("degree"),
                        py::arg("module") = py::int_(1));
    base_operations.def("euler_slow", &py_euler_slow,
                        py::arg("number"));
    base_operations.def("euler_def", &py_euler_def,
                        py::arg("number"));
    base_operations.def("extended_gcd", &py_extended_gcd,
                        py::arg("first"),
                        py::arg("second"));
    base_operations.def("inverse_element", &py_inverse_element,
                        py::arg("number"),
                        py::arg("module")=py::int_(1));
    base_operations.def("solve_linear_congruence", &py_linear_congruence,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("module"));
    base_operations.def("solve_chinese_lefts", &py_chinese_lefts,
                        py::arg("coefs"));
    base_operations.def("solve_diofant_equasion", &py_diofant_equasion,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("d")
                        );
    base_operations.def("find_prime_roots", &py_prime_roots,
                        py::arg("module")
    );
    base_operations.def("solve_quadratic_congruence", &py_quadratic_congruence,
                        py::arg("a"),py::arg("module")
    );
    base_operations.def("find_quadratic_residues_and_non_residues", &py_quadratic_res_and_non_res,
                        py::arg("module")
    );
}
//
// Created by kirill on 29.03.2025.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "library/basic_math/base_operations.h"
#include<python/convertions.h>

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


std::vector<py::int_> py_extended_gcd(const py::int_ &first, const py::int_ &second, const py::bool_ &printing) {
    return strings_to_pyints(extended_gcd(
            pyint_to_string(first),
            pyint_to_string(second),
            py::cast<bool>(printing)
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
std::vector<std::vector<py::int_>> py_diofant_equations(const py::int_ &a, const py::int_ &b, const py::int_ &d) {

    std::vector<std::vector<std::string>> string_result = solve_diofant_equation(
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

PYBIND11_MODULE(my_module, m) {
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
                        py::arg("second"),
                        py::arg("printing") = py::bool_(false));
    base_operations.def("inverse_element", &py_inverse_element,
                        py::arg("number"),
                        py::arg("module")=py::int_(1));
    base_operations.def("solve_linear_congruence", &py_linear_congruence,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("module"));
    base_operations.def("solve_chinese_lefts", &py_chinese_lefts,
                        py::arg("coefs"));
    base_operations.def("solve_diofant_equation", &py_diofant_equations,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("d")
                        );
    base_operations.def("find_prime_roots", &py_prime_roots,
                        py::arg("module")
    );
}
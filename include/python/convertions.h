//
// Created by kirill on 30.03.2025.
//

#ifndef CRYPTO_CONVERTIONS_H
#define CRYPTO_CONVERTIONS_H
#include<pybind11/pybind11.h>
namespace py = pybind11;
py::int_ string_to_pyint(const std::string &s);
std::vector<py::int_> strings_to_pyints(const std::vector<std::string>& strs);
std::vector<std::string> pyints_to_strings(const std::vector<py::int_>& py_ints);
std::string pyint_to_string(const py::int_ &py_int);
#endif //CRYPTO_CONVERTIONS_H

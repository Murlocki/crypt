//
// Created by kirill on 30.03.2025.
//

#ifndef CRYPTO_CONVERTIONS_H
#define CRYPTO_CONVERTIONS_H
#include<pybind11/pybind11.h>
namespace py = pybind11;
py::int_ string_to_pyint(const std::string &s);
std::vector<py::int_> strings_to_pyint(const std::vector<std::string>& strs);
#endif //CRYPTO_CONVERTIONS_H

//
// Created by kirill on 29.03.2025.
//
#include <pybind11/pybind11.h>
#include "basic_math/base_operations.h"

namespace py = pybind11;

std::string py_fast_degree(const py::int_& number, const py::int_& degree, const py::int_& module) {
    return fast_degree(
            py::cast<std::string>(py::str(number)),
            py::cast<std::string>(py::str(degree)),
            py::cast<std::string>(py::str(module))
    );
}


PYBIND11_MODULE(my_module, m) {
    m.def("fast_degree", &py_fast_degree,
          py::arg("number"),
          py::arg("degree"),
          py::arg("module") = py::int_(1));
}
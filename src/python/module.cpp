//
// Created by kirill on 29.03.2025.
//
#include <pybind11/pybind11.h>
#include "../../include/basic_math/gmp_utils.h"

namespace py = pybind11;

std::string py_gmp_multiply(const py::int_& a, const py::int_& b, const py::int_& mod) {
    return gmp_multiply(
            py::cast<std::string>(py::str(a)),
            py::cast<std::string>(py::str(b)),
            py::cast<std::string>(py::str(mod))
    );
}
std::string py_gmp_add(const py::int_& a, const py::int_& b, const py::int_& mod) {
    return gmp_add(
            py::cast<std::string>(py::str(a)),
            py::cast<std::string>(py::str(b)),
            py::cast<std::string>(py::str(mod))
    );
}
std::string py_gmp_mod(const py::int_& a, const py::int_& module) {
    return gmp_module(
            py::cast<std::string>(py::str(a)),
            py::cast<std::string>(py::str(module))
    );
}

PYBIND11_MODULE(my_module, m) {
    m.def("multiply", &py_gmp_multiply,
          py::arg("a"),
          py::arg("b"),
          py::arg("mod") = py::int_(1));
    m.def("add", &py_gmp_add,
          py::arg("a"),
          py::arg("b"),
          py::arg("mod") = py::int_(1));
    m.def("module", &py_gmp_mod,
          py::arg("a"),
          py::arg("mod"));
}
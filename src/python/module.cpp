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
            py::cast<std::string>(py::str(number)),
            py::cast<std::string>(py::str(degree)),
            py::cast<std::string>(py::str(module))
    ));
}

py::int_ py_euler_slow(const py::int_ &number) {
    return string_to_pyint(euler(
            py::cast<std::string>(py::str(number))
    ));
}

std::vector<py::int_> py_extended_gcd(const py::int_ &first, const py::int_ &second, const py::bool_ &printing) {
    return strings_to_pyint(extended_gcd(
            py::cast<std::string>(py::str(first)),
            py::cast<std::string>(py::str(second)),
            py::cast<bool>(printing)
    ));
}

PYBIND11_MODULE(my_module, m) {
    auto base_operations = m.def_submodule("BaseOperations", "Базовые операции");
    base_operations.def("fast_degree", &py_fast_degree,
                        py::arg("number"),
                        py::arg("degree"),
                        py::arg("module") = py::int_(1));
    base_operations.def("euler_slow", &py_euler_slow,
                        py::arg("number"));
    base_operations.def("extended_gcd", &py_extended_gcd,
                        py::arg("first"),
                        py::arg("second"),
                        py::arg("printing") = py::bool_(false));

}
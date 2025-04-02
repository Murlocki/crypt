#include<pybind11/pybind11.h>
#include<vector>
#include<string>
#include <algorithm>
#include <iterator>
#include "python/convertions.h"

namespace py = pybind11;

std::vector<py::int_> strings_to_pyints(const std::vector<std::string>& strs) {
    std::vector<py::int_> result;
    result.reserve(strs.size()); // Оптимизация: резервируем память заранее
    std::transform(
            strs.begin(), strs.end(),
            std::back_inserter(result),
            [](const std::string& s) {
                return string_to_pyint(s); }
    );
    return result;
}
std::vector<std::string> pyints_to_strings(const std::vector<py::int_>& py_ints) {
    std::vector<std::string> result;
    result.reserve(py_ints.size()); // Оптимизация: резервируем память заранее
    std::transform(
            py_ints.begin(), py_ints.end(),
            std::back_inserter(result),
            [](const py::int_& s) {
                return pyint_to_string(s); }
    );
    return result;
}
py::int_ string_to_pyint(const std::string &s){
    return py::int_(py::str(s));
}

std::string pyint_to_string(const py::int_ &py_int){
    return py::cast<std::string>(py::str(py_int));;
}

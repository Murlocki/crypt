#include<pybind11/pybind11.h>
#include<vector>
#include<string>
#include <algorithm>
#include <iterator>
namespace py = pybind11;

std::vector<py::int_> strings_to_pyint(const std::vector<std::string>& strs) {
    std::vector<py::int_> result;
    result.reserve(strs.size()); // Оптимизация: резервируем память заранее
    std::transform(
            strs.begin(), strs.end(),
            std::back_inserter(result),
            [](const std::string& s) {
                return py::int_(py::str(s)); }
    );
    return result;
}
py::int_ string_to_pyint(const std::string &s){
    return py::int_(py::str(s));
}
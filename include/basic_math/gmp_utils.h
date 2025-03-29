//
// Created by kirill on 29.03.2025.
//

#ifndef PYBIND_EXAMPLE_GMP_UTILS_H
#define PYBIND_EXAMPLE_GMP_UTILS_H
#pragma once
#include <string>


std::string gmp_multiply(const std::string& a, const std::string& b, const std::string& module);
std::string gmp_add(const std::string& a, const std::string& b, const std::string& module);
std::string gmp_module(const std::string& a, const std::string& module);
std::string gmp_binary(const std::string& number);
#endif //PYBIND_EXAMPLE_GMP_UTILS_H

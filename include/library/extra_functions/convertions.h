// convertions.h
#ifndef CRYPTO_CONVERTIONS_H
#define CRYPTO_CONVERTIONS_H

#include <vector>
#include <string>
#include <gmpxx.h>
#pragma once
std::vector<std::string> mpz_to_strings(const std::vector<mpz_class>& nums);
std::vector<mpz_class> strings_to_mpzs(const std::vector<std::string>& nums);
std::vector<std::string> split_by_string(const std::string& str, const std::string& delimiter);
#endif //CRYPTO_CONVERTIONS_H
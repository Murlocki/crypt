#include "library/extra_functions/convertions.h"
#include<vector>
#include<string>
#include<gmpxx.h>
#include <algorithm>
#include <iterator>
std::vector<std::string> mpz_to_strings(const std::vector<mpz_class>& nums) {
    std::vector<std::string> result;
    result.reserve(nums.size()); // Оптимизация: резервируем память заранее
    std::transform(
            nums.begin(), nums.end(),
            std::back_inserter(result),
            [](const mpz_class& num) { return num.get_str(); }
    );
    return result;
}
std::vector<mpz_class> strings_to_mpzs(const std::vector<std::string>& nums) {
    std::vector<mpz_class> result;
    result.reserve(nums.size()); // Оптимизация: резервируем память заранее
    std::transform(
            nums.begin(), nums.end(),
            std::back_inserter(result),
            [](const std::string &num) { return mpz_class(num); }
    );
    return result;
}

std::vector<std::string> split_by_string(const std::string& str,
                                         const std::string& delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    size_t delimiter_length = delimiter.length();

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter_length;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

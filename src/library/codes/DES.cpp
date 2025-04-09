//
// Created by kirill on 09.04.2025.
//

#include "library/codes/DES.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

void DES::create_round_keys() {
    std::string real_key = use_perm(key, del_perm);
    std::string left_key = real_key.substr(0, 28);
    std::string right_key = real_key.substr(28);

    for (int i = 0; i < 16; ++i) {
        int step = (i + 1 == 1 || i + 1 == 2 || i + 1 == 9 || i + 1 == 16) ? 1 : 2;
        left_key = shift(left_key, -step);
        right_key = shift(right_key, -step);
        std::string compress_key = use_perm(left_key + right_key, permutation);
        round_keys.push_back(compress_key);
    }
}

std::string DES::shift(const std::string &key, int steps) {
    std::string result = key;
    int len = key.length();
    steps = (steps % len + len) % len; // Handle negative steps

    for (int i = 0; i < len; ++i) {
        result[(i + steps) % len] = key[i];
    }
    return result;
}

std::string DES::use_perm(const std::string &init_string, const std::vector<int> &permutation1) {
    std::string result;
    for (int bit: permutation1) {
        result += init_string[bit - 1];
    }
    return result;
}

std::string DES::calcF(const std::string &input_string, const std::string &key) {
    std::string extend_input_string = use_perm(input_string, expand_permutation);
    std::string xor_string = xor_calc(key, extend_input_string);
    std::string result;

    for (int i = 0; i < 8; ++i) {
        std::string current_str = xor_string.substr(i * 6, 6);
        int row = std::stoi(std::string() + current_str[0] + current_str[5], nullptr, 2);
        int col = std::stoi(current_str.substr(1, 4), nullptr, 2);

        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << std::hex << s_box[i][row][col];
        std::string result_bit = ss.str();

        // Convert hex to binary string
        std::string binary;
        for (char c: result_bit) {
            switch (c) {
                case '0':
                    binary += "0000";
                    break;
                case '1':
                    binary += "0001";
                    break;
                case '2':
                    binary += "0010";
                    break;
                case '3':
                    binary += "0011";
                    break;
                case '4':
                    binary += "0100";
                    break;
                case '5':
                    binary += "0101";
                    break;
                case '6':
                    binary += "0110";
                    break;
                case '7':
                    binary += "0111";
                    break;
                case '8':
                    binary += "1000";
                    break;
                case '9':
                    binary += "1001";
                    break;
                case 'a':
                    binary += "1010";
                    break;
                case 'b':
                    binary += "1011";
                    break;
                case 'c':
                    binary += "1100";
                    break;
                case 'd':
                    binary += "1101";
                    break;
                case 'e':
                    binary += "1110";
                    break;
                case 'f':
                    binary += "1111";
                    break;
            }
        }
        result += binary;
    }
    return use_perm(result, forward_permutation);
}

std::string DES::xor_calc(const std::string &first, const std::string &second) {
    std::string result;
    for (size_t i = 0; i < first.length(); ++i) {
        result += (first[i] == second[i]) ? '0' : '1';
    }
    return result;
}

std::string DES::processOneRound(const std::string &input_string, int round_number, bool inverse) {
    std::string left_str = input_string.substr(0, 32);
    std::string right_str = input_string.substr(32);
    std::string function_str = calcF(right_str, round_keys[inverse ? (15 - round_number) : round_number]);
    std::string xor_str = xor_calc(left_str, function_str);

    if (round_number < 15) {
        return right_str + xor_str;
    }
    return xor_str + right_str;
}


DES::DES(const std::string &key) {
    if (key.length() != 64) {
        throw std::invalid_argument("DES init key length is not 64 bytes");
    }
    this->key = key;
    create_round_keys();
}

int DES::key_length() {
    return key.length();
}

std::string DES::encrypt(const std::string &plaintext) {
    if (plaintext.length() != 64) {
        throw std::invalid_argument("plaintext length must be 64 bytes");
    }
    std::string result = use_perm(plaintext, in_permutation);
    for (int i = 0; i < 16; ++i) {
        result = processOneRound(result, i);
    }
    return use_perm(result, out_permutation);
}

std::string DES::decrypt(const std::string &ciphertext) {
    if (ciphertext.length() != 64) {
        throw std::invalid_argument("ciphertext length must be 64 bytes");
    }
    std::string result = use_perm(ciphertext, in_permutation);
    for (int i = 0; i < 16; ++i) {
        result = processOneRound(result, i, true);
    }
    return use_perm(result, out_permutation);
}


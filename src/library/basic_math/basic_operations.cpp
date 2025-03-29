//
// Created by kirill on 29.03.2025.
//
#include<basic_math/gmp_utils.h>
#include<iostream>
using namespace std;

// Function for fast degree alg
std::string fast_degree(const std::string& number,const std::string& degree,const std::string& module){
    // Get degree in binary
    const std::string binary_degree = gmp_binary(degree);

    // Main cycle of alg
    std::string result = "1";
    for(int i=0;i<binary_degree.size();i++){
        if(binary_degree[i]=='1'){
            result = gmp_multiply(result,number,module);
        }
        if(i!=binary_degree.size()-1) result = gmp_multiply(result,result,module);
    }
    return result;
}


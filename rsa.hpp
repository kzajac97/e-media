#ifndef RSA_HPP
#define RSA_HPP

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cinttypes>
#include <cstdint>
#include <tuple>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

using namespace boost::multiprecision;

namespace Cryptography
{  
    using numeric_t = int; //alias for numeric type used in reading wave file
    using key_t = unsigned long long int;
    using uint1024_t =  boost::multiprecision::uint1024_t;
    using uint65536_t = number<cpp_int_backend<65536,65536,unsigned_magnitude, unchecked, void> >;

    struct RsaKeys
    {
        // two large prime numbers
        key_t p_value;
        key_t q_value;
        // encryption key
        key_t public_key;
        // exponent
        key_t exponent;
        // decryption key
        key_t private_key;

        RsaKeys(void) = default;
        RsaKeys(key_t p_init, key_t q_init);
        ~RsaKeys() {};

        void PrintKeys(void);
    };

    // Euclidean algorithm
    // <returns> Greatest common denominator of two ints
    key_t greatestCommonDenominator(key_t arg_1, key_t arg_2);
    // finds exponent for public key 
    // must co-prime and smaller than value 
    // of prime numbers product 
    key_t getCoPrime(key_t phi_value);
    // returns two large prime numbers
    std::tuple<key_t,key_t> getPrimeNumbers(void);
    //
    uint65536_t raiseLargeNumber(numeric_t number, key_t exponent);
    //
    numeric_t modularExponent(numeric_t number, key_t exponent, key_t modulus);
    std::vector<numeric_t> xorEncrypt(std::vector<numeric_t> data, int key);
    // encrypts numeric data in a vector using passed rsakeys
    std::vector<numeric_t> rsaEncrypt(std::vector<numeric_t> data, RsaKeys keys);
    // decrypts numeric data in a vector using passed rsakeys
    std::vector<numeric_t> rsaDecrypt(std::vector<numeric_t> data, RsaKeys keys);
    void addDecryptedKey(std::vector<numeric_t> & decrypted_data, const numeric_t number, const unsigned int index, const RsaKeys keys);
    std::vector<numeric_t> rsaDecryptAsync(std::vector<numeric_t> data, RsaKeys keys);
}

#endif
#include <iostream>
#include <vector>
#include <cmath>
#include <cinttypes>
#include <cstdint>
#include <tuple>

using numeric_t = int; //alias for numeric type used in reading wave file
using key_t = unsigned long long int;

namespace Cryptography
{
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
    // encrypts numeric data in a vector using passed rsakeys
    std::vector<numeric_t> encrypt(std::vector<numeric_t> data, RsaKeys keys);
    // decrypts numeric data in a vector using passed rsakeys
    std::vector<numeric_t> decrypt(std::vector<numeric_t> data, RsaKeys keys);
}
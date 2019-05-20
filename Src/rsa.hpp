#ifndef RSA_HPP
#define RSA_HPP

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cinttypes>
#include <cstdint>
#include <tuple>
#include <thread>
#include <functional>
#include <random>
#include <numeric>
#include <algorithm>
#include <cstdlib>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/integer.hpp>

using namespace boost::multiprecision;

namespace Cryptography
{  
    using numeric_t = uint16_t; //alias for numeric type used in reading wave file
    using uint128_t = boost::multiprecision::uint128_t;
    using uint1024_t =  boost::multiprecision::uint1024_t;
    using uint4096_t = number<cpp_int_backend<65536,65536,unsigned_magnitude, unchecked, void> >;
    using uint_max_t = number<cpp_int_backend<65536,65536,unsigned_magnitude, unchecked, void> >;
    
    // Euclidean algorithm
    // <returns> Greatest common denominator of two ints
    template <typename key_t>
    key_t greatestCommonDenominator(key_t arg_1, key_t arg_2)
    {
        key_t denominator; 

        while(true) 
        { 
            denominator = arg_1 % arg_2;
            // return if reminder is 0
            if (denominator == 0) 
                { return arg_2; }   
            // swap
            arg_1 = arg_2; 
            arg_2 = denominator; 
            std::cout<<"a";
        }
    } 
    // finds exponent for public key 
    // must co-prime and smaller than value 
    // of prime numbers product 
    template <typename key_t>
    key_t getCoPrime(key_t phi_value)
    {
        key_t exponent = 2; // start from 2 because 1 divides every number without reminder
        while(exponent < phi_value)
        {
            if (greatestCommonDenominator(exponent, phi_value) == 1) { return exponent; } 
            else { exponent++; }  
        }

        return exponent;
    }

    template <typename key_t>
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
        RsaKeys(key_t p_init, key_t q_init)
        {
            // save prime numbers in structure
            this->p_value = p_init;
            this->q_value = q_init;
            // save public key as product of two primes
            this->public_key = p_value * q_value;
            // get exponent as smallest co prime 
            // exponent is a part of public key 
            this->exponent = getCoPrime((p_value-1)*(q_value-1));
            // get private key from formula 
            this->private_key = (1 + (2 * (p_value-1) * (q_value-1)) )/(this->exponent);
        }

        ~RsaKeys() {};

        void PrintKeys(void)
        {
            std::cout << "Prime numbers: " << this->p_value << " " << this->q_value << "\n";
            std::cout << "Private Key: " << this->private_key << "\n";
            std::cout << "Public Key: " << this->public_key << "\n";
            std::cout << "Exponent: " << this->exponent << "\n";    
        }

        void generateKeys(key_t p_init, key_t q_init)
        {
            // save prime numbers in structure
            this->p_value = p_init;
            this->q_value = q_init;
            // save public key as product of two primes
            this->public_key = p_value * q_value;
            // get exponent as smallest co prime 
            // exponent is a part of public key 
            this->exponent = getCoPrime((p_value-1)*(q_value-1));
            // get private key from formula 
            this->private_key = (1 + (2 * (p_value-1) * (q_value-1)) )/(this->exponent);
        }
    };

    //
    template <typename key_t>
    key_t raiseLargeNumber(numeric_t number, key_t exponent)
    {
        key_t large_number = boost::numeric_cast<key_t>(number);
    
        for(unsigned int i=1; i < exponent; i++)
            { large_number *= number; }

        return large_number; 
    }

    template <typename key_t, typename numeric_t>
    key_t modularExponent(numeric_t number, key_t exponent, key_t modulus)
    {
        if(modulus == 1)
            { return 0; }
    
        else
        {
            key_t result = 1;
            // apply modulo in every iteration to avoid overflow
            for(unsigned int i=0; i < exponent; i++)
                { result = (result*number) % modulus; }
        
            return boost::numeric_cast<key_t> (result); // use casting for numeric stablility
        }
    }

    template <typename key_t>
    numeric_t decryptingExponent(key_t number, key_t exponent, key_t modulus)
    {
        if(modulus == 1)
            { return 0; }
    
        else
        {
            uint4096_t result = 1;
            // apply modulo in every iteration to avoid overflow
            for(unsigned int i=0; i < exponent; i++)
                { result = (result*number) % modulus; }
        
            return (numeric_t) result; // use casting for numeric stablility
        }
    }

    // encrypts numeric data in a vector using passed rsakeys
    template <typename key_t>
    std::vector<numeric_t> rsaEncrypt(std::vector<numeric_t> data, RsaKeys<key_t> keys)
    {
        std::vector<key_t> encrypted_data;
        std::vector<numeric_t> return_data;
        
        for(auto element : data)    
        { 
            key_t encrypted_number = modularExponent(element,keys.exponent,keys.public_key);
            encrypted_data.push_back(encrypted_number); 
        }

        for(auto element : encrypted_data)
        {
            for(unsigned int i=0; i < sizeof(key_t)/sizeof(numeric_t); ++i)
            { 
                numeric_t value = (element >> (8 * sizeof(numeric_t) * i));
                return_data.push_back(value); 
            }
        }

        return return_data;
    }

    // decrypts numeric data in a vector using passed rsakeys
    template <typename key_t>
    std::vector<numeric_t> rsaDecrypt(std::vector<numeric_t> data, RsaKeys<key_t> keys)
    {
        std::vector<numeric_t> decrypted_data; 
        auto size_ratio = sizeof(key_t)/sizeof(numeric_t);
        std::vector<key_t> encrypted_data(data.size() * sizeof(numeric_t)/sizeof(key_t),0);
        
        for(unsigned int i=0; i < encrypted_data.size(); ++i)
        {
            for(unsigned int j=0; j < size_ratio; ++j)
            {                
                encrypted_data[i] += j == 0 ? 
                    data[size_ratio*i + j] : (key_t) data[size_ratio*i + j] * raiseLargeNumber(2,8*size_ratio*j);
            }
        }
    
        for(auto element : encrypted_data)
        {
            numeric_t decrypted_number = decryptingExponent(element,keys.private_key,keys.public_key);
            decrypted_data.push_back(decrypted_number); 
        }
    
        return decrypted_data;
    }

    // Miller-Rabin test
    // <returns> True if number is probably prime
    template <typename key_t>
    bool millerRabinTest(key_t number, key_t rounds)
    {
        key_t random = 2 + rand() % (number - 4); 
        key_t x = modularExponent(random,rounds,number); 
    
        if (x == 1  || x == number - 1) 
            { return true; }
    
        while (rounds != number-1) 
        { 
            x = (x * x) % number; 
            rounds *= 2; 
    
            if (x == 1)
                { return false; }
            if (x == number-1)    
                { return true; }
        }

        return false;
    }

    template <typename key_t>
    key_t generatePrime(void)
    {
        key_t number = 0;

        number ^= 1UL; // set last bit to 1 so number is odd
        number ^= 1UL << 4*sizeof(number); // set first bit to one so number is large for its size

        while(!millerRabinTest(number))
            { number--; }

        return number;
    }

    // XOR encryption funcitons
    std::vector<numeric_t> xorEncrypt(std::vector<numeric_t> data, uint1024_t key);
    uint1024_t GenerateXorKey(void);
}

#endif
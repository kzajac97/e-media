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

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/integer.hpp>

using namespace boost::multiprecision;

namespace Cryptography
{  
    using numeric_t = int16_t; //alias for numeric type used in reading wave file
    using uint1024_t =  boost::multiprecision::uint1024_t;
    
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

    template <typename key_t>
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
        
            return boost::numeric_cast<key_t>(result); // use casting for numeric stablility
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
            for(unsigned int i=0; i < sizeof(element)/2; ++i)
                { return_data.push_back( boost::numeric_cast<numeric_t>(element >> (16*i) )); }
        }

        return return_data;
    }

    // decrypts numeric data in a vector using passed rsakeys
    template <typename key_t>
    std::vector<numeric_t> rsaDecrypt(std::vector<numeric_t> data, RsaKeys<key_t> keys)
    {
        std::vector<numeric_t> decrypted_data;
        std::vector<key_t> encrypted_data;
    
        for(unsigned int i=0; i < data.size(); i += sizeof(encrypted_data[0])/sizeof(data[0]) )
            { encrypted_data.push_back( boost::numeric_cast<key_t> (data[i] >> (16*i)) ); }

        for(auto element : encrypted_data)
        {
            numeric_t decrypted_number = boost::numeric_cast<numeric_t>(modularExponent(element,keys.private_key,keys.public_key));
            decrypted_data.push_back(decrypted_number); 
        }

        return decrypted_data;
    }

    template <typename key_t>
    void addDecryptedKey(std::vector<numeric_t> & decrypted_data, const numeric_t number, const unsigned int index, const RsaKeys<key_t> keys)
    {
        numeric_t encrypted_number = modularExponent(number,keys.private_key,keys.public_key);
        decrypted_data[index] = encrypted_number; 
    }

    template <typename key_t>
    std::vector<numeric_t> rsaDecryptAsync(std::vector<numeric_t> data, RsaKeys<key_t> keys)
    {
        std::vector<numeric_t> decrypted_data;
    
        decrypted_data.resize(data.size());
        std::vector<std::thread> threads;

        for(unsigned int i=0; i < data.size(); ++i)
        {
            std::thread t(addDecryptedKey,std::ref(decrypted_data),data[i],i,keys);
            threads.push_back(std::move(t));
        }

        for(unsigned int j=0; j < threads.size(); ++j)
            { threads[j].join(); }

        threads.clear();

        return decrypted_data;
    }
    
    // XOR encryption funcitons
    std::vector<numeric_t> xorEncrypt(std::vector<numeric_t> data, uint1024_t key);
    uint1024_t GenerateXorKey(void);
}

#endif
#include "rsa.hpp"

using namespace Cryptography;

RsaKeys::RsaKeys(key_t p_init, key_t q_init)
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

void RsaKeys::PrintKeys(void) 
{
    std::cout << "Prime numbers: " << this->p_value << " " << this->q_value << "\n";
    std::cout << "Private Key: " << this->private_key << "\n";
    std::cout << "Public Key: " << this->public_key << "\n";
    std::cout << "Exponent: " << this->exponent << "\n";
}

key_t Cryptography::getCoPrime(key_t phi_value)
{
    key_t exponent = 2; // start from 2 because 1 divides every number without reminder
    while(exponent < phi_value)
    {
        if (greatestCommonDenominator(exponent, phi_value) == 1) { return exponent; } 
        else { exponent++; }  
    }

    return exponent;
}

key_t Cryptography::greatestCommonDenominator(key_t arg_1, key_t arg_2)
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

uint65536_t Cryptography::raiseLargeNumber(numeric_t number, key_t exponent)
{
    uint65536_t large_number = boost::numeric_cast<uint65536_t>(number);
    
    for(unsigned int i=1; i < exponent; i++)
        { large_number *= number; }

    return large_number; 
}
    
std::vector<numeric_t> Cryptography::xorEncrypt(std::vector<numeric_t> data, int key)
{
    for(auto & element : data)
        { element ^= key; }

    return data;
}

std::vector<numeric_t> Cryptography::rsaEncrypt(std::vector<numeric_t> data, RsaKeys keys)
{
    std::vector<numeric_t> encrypted_data;

    for(auto element : data)    
    { 
        uint1024_t encrypted_number = boost::numeric_cast<uint1024_t>( std::pow(element,keys.exponent) );

        encrypted_number %= keys.public_key;   
        encrypted_data.push_back( (numeric_t) encrypted_number ); 
    }

    return encrypted_data;
}

std::vector<numeric_t> Cryptography::rsaDecrypt(std::vector<numeric_t> data, RsaKeys keys)
{
    std::vector<numeric_t> decrypted_data;
    
    for(auto element : data)
    { 
        uint65536_t encrypted_number = boost::numeric_cast<uint65536_t>( raiseLargeNumber(element,keys.private_key) );
        
        encrypted_number %= keys.public_key;
        decrypted_data.push_back( (numeric_t) encrypted_number ); 
    }

    return decrypted_data;
}

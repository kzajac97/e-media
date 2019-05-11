#include "rsa.hpp"

#include <thread>
#include <functional>
#include <random>
#include <numeric>
#include <algorithm>

#include <cstdlib>

using namespace Cryptography;

std::vector<numeric_t> Cryptography::xorEncrypt(std::vector<numeric_t> data, uint1024_t key)
{
    std::vector<uint8_t> keys(128,0); // split 1024 bit key into series of 8 bit numbers 

    for(unsigned int i=0; i < keys.size(); ++i)
        { keys[i] = boost::numeric_cast<uint8_t>(key >> (8*i)); } // use bit shift 

    // apply each 8 bit key to each value 
    // when data is longer than keys, repeat from beginnig
    for(unsigned int j=0; j < data.size(); ++j)
        { data[j] ^= keys[j % keys.size()]; } 

    return data;
}

uint1024_t Cryptography::GenerateXorKey(void)
{
    uint1024_t result;
    std::vector<uint8_t> random_numbers(128,0);
   
    // std::random_device rnd;
    // std::mt19937 mersenne_engine(rnd());
    // std::uniform_int_distribution<> dist(0,255);
    
    // // create random vectors in lambda function capturing dist and engine variables
    // std::generate(random_numbers.begin(),random_numbers.end(),[&dist,&mersenne_engine]() mutable 
    //     { return boost::numeric_cast<uint8_t>( dist(mersenne_engine)); });

    std::generate(random_numbers.begin(),random_numbers.end(),[]() mutable
        { return rand() % 255; });

    for(unsigned int j=0; j < random_numbers.size(); ++j) 
        { result = (random_numbers[j] << 8*j); } 

    return result;
}
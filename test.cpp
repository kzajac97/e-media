#include <iostream>
#include <cinttypes>
#include <vector>
#include <cmath>

using numeric_t = uint8_t;
using key_t = uint16_t;

std::vector<numeric_t> _16to8(std::vector<key_t> data)
{
    std::vector<key_t> encrypted_data;
    std::vector<numeric_t> return_data;
    
    for(auto element : data)
    {
        for(unsigned int i=0; i < sizeof(key_t)/sizeof(numeric_t); ++i)
            { return_data.push_back( element >>= ( 8 * sizeof(numeric_t) * i)); }
    }

    return return_data;
}

std::vector<uint16_t> _8to16(std::vector<uint8_t> data)
{
    std::vector<uint16_t> result(data.size() * sizeof(uint8_t)/sizeof(uint16_t),0);

    for(unsigned int i=0; i < result.size(); ++i)
    {
        for(unsigned int j=0; j < sizeof(uint16_t)/sizeof(uint8_t); ++j)
        {
            if(j == 0) { result[i] += data[sizeof(uint16_t)/sizeof(uint8_t)*i + j]; }
            else { result[i] += (uint16_t) data[sizeof(uint16_t)/sizeof(uint8_t)*i + j] * std::pow(2, 4 * sizeof(uint16_t)/sizeof(uint8_t)*j ); }
        }
    }

    return result;
}

int main(void)
{
    std::vector<key_t> vec16 = {46536,23834,26272,65535,86};
    
    auto vec = _16to8(vec16);
    auto vec2 = _8to16(vec);

    std::cout << "TO 8\n";
    for(auto x : vec)
    { std::cout << (int)x << " "; }
    std::cout << "\n";

    std::cout << "TO 16\n";
    for(auto x : vec2)
    { std::cout << x << " "; }
    std::cout << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "rsa.hpp"
#include "reader.hpp"
#include "menu.hpp"

using namespace boost::multiprecision;

int main(void)
{
    //Menu();

    // std::vector<int16_t> data = {1,2,3,4,5,4,5,5,4,3,4,4,2,34,4,14,1,3,2,3,3,2,141,5,15};
    // uint1024_t key = 2363637318288490413;
    // std::cout << "xor key: " << key << "\n";
    // auto encrypted = Cryptography::xorEncrypt(data,key);
    // auto decrypted = Cryptography::xorEncrypt(encrypted,key);

    // std::cout << "DATA: \n";
    // for(auto x : data)
    //     { std::cout << x << " "; }
    // std::cout << "\n";

    // std::cout << "ENCRPYTED: \n";
    // for(auto x : encrypted)
    //     { std::cout << x << " "; }
    // std::cout << "\n";

    // std::cout << "DECRYPTED: \n";
    // for(auto x : decrypted)
    //     { std::cout << x << " "; }
    // std::cout << "\n";
    // return 0;

    Cryptography::RsaKeys keys(104729,108203);
    keys.PrintKeys();
}
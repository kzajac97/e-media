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

    // Cryptography::RsaKeys<uint64_t> keys(383,397);
    // keys.PrintKeys();
    // //std::vector<uint16_t> data = {53, 29, 38, 27, 38, 25, 36, 28, 84, 14, 56, 89, 36, 26, 32, 33, 35, 75, 98, 88};
    // std::vector<uint16_t> data = {32639, 32639, 32639, 32639, 32639};
    // // uint1024_t key = 2363637318288490413;
    // // std::cout << "xor key: " << key << "\n";
    // auto encrypted = Cryptography::rsaEncrypt(data,keys);
    // auto decrypted = Cryptography::rsaDecrypt(encrypted,keys);

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

    int test = 0;

    test ^= 1UL;
    test ^= 1UL << 4*sizeof(test);
    std::cout << test << "\n";

    return 0;
}
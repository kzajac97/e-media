#include <iostream>
#include <vector>

#include "rsa.hpp"

int main(void)
{
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};

    auto keys = Cryptography::RsaKeys(3,7);
    auto encrypted = Cryptography::encrypt(vec,keys);
    auto decrypted = Cryptography::decrypt(encrypted,keys);

    for(auto x : encrypted) { std::cout << x << " "; }
    std::cout << "\n";
    for(auto x : decrypted) { std::cout << x << " "; }
    std::cout << "\n";
}
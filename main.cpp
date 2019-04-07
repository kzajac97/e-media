#include <iostream>
#include <vector>

#include "rsa.hpp"

int main(void)
{
    std::vector<int> vec = {101,223,32,44,534,66,77,88,95,103};

    auto keys = Cryptography::RsaKeys(53,59);
    keys.PrintKeys();
    auto encrypted = Cryptography::rsaEncrypt(vec,keys);
    auto decrypted = Cryptography::rsaDecrypt(encrypted,keys);

    std::cout << "Message:\n";
    for(auto x : vec) { std::cout << x << " "; }
    std::cout << "\n";
    std::cout << "Encrypted:\n";
    for(auto x : encrypted) { std::cout << x << " "; }
    std::cout << "\n";
    std::cout << "Decrypted:\n";
    for(auto x : decrypted) { std::cout << x << " "; }
    std::cout << "\n";
}
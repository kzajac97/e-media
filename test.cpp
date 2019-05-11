#include <iostream>
#include <cinttypes>

template <typename T>
void getsize(T arg)
{ std::cout << sizeof(arg) << "\n"; }

int main(void)
{
    uint16_t a = 10;
    uint8_t b = 12;
    
    std::cout << "Int16\n";
    getsize(a);
    std::cout << "Int8\n";
    getsize(b);
}
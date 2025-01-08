#include "BigInteger.hpp"
#include "FastBigInteger.hpp"
#include "BigFloat.hpp"
#include "BigMath.hpp"
#include <iostream>
#include <chrono>


int main()
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    BigInt a(2025);
    BigInt b = a.factorial();

    for (std::vector<char>::const_reverse_iterator it = b.rbegin(), end = b.rend(); it != end; ++it)
    {
        if (static_cast<int>(*it) > 0)
        {
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::cout << b << std::endl;
            std::cout << static_cast<int>(*it) << std::endl;
            std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            break;
        }
    }

    return 0;
}
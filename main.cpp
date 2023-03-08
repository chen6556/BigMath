#include "BigInteger.hpp"
#include "FastBigInteger.hpp"
#include "BigFloat.hpp"
#include "BigMath.hpp"
#include <iostream>



int main(int, char**) 
{

    BigInt a("1234");
    std::cout << a.pow(a) << std::endl;
}
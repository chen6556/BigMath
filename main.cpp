#include "BigInteger.hpp"
#include "BigFloat.hpp"
#include "BigMath.hpp"
#include <iostream>


int main()
{
    { // BigInteger Test 0
        BigInteger a("31415926"), b("314159"), c("-31415926"), d("-314159");
        std::cout << "BigInteger Test 0" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigInteger Test 1
        BigInteger a("31415926"), b("314159"), c("-31415926"), d("-314159");
        std::cout << "BigInteger Test 1" << std::endl;
        std::cout << a + a << ',' << a - a << ',' << a * a << ',' << a / a << std::endl;
        std::cout << b + b << ',' << b - b << ',' << b * b << ',' << b / b << std::endl;
        std::cout << c + c << ',' << c - c << ',' << c * c << ',' << c / c << std::endl;
        std::cout << d + d << ',' << d - d << ',' << d * d << ',' << d / d << std::endl;
    }

    { // BigFloat Test 0
        BigFloat a("3.1415926"), b("3.14159"), c("-3.1415926"), d("-3.14159");
        std::cout << "BigFloat Test 0" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigFloat Test 1
        BigFloat a("0.31415926"), b("3.14159"), c("-0.1415926"), d("-3.14159");
        std::cout << "BigFloat Test 1" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigFloat Test 2
        BigFloat a("3.1415926"), b("0.314159"), c("-3.1415926"), d("-0.314159");
        std::cout << "BigFloat Test 2" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigFloat Test 3
        BigFloat a("3.1415926"), b("314159"), c("-3.1415926"), d("-314159");
        std::cout << "BigFloat Test 3" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigFloat Test 4
        BigFloat a("31415926"), b("3.14159"), c("-31415926"), d("-3.14159");
        std::cout << "BigFloat Test 4" << std::endl;
        std::cout << a + b << ',' << a + c << ',' << a + d << ',' << b + c << ',' << b + d << ',' << c + d << std::endl;
        std::cout << b + a << ',' << c + a << ',' << d + a << ',' << c + b << ',' << d + b << ',' << d + c << std::endl;
        std::cout << a - b << ',' << a - c << ',' << a - d << ',' << b - c << ',' << b - d << ',' << c - d << std::endl;
        std::cout << b - a << ',' << c - a << ',' << d - a << ',' << c - b << ',' << d - b << ',' << d - c << std::endl;
        std::cout << a * b << ',' << a * c << ',' << a * d << ',' << b * c << ',' << b * d << ',' << c * d << std::endl;
        std::cout << b * a << ',' << c * a << ',' << d * a << ',' << c * b << ',' << d * b << ',' << d * c << std::endl;
        std::cout << a / b << ',' << a / c << ',' << a / d << ',' << b / c << ',' << b / d << ',' << c / d << std::endl;
        std::cout << b / a << ',' << c / a << ',' << d / a << ',' << c / b << ',' << d / b << ',' << d / c << std::endl;
    }

    { // BigFloat Test 5
        BigFloat a("31415926"), b("0.31415926"), c("-31415926"), d("-0.31415926");
        std::cout << "BigFloat Test 5" << std::endl;
        std::cout << a + a << ',' << a - a << ',' << a * a << ',' << a / a << std::endl;
        std::cout << b + b << ',' << b - b << ',' << b * b << ',' << b / b << std::endl;
        std::cout << c + c << ',' << c - c << ',' << c * c << ',' << c / c << std::endl;
        std::cout << d + d << ',' << d - d << ',' << d * d << ',' << d / d << std::endl;
    }

    

    return 0;
}
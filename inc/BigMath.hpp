#pragma once
#include "BigFloat.hpp"
#include "BigInteger.hpp"
#include "FastBigInteger.hpp"
#include "Util.hpp"
#include <thread>

namespace Constant
{
    static const BigFloat Pi("3.14159265358979323846");
    static const BigFloat Pi_50("3.14159265358979323846264338327950288419716939937510");
    static const BigFloat Pi_100("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"); 
    static const BigFloat Duo_Pi_100("6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341358");
    static const BigFloat E("2.71828182845904523536");
    static const BigFloat E_50("2.71828182845904523536028747135266249775724709369995");
    static const BigFloat E_100("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
};

BigFloat sin(const BigFloat& big_float, const size_t& n = 10);
BigFloat cos(const BigFloat& big_float, const size_t& n = 10);
BigFloat tan(const BigFloat& big_float, const size_t& n = 10);

BigInt factorial(const BigInt& big_int);
BigInt factorial(const size_t& n);
BigIntF factorial(const BigIntF& big_int);

BigFloat sqrt(const BigInt& big_int, const size_t& n = 20);
BigFloat sqrt(const BigFloat& big_float, const size_t& n = 20);

BigFloat pi(const size_t& n = 20);
BigFloat e(const size_t& n = 20);
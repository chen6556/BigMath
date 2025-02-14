#pragma once
#include "BigInteger.hpp"
#include "BigFloat.hpp"


namespace Constant
{
    static unsigned char CPU_CORES = 8;
};

class Util
{
public:
    static void append(BigInt &big_int, const char ch)
    {
        big_int._nums.push_back(ch);
    }

    static void append_to_int_part(BigFloat &big_float, const char ch)
    {
        big_float._int_part._nums.push_back(ch);
    }

    static void append_to_float_part(BigFloat &big_float, const char ch)
    {
        big_float._float_part._nums.push_back(ch);
    }

    static void copy_to_int_part(BigFloat &big_float, const BigInt &big_int)
    {
        big_float._int_part = big_int;
    }

    static void copy_to_float_part(BigFloat &big_float, const BigInt &big_int)
    {
        big_float._float_part = big_int;
    }
};
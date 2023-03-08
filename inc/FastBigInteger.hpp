#pragma once
#include <iostream>
#include <list>
#include <thread>
#include "BigInteger.hpp"
#include "Util.hpp"

class FastBigInteger
{
    private:
        std::list<int> _nums;
        bool _negative = false;
        FastBigInteger(const std::list<int>& big_int);
        static void to_BigInt_subfunction(size_t index, std::list<int>::const_reverse_iterator it, const std::list<int>::const_reverse_iterator end, std::list<BigInt>& output);
    public:
        
        FastBigInteger();
        FastBigInteger(const char big_int);
        FastBigInteger(const char* big_int);
        FastBigInteger(const FastBigInteger& big_int);
        FastBigInteger(const BigInt& big_int);
        FastBigInteger(size_t n);
        ~FastBigInteger();

        bool operator>(const FastBigInteger& big_int) const;
        bool operator<(const FastBigInteger& big_int) const;
        bool operator==(const FastBigInteger& big_int) const;
        bool operator!=(const FastBigInteger& big_int) const;
        bool operator>=(const FastBigInteger& big_int) const;
        bool operator<=(const FastBigInteger& big_int) const;

        bool negative() const;
        size_t length() const;
        FastBigInteger abs() const;
        FastBigInteger opposite() const; 
        FastBigInteger opposite(const bool& inplace);
        FastBigInteger pow(const FastBigInteger& big_int) const;
        FastBigInteger pow(const size_t& n) const;
        FastBigInteger factorial() const;
        friend FastBigInteger operator-(const FastBigInteger& big_int);

        FastBigInteger operator+(const FastBigInteger& big_int) const;
        FastBigInteger operator-(const FastBigInteger& big_int) const;
        FastBigInteger operator*(const FastBigInteger& big_int) const;
        FastBigInteger operator/(const FastBigInteger& big_int) const;
        FastBigInteger operator%(const FastBigInteger& big_int) const;
        void operator=(const FastBigInteger& big_int);

        void operator+=(const FastBigInteger& big_int);
        void operator-=(const FastBigInteger& big_int);
        void operator*=(const FastBigInteger& big_int);
        void operator/=(const FastBigInteger& big_int);
        void operator%=(const FastBigInteger& big_int);
        
        FastBigInteger operator++();
        FastBigInteger operator++(const int);
        FastBigInteger operator--();
        FastBigInteger operator--(const int);

        std::string to_str() const;
        BigInt to_BigInt() const;
        friend std::ostream& operator<<(std::ostream& o, const FastBigInteger& big_int);
};

typedef FastBigInteger BigIntF;
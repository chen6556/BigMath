#pragma once
#include <iostream>
#include <string>
#include <vector>


class BigInteger
{
    private:
        std::vector<char> _nums;
        bool _negative = false;
        BigInteger(const std::vector<char>& big_int);
        size_t to_uint() const;
        int to_int() const;
        
    public:
        BigInteger sqrt() const;
        BigInteger();
        BigInteger(const char* big_int);
        BigInteger(const BigInteger& big_int);
        BigInteger(long long n);
        ~BigInteger();

        bool operator>(const BigInteger& big_int) const;
        bool operator<(const BigInteger& big_int) const;
        bool operator==(const BigInteger& big_int) const;
        bool operator!=(const BigInteger& big_int) const;
        bool operator>=(const BigInteger& big_int) const;
        bool operator<=(const BigInteger& big_int) const;

        bool negative() const;
        size_t length() const;
        BigInteger abs() const;
        BigInteger opposite() const; 
        BigInteger opposite(const bool inplace);
        BigInteger pow(const BigInteger& big_int) const;
        BigInteger pow(const size_t n) const;
        BigInteger factorial() const;
        friend BigInteger operator-(const BigInteger& big_int);

        BigInteger operator+(const BigInteger& big_int) const;
        BigInteger operator-(const BigInteger& big_int) const;
        BigInteger operator*(const BigInteger& big_int) const;
        BigInteger operator/(const BigInteger& big_int) const;
        BigInteger operator%(const BigInteger& big_int) const;
        void operator=(const BigInteger& big_int);

        void operator+=(const BigInteger& big_int);
        void operator-=(const BigInteger& big_int);
        void operator*=(const BigInteger& big_int);
        void operator/=(const BigInteger& big_int);
        void operator%=(const BigInteger& big_int);
        
        BigInteger& operator++();
        BigInteger operator++(const int);
        BigInteger& operator--();
        BigInteger operator--(const int);

        std::string to_str() const;
        friend std::ostream& operator<<(std::ostream& o, const BigInteger& big_int);
        friend class FastBigInteger;
        friend class util;

        std::vector<char>::const_iterator begin() const;
        std::vector<char>::const_iterator end() const;
        std::vector<char>::const_reverse_iterator rbegin() const;
        std::vector<char>::const_reverse_iterator rend() const;
        char operator[](const size_t i) const;
        char& operator[](const size_t i);
};

typedef BigInteger BigInt;
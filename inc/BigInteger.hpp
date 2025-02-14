#pragma once
#include <iostream>
#include <string>
#include <vector>


class BigInteger
{
private:
    std::vector<char> _nums;
    bool _negative = false;
    BigInteger(const std::vector<char> &big_int);

public:
    static const BigInteger ZERO, ONE, TWO;

public:
    BigInteger();
    BigInteger(const char* big_int);
    BigInteger(const BigInteger &big_int);
    BigInteger(long long n);
    BigInteger(size_t n);
    ~BigInteger();

    bool operator>(const BigInteger &big_int) const;
    bool operator<(const BigInteger &big_int) const;
    bool operator==(const BigInteger &big_int) const;
    bool operator!=(const BigInteger &big_int) const;
    bool operator>=(const BigInteger &big_int) const;
    bool operator<=(const BigInteger &big_int) const;

    bool negative() const;
    size_t length() const;
    BigInteger abs() const;
    BigInteger opposite() const;
    BigInteger &opposite(const bool inplace);
    BigInteger pow(const BigInteger &big_int) const;
    BigInteger pow(const size_t n) const;
    friend BigInteger operator-(const BigInteger &big_int);

    BigInteger operator+(const BigInteger &big_int) const;
    BigInteger operator-(const BigInteger &big_int) const;
    BigInteger operator*(const BigInteger &big_int) const;
    BigInteger operator/(const BigInteger &big_int) const;
    BigInteger operator%(const BigInteger &big_int) const;
    BigInteger &operator=(const BigInteger &big_int);

    void operator+=(const BigInteger &big_int);
    void operator-=(const BigInteger &big_int);
    void operator*=(const BigInteger &big_int);
    void operator/=(const BigInteger &big_int);
    void operator%=(const BigInteger &big_int);

    BigInteger &operator++();
    BigInteger operator++(const int);
    BigInteger &operator--();
    BigInteger operator--(const int);

    size_t to_sizet() const;
    std::string to_str() const;
    friend std::ostream &operator<<(std::ostream &o, const BigInteger &big_int);
    friend class Util;
    friend class BigFloat;

    std::vector<char>::const_iterator begin() const;
    std::vector<char>::const_iterator end() const;
    std::vector<char>::const_reverse_iterator rbegin() const;
    std::vector<char>::const_reverse_iterator rend() const;
    char operator[](const size_t i) const;
    char &operator[](const size_t i);

    static BigInteger &to10n(BigInteger &big_int, size_t n);
};

typedef BigInteger BigInt;
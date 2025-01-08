#pragma once
#include "BigInteger.hpp"


class BigFloat
{
    private:
        bool _negative = false;
        BigInt _int_part = BigInt('0');
        BigInt _float_part = BigInt('0');
        size_t _digits = 0;
    public:
        size_t accuracy = 20;

        BigFloat();
        ~BigFloat();
        BigFloat(const char big_float);
        BigFloat(const char* big_float);
        BigFloat(const BigFloat& big_float);
        BigFloat(const BigInt& big_int);

        bool operator>(const BigFloat& big_float) const;
        bool operator<(const BigFloat& big_float) const;
        bool operator==(const BigFloat& big_float) const;
        bool operator!=(const BigFloat& big_float) const;
        bool operator>=(const BigFloat& big_float) const;
        bool operator<=(const BigFloat& big_float) const;

        bool negative() const;
        BigFloat round(const BigFloat& big_float) const;
        BigFloat round(const size_t n) const;
        BigFloat round(const BigFloat& big_float, const bool inplace);
        BigFloat round(const size_t n, const bool inplace);
        BigFloat abs() const;
        BigFloat opposite() const;
        BigFloat opposite(const bool inplace);
        BigFloat pow(const BigFloat& big_float) const;
        BigFloat pow(const size_t n) const;
        BigFloat rad(const BigFloat& big_flaot) const;
        BigFloat rad(const size_t n) const;
        friend BigFloat operator-(const BigFloat& big_float);

        BigFloat operator+(const BigFloat& big_float) const;
        BigFloat operator-(const BigFloat& big_float) const;
        BigFloat operator*(const BigFloat& big_float) const;
        BigFloat operator/(const BigFloat& big_float) const;
        void operator=(const BigFloat& big_float);
        void operator=(const BigInt& big_int);
        
        void operator+=(const BigFloat& big_float);
        void operator-=(const BigFloat& big_float);
        void operator*=(const BigFloat& big_float);
        void operator/=(const BigFloat& big_float);

        BigFloat& operator++();
        BigFloat operator++(const int);
        BigFloat& operator--();
        BigFloat operator--(const int);

        std::string to_str() const;
        BigInt to_big_int() const;
        friend std::ostream& operator<<(std::ostream& o, const BigFloat& big_float);
        friend class util;

        size_t length() const;
        size_t length_of_int_part() const;
        size_t length_of_float_part() const;

        std::vector<char>::const_iterator ibegin() const;
        std::vector<char>::const_iterator iend() const;
        std::vector<char>::const_reverse_iterator irbegin() const;
        std::vector<char>::const_reverse_iterator irend() const;

        std::vector<char>::const_iterator fbegin() const;
        std::vector<char>::const_iterator fend() const;
        std::vector<char>::const_reverse_iterator frbegin() const;
        std::vector<char>::const_reverse_iterator frend() const;

        char operator[](const long long i) const;
        char& operator[](const long long i);
};
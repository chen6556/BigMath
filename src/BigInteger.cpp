#include <algorithm>
#include "BigInteger.hpp"


BigInteger::BigInteger(){}

BigInteger::BigInteger(const char* big_int)
{
    if (*big_int == 45)
    {
        _negative = true;
        ++big_int;
    }
    while (*big_int == 48)
    {
        ++big_int;
    }
    if (_negative)
    {
        while (*big_int)
        {
            _nums.push_back(48 - *(big_int++));
        }
    }
    else
    {
        while (*big_int)
        {
            _nums.push_back(*(big_int++) - 48);
        }
    }
    if (_nums.empty())
    {
        _nums.push_back(0);
        _negative = false;
    }
}

BigInteger::BigInteger(const BigInteger& big_int)
{
    _nums.assign(big_int._nums.cbegin(), big_int._nums.cend());
    _negative = big_int._negative;
}

BigInteger::BigInteger(const std::vector<char>& big_int)
{
    _nums.assign(big_int.cbegin(), big_int.cend());
    while (!_nums.empty() && _nums.front() == 0)
    {
        _nums.erase(_nums.begin());
    }
    if (_nums.empty())
    {
        _nums.push_back(0);
    }
    _negative = _nums.front() < 0;
}

BigInteger::BigInteger(long long n)
{
    if (n == 0)
    {
        _nums.push_back(0);
    }
    else
    {
        _negative = n < 0;
        while (n != 0)
        {
            _nums.push_back(n%10);
            n /= 10;
        }
        std::reverse(_nums.begin(), _nums.end());
    }
}

BigInteger::~BigInteger(){}

/* --------------------------------------------------------- */

bool BigInteger::operator>(const BigInteger& big_int) const
{
    if (_negative != big_int._negative)
    {
        return !_negative;
    }
    else if (_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() < big_int._nums.size();
    }
    else if (!_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() > big_int._nums.size();
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        if (it_a != end_of_a)
        {
            return *it_a > *it_b;
        }
        else
        {
            return false;
        }
    }
}

bool BigInteger::operator<(const BigInteger& big_int) const
{
    if (_negative != big_int._negative)
    {
        return _negative;
    }
    else if (_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() > big_int._nums.size();
    }
    else if (!_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() < big_int._nums.size();
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        if (it_a != end_of_a)
        {
            return *it_a < *it_b;
        }
        else
        {
            return false;
        }
    }
}

bool BigInteger::operator==(const BigInteger& big_int) const
{
    if (_negative != big_int._negative || _nums.size() != big_int._nums.size())
    {
        return false;
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        return it_a == end_of_a;
    }
}

bool BigInteger::operator!=(const BigInteger& big_int) const
{
    if (_negative != big_int._negative || _nums.size() != big_int._nums.size())
    {
        return true;
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        return it_a != end_of_a;
    }
}

bool BigInteger::operator>=(const BigInteger& big_int) const
{
    if (_negative != big_int._negative)
    {
        return !_negative;
    }
    else if (_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() < big_int._nums.size();
    }
    else if (!_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() > big_int._nums.size();
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        if (it_a != end_of_a)
        {
            return *it_a > *it_b;
        }
        else
        {
            return true;
        }
    }
}

bool BigInteger::operator<=(const BigInteger& big_int) const
{
    if (_negative != big_int._negative)
    {
        return _negative;
    }
    else if (_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() > big_int._nums.size();
    }
    else if (!_negative && _nums.size() != big_int._nums.size())
    {
        return _nums.size() < big_int._nums.size();
    }
    else
    {
        std::vector<char>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        if (it_a != end_of_a)
        {
            return *it_a < *it_b;
        }
        else
        {
            return true;
        }
    }
}

/* --------------------------------------------------------- */

bool BigInteger::negative() const
{
    return _negative;
}

size_t BigInteger::length() const
{
    return _nums.size();
}

BigInteger BigInteger::abs() const
{
    if (_negative)
    {
        std::vector<char> temp;
        for (const char ch : _nums)
        {
            temp.push_back(-ch);
        }
        return BigInteger(temp);
    }
    else
    {
        return *this;
    }
}

BigInteger BigInteger::opposite() const
{
    return -*this;
}

BigInteger BigInteger::opposite(const bool inplace)
{
    if (*this == BigInteger(0ll))
    {
        return *this;
    }
    if (inplace)
    {
        _negative = !_negative;
        std::vector<char>::iterator it = _nums.begin(), end = _nums.end();
        while (it != end)
        {
            *it = -*it;
            ++it;
        }
        return *this;
    }
    else
    {
        return -*this;
    }
}

BigInteger BigInteger::pow(const BigInteger& big_int) const
{
    if (big_int <= BigInteger(0ll))
    {
        return BigInteger(1ll);
    }
    BigInteger ans(*this);
    BigInteger i(1ll);
    const BigInteger two(2ll);
    while (i < big_int)
    {
        i *= two;
        if (i >= big_int)
        {
            if (i == big_int)
            {
                ans *= ans;
            }
            else
            {
                i /= two;
            }
            break;
        }
        ans *= ans;
    }
    while (i < big_int)
    {
        ans *= *this;
        ++i;
    }
    return ans;
}

BigInteger BigInteger::pow(const size_t n) const
{
    if (n == 0)
    {
        return BigInteger(1ll);
    }
    size_t i = 1;
    BigInteger ans(*this);
    while (i < n)
    {
        i *= 2;
        if (i >= n)
        {
            if (i == n)
            {
                ans *= ans;
            }
            else
            {
                i /= 2;
            }
            break;
        }
        ans *= ans;
    }
    while (i < n)
    {
        ans *= *this;
        ++i;
    }
    return ans;
}

BigInteger BigInteger::factorial() const
{
    if (*this == BigInteger(0ll))
    {
        return BigInteger(1ll);
    }
    BigInteger ans(this->abs()), count(this->abs());
    const BigInteger two(2ll);
    while (count > two)
    {
        ans *= --count;
    }
    return ans;
}

BigInteger operator-(const BigInteger& big_int)
{
    if (big_int == BigInteger(0ll))
    {
        return big_int;
    }
    std::vector<char> temp;
    for (const char ch : big_int._nums)
    {
        temp.push_back(-ch);
    }
    return BigInteger(temp);
}

/* --------------------------------------------------------- */

BigInteger BigInteger::operator+(const BigInteger& big_int) const
{
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char> * nums_a, * nums_b;
    std::vector<char>::const_reverse_iterator it_a, it_b, end_of_a;
    bool negative_a, negative_b;
    
    if (_nums.size() < big_int._nums.size() || this->abs() < big_int.abs())
    {
        nums_a = const_cast<std::vector<char>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<char>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<char>*>(&_nums);
        nums_b = const_cast<std::vector<char>*>(&(big_int._nums));
    }
    negative_a = nums_a->front() < 0;
    negative_b = nums_b->front() < 0; 
    it_a = nums_a->crbegin();
    it_b = nums_b->crbegin();
    end_of_a = nums_a->crend();
    for (size_t i = 0, end = nums_b->size(), end2 = nums_a->size() - 1; i < end; ++i)
    {
        if (negative_a != negative_b && i < end2)
        {
            if (negative_a && *it_a + *it_b + temp_num > 0) // 借位
            {
                temp_nums.push_back(((*it_a + *it_b + temp_num) % 10 - 10) % 10);
                temp_num = (*(it_b++) - *(it_a++) + 10 + temp_num) / 10 > 0 ? 1 : 0;
            }
            else if (negative_b && *it_b + *it_a + temp_num < 0) // 借位
            {
                temp_nums.push_back(((*it_a + *it_b + temp_num) % 10 + 10) % 10);
                temp_num = (*(it_b++) - *(it_a++) - 10 + temp_num) / 10 < 0 ? -1 : 0;
            }
            else // 不用借位
            {
                const char t = *(it_a++) + *(it_b++) + temp_num;
                temp_nums.push_back(t % 10);
                temp_num = t / 10;
            }
        }
        else
        {
            const char t = *(it_a++) + *(it_b++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    while (it_a != end_of_a)
    {
        if (negative_a && *it_a + temp_num > 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 - 10) % 10);
            temp_num = (temp_num - *(it_a++) + 10) / 10 > 0 ? 1 : 0;
        }
        else if (!negative_a && *it_a + temp_num < 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 + 10) % 10);
            temp_num = (temp_num - *(it_a++) - 10) / 10 < 0 ? -1 : 0;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    std::reverse(temp_nums.begin(), temp_nums.end());
    return BigInteger(temp_nums);
}

BigInteger BigInteger::operator-(const BigInteger& big_int) const
{
    return *this + (-big_int);
}

BigInteger BigInteger::operator*(const BigInteger& big_int) const
{
    const BigInteger zero(0ll);
    if (*this == zero || big_int == zero)
    {
        return zero;
    }
    const size_t length0 = _nums.size(), length1 = big_int._nums.size();
    const size_t m = std::min(length0, length1) / 2;
    if (m < 64)
    {
        std::vector<char> temp_nums_mul, temp_nums_add, ans_nums;
        std::vector<char> temp_nums_muls[10];
        char temp_num = 0;
        std::vector<char> * nums_a, * nums_b;
        std::vector<char>::const_reverse_iterator it_a, it_b, end_of_a;
        std::vector<char>::const_iterator it_add, end_of_add, it_mul, end_of_mul;
        if (_nums.size() < big_int._nums.size())
        {
            nums_a = const_cast<std::vector<char>*>(&(big_int._nums));
            nums_b = const_cast<std::vector<char>*>(&_nums);
        }
        else
        {
            nums_a = const_cast<std::vector<char>*>(&_nums);
            nums_b = const_cast<std::vector<char>*>(&(big_int._nums));
        }
        it_b = nums_b->crbegin();
        end_of_a = nums_a->crend();
        for (size_t i = 0, end = nums_b->size(); i < end; ++i, ++it_b)
        {
            if (*it_b == 0)
            {
                temp_num = 0;
                continue;
            }
            it_a = nums_a->crbegin();
            temp_nums_add.assign(ans_nums.cbegin(), ans_nums.cend());
            ans_nums.clear();
            temp_nums_mul.assign(i, 0);
            if (temp_nums_muls[*it_b].empty())
            {
                while (it_a != end_of_a)
                {
                    const char t = *(it_a++) * (*it_b) + temp_num;
                    temp_nums_mul.push_back(t % 10);
                    temp_num = t / 10;
                }
                if (temp_num != 0)
                {
                    temp_nums_mul.push_back(temp_num);
                    temp_num = 0;
                }
                temp_nums_muls[*it_b].assign(temp_nums_mul.cbegin() + i, temp_nums_mul.cend());
            }
            else
            {
                temp_nums_mul.insert(temp_nums_mul.end(), temp_nums_muls[*it_b].cbegin(), temp_nums_muls[*it_b].cend());
            }
            it_add = temp_nums_add.cbegin();
            end_of_add = temp_nums_add.cend();
            it_mul = temp_nums_mul.cbegin();
            end_of_mul = temp_nums_mul.cend();
            while (it_add != end_of_add)
            {
                const char t = *(it_mul++) + *(it_add++) + temp_num;
                ans_nums.push_back(t % 10);
                temp_num = t / 10;
            }
            while (temp_num != 0 && it_mul != end_of_mul)
            {
                const char t = *(it_mul++) + temp_num;
                ans_nums.push_back(t % 10);
                temp_num = t / 10;
            }
            if (temp_num == 0)
            {
                ans_nums.insert(ans_nums.end(), it_mul, end_of_mul);
            }
            else
            {
                ans_nums.push_back(temp_num);
                temp_num = 0;
            }
        }
        std::reverse(ans_nums.begin(), ans_nums.end());
        return BigInteger(ans_nums);
    }
    else
    {
        BigInteger a, b, c, d;
        if (length0 >= length1)
        {
            a._nums.assign(_nums.begin(), _nums.begin() + m);
            b._nums.assign(_nums.begin() + m, _nums.end());
            c._nums.assign(big_int._nums.begin(), big_int._nums.begin() + m);
            d._nums.assign(big_int._nums.begin() + m, big_int._nums.end());
        }
        else
        {
            a._nums.assign(big_int._nums.begin(), big_int._nums.begin() + m);
            b._nums.assign(big_int._nums.begin() + m, big_int._nums.end());
            c._nums.assign(_nums.begin(), _nums.begin() + m);
            d._nums.assign(_nums.begin() + m, _nums.end());
        }
        BigInteger z0 = a * c, z2 = b * d;
        BigInteger z1 = (a + b) * (c + d) - z0 - z2;
        z0._nums.insert(z0._nums.end(), m + m, 0);
        z1._nums.insert(z1._nums.end(), m, 0);
        return z0 + (z1 + z2);
    }
}

BigInteger BigInteger::operator/(const BigInteger& big_int) const
{
    BigInteger big_int_a = this->abs(), big_int_b, temp_num, ans(0ll);
    const BigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), ten(10ll);
    if (big_int_a < abs_of_big_int || *this == zero)
    {
        return zero;
    }
    else if (big_int_a == abs_of_big_int)
    {
        return _negative == big_int._negative ? one : -one;
    }
    size_t len_a = _nums.size(), len_b = big_int._nums.size();
    while (len_a >= len_b && big_int_a >= abs_of_big_int)
    {
        temp_num = one;
        while (true)
        {
            big_int_b = abs_of_big_int * temp_num * ten.pow(len_a - len_b);
            
            if (len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * ten.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        ans += (temp_num * ten.pow(len_a - len_b));
        len_a = big_int_a._nums.size();
    }
    if (_negative == big_int._negative)
    {
        return ans;
    }
    else
    {
        return -ans;
    }
}

BigInteger BigInteger::operator%(const BigInteger& big_int) const
{
    BigInteger big_int_a = this->abs(), big_int_b, temp_num;
    const BigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), ten(10ll);
    if (*this == zero || *this == big_int || big_int == one)
    {
        return zero;
    }
    size_t len_a = _nums.size(), len_b = big_int._nums.size();
    while (len_a >= len_b && big_int_a >= abs_of_big_int)
    {
        temp_num = one;
        while (true)
        {
            big_int_b = abs_of_big_int * temp_num * ten.pow(len_a - len_b);
            
            if (len_a > 1 && len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * ten.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        len_a = big_int_a._nums.size();
    }
    if (_negative)
    {
        return -big_int_a;
    }
    else
    {
        return big_int_a;
    }
}

void BigInteger::operator=(const BigInteger& big_int)
{
    _negative = big_int._negative;
    _nums.assign(big_int._nums.cbegin(), big_int._nums.cend());
}

/* --------------------------------------------------------- */

void BigInteger::operator+=(const BigInteger& big_int)
{
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char> * nums_a, * nums_b;
    std::vector<char>::const_reverse_iterator it_a, it_b, end_of_a;
    bool negative_a, negative_b;
    if (_nums.size() < big_int._nums.size() || this->abs() < big_int.abs())
    {
        nums_a = const_cast<std::vector<char>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<char>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<char>*>(&_nums);
        nums_b = const_cast<std::vector<char>*>(&(big_int._nums));
    }
    negative_a = nums_a->front() < 0;
    negative_b = nums_b->front() < 0; 
    it_a = nums_a->crbegin();
    it_b = nums_b->crbegin();
    end_of_a = nums_a->crend();
    for (size_t i = 0, end = nums_b->size(), end2 = nums_a->size() - 1; i < end; ++i)
    {
        if (negative_a != negative_b && i < end2)
        {
            if (negative_a && *it_a + *it_b + temp_num > 0) // 借位
            {
                temp_nums.push_back(((*it_a + *it_b + temp_num) % 10 - 10) % 10);
                temp_num = (*(it_b++) - *(it_a++) + 10 + temp_num) / 10 > 0 ? 1 : 0;
            }
            else if (negative_b && *it_b + *it_a + temp_num < 0) // 借位
            {
                temp_nums.push_back(((*it_a + *it_b + temp_num) % 10 + 10) % 10);
                temp_num = (*(it_b++) - *(it_a++) - 10 + temp_num) / 10 < 0 ? -1 : 0;
            }
            else // 不用借位
            {
                const char t = *(it_a++) + *(it_b++) + temp_num;
                temp_nums.push_back(t % 10);
                temp_num = t / 10;
            }
        }
        else
        {
            const char t = *(it_a++) + *(it_b++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    while (it_a != end_of_a)
    {
        if (negative_a && *it_a + temp_num > 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 - 10) % 10);
            temp_num = (temp_num - *(it_a++) + 10) / 10;
        }
        else if (!negative_a && *it_a + temp_num < 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 + 10) % 10);
            temp_num = (temp_num - *(it_a++) - 10) / 10;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
}

void BigInteger::operator-=(const BigInteger& big_int)
{
    *this += (-big_int);
}

void BigInteger::operator*=(const BigInteger& big_int)
{
    const BigInteger zero(0ll);
    if (*this == zero || big_int == zero)
    {
        _negative = false;
        _nums.clear();
        _nums.push_back(0);
        return;
    }
    if (std::min(_nums.size(), big_int._nums.size()) < 128)
    {
        std::vector<char> temp_nums_mul, temp_nums_add, ans_nums;
        std::vector<char> temp_nums_muls[10];
        char temp_num = 0;
        std::vector<char> * nums_a, * nums_b;
        std::vector<char>::const_reverse_iterator it_a, it_b, end_of_a;
        std::vector<char>::const_iterator it_add, end_of_add, it_mul, end_of_mul;
        if (_nums.size() < big_int._nums.size())
        {
            nums_a = const_cast<std::vector<char>*>(&(big_int._nums));
            nums_b = const_cast<std::vector<char>*>(&_nums);
        }
        else
        {
            nums_a = const_cast<std::vector<char>*>(&_nums);
            nums_b = const_cast<std::vector<char>*>(&(big_int._nums));
        }
        it_b = nums_b->crbegin();
        end_of_a = nums_a->crend();
        for (size_t i = 0, end = nums_b->size(); i < end; ++i, ++it_b)
        {
            if (*it_b == 0)
            {
                temp_num = 0;
                continue;
            }
            it_a = nums_a->crbegin();
            temp_nums_add.assign(ans_nums.cbegin(), ans_nums.cend());
            ans_nums.clear();
            temp_nums_mul.assign(i, 0);
            if (temp_nums_muls[*it_b].empty())
            {
                while (it_a != end_of_a)
                {
                    const char t = *(it_a++) * (*it_b) + temp_num;
                    temp_nums_mul.push_back(t % 10);
                    temp_num = t / 10;
                }
                if (temp_num != 0)
                {
                    temp_nums_mul.push_back(temp_num);
                    temp_num = 0;
                }
                temp_nums_muls[*it_b].assign(temp_nums_mul.cbegin() + i, temp_nums_mul.cend());
            }
            else
            {
                temp_nums_mul.insert(temp_nums_mul.end(), temp_nums_muls[*it_b].cbegin(), temp_nums_muls[*it_b].cend());
            }
            it_add = temp_nums_add.cbegin();
            end_of_add = temp_nums_add.cend();
            it_mul = temp_nums_mul.cbegin();
            end_of_mul = temp_nums_mul.cend();
            while (it_add != end_of_add)
            {
                const char t = *(it_mul++) + *(it_add++) + temp_num;
                ans_nums.push_back(t % 10);
                temp_num = t / 10;
            }
            while (temp_num != 0 && it_mul != end_of_mul)
            {
                const char t = *(it_mul++) + temp_num;
                ans_nums.push_back(t % 10);
                temp_num = t / 10;
            }
            if (temp_num == 0)
            {
                ans_nums.insert(ans_nums.end(), it_mul, end_of_mul);
            }
            else
            {
                ans_nums.push_back(temp_num);
                temp_num = 0;
            }
        }
        _nums.assign(ans_nums.crbegin(), ans_nums.crend());
        _negative = _nums.front() < 0;
    }
    else
    {
        *this = (*this) * big_int;
    }
}

void BigInteger::operator/=(const BigInteger& big_int)
{
    BigInteger big_int_a = this->abs(), big_int_b, temp_num, ans(0ll);
    const BigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), ten(10ll);
    if (big_int_a < abs_of_big_int || *this == zero)
    {
        _negative = false;
        _nums.clear();
        _nums.push_back(0);
        return;
    }
    else if (big_int_a == abs_of_big_int)
    {
        _negative = (_negative != big_int._negative);
        _nums.clear();
        _nums.push_back(_negative ? -1 : 1);
        return;
    }
    size_t len_a = _nums.size(), len_b = big_int._nums.size();
    while (len_a >= len_b && big_int_a >= abs_of_big_int)
    {
        temp_num = one;
        while (true)
        {
            big_int_b = abs_of_big_int * temp_num * ten.pow(len_a - len_b);
            
            if (len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * ten.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        ans += (temp_num * ten.pow(len_a - len_b));
        len_a = big_int_a._nums.size();
    }
    if (_negative == big_int._negative)
    {
        *this = ans;
    }
    else
    {
        *this = -ans;
    }
}

void BigInteger::operator%=(const BigInteger& big_int)
{
    BigInteger big_int_a = this->abs(), big_int_b, zero(0ll), one(1ll), ten(10ll), temp_num;
    const BigInteger abs_of_big_int = big_int.abs();
    if (*this == zero || *this == big_int || big_int == one)
    {
        _negative = false;
        _nums.clear();
        _nums.push_back(0);
        return;
    }
    size_t len_a = _nums.size(), len_b = big_int._nums.size();
    while (len_a >= len_b && big_int_a >= abs_of_big_int)
    {
        temp_num = one;
        while (true)
        {
            big_int_b = abs_of_big_int * temp_num * ten.pow(len_a - len_b);
            
            if (len_a > 1 && len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * ten.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        len_a = big_int_a._nums.size();
    }
    if (_negative)
    {
        *this = -big_int_a;
    }
    else
    {
        *this = big_int_a;
    }
}

BigInteger& BigInteger::operator++()
{
    if ((_negative && _nums.back() != 0) || (!_negative && _nums.back() != 9))
    {
        _nums.back()++;
        return *this;
    }
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (_negative && *it_a == 0) // 借位
    {
        temp_nums.push_back(-9);
        temp_num = 1;
        ++it_a;
    }
    else // 不用借位
    {
        const char t = *(it_a++) + 1;
        temp_nums.push_back(t % 10);
        temp_num = t / 10;
    }
    while (it_a != end_of_a)
    {
        if (_negative && *it_a + temp_num > 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 - 10) % 10);
            temp_num = (temp_num - *(it_a++) + 10) / 10;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return *this;
}

BigInteger BigInteger::operator++(const int)
{
    if ((_negative && _nums.back() != 0) || (!_negative && _nums.back() != 9))
    {
        BigInteger temp(*this);
        temp._nums.back()++;
        return temp;
    }
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (_negative && *it_a == 0) // 借位
    {
        temp_nums.push_back(-9);
        temp_num = 1;
        ++it_a;
    }
    else // 不用借位
    {
        const char t = *(it_a++) + 1;
        temp_nums.push_back(t % 10);
        temp_num = t / 10;
    }
    while (it_a != end_of_a)
    {
        if (_negative && *it_a + temp_num > 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 - 10) % 10);
            temp_num = (temp_num - *(it_a++) + 10) / 10;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    BigInteger temp(*this);
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return temp;
}

BigInteger& BigInteger::operator--()
{
    if ((_negative && _nums.back() != -9) || (!_negative && _nums.back() != 0))
    {
        _nums.back()--;
        return *this;
    }
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (!_negative && _nums.size() > 1 && *it_a == 0) // 借位
    {
        temp_nums.push_back(9);
        temp_num = -1;
        ++it_a;
    }
    else // 不用借位
    {
        const char t = *(it_a++) - 1;
        temp_nums.push_back(t % 10);
        temp_num = t / 10;
    }
    while (it_a != end_of_a)
    {
        if (!_negative && *it_a + temp_num < 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 + 10) % 10);
            temp_num = (temp_num - *(it_a++) - 10) / 10;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return *this;
}

BigInteger BigInteger::operator--(const int)
{
    if ((_negative && _nums.back() != -9) || (!_negative && _nums.back() != 0))
    {
        BigInteger temp(*this);
        temp._nums.back()--;
        return temp;
    }
    std::vector<char> temp_nums;
    char temp_num = 0;
    std::vector<char>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (!_negative && _nums.size() > 1 && *it_a == 0) // 借位
    {
        temp_nums.push_back(9);
        temp_num = -1;
        ++it_a;
    }
    else // 不用借位
    {
        const char t = *(it_a++) - 1;
        temp_nums.push_back(t % 10);
        temp_num = t / 10;
    }
    while (it_a != end_of_a)
    {
        if (!_negative && *it_a + temp_num < 0)
        {
            temp_nums.push_back(((*it_a + temp_num) % 10 + 10) % 10);
            temp_num = (temp_num - *(it_a++) - 10) / 10;
        }
        else
        {
            const char t = *(it_a++) + temp_num;
            temp_nums.push_back(t % 10);
            temp_num = t / 10;
        }
    }
    if (temp_num != 0)
    {
        temp_nums.push_back(temp_num);
    }
    while (temp_nums.size() > 1 && temp_nums.back() == 0)
    {
        temp_nums.pop_back();
    }
    BigInteger temp(*this);
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return temp;
}

/* --------------------------------------------------------- */

std::string BigInteger::to_str() const
{
    std::vector<char> temp;
    if (_negative)
    {
        temp.push_back('-');
        for (const char ch : _nums)
        {
            temp.push_back(48 - ch);
        }
    }
    else
    {
        for (const char ch : _nums)
        {
            temp.push_back(ch + 48);
        }
    }
    temp.push_back('\0');
    return std::string(temp.cbegin(), temp.cend());
}

size_t BigInteger::to_uint() const
{
    size_t ans = 0, i = 1;
    std::vector<char>::const_reverse_iterator it = _nums.crbegin();
    const std::vector<char>::const_reverse_iterator end = _nums.crend();
    while (it != end)
    {
        ans += *it++ * i;
        i *= 10;
    }
    return ans;
}

int BigInteger::to_int() const
{
    int ans = 0, i = 1;
    std::vector<char>::const_reverse_iterator it = _nums.crbegin();
    const std::vector<char>::const_reverse_iterator end = _nums.crend();
    while (it != end)
    {
        ans += *it++ * i;
        i *= 10;
    }
    return ans;
}

/* --------------------------------------------------------- */

std::ostream& operator<<(std::ostream& o, const BigInteger& big_int)
{
    if (big_int._negative)
    {
        o << '-';
        for (const char ch : big_int._nums)
        {
            o << char(48 - ch);
        }
    }
    else
    {
        for (const char ch : big_int._nums)
        {
            o << char(ch + 48);
        }
    }
    return o;
}

/* --------------------------------------------------------- */
 
std::vector<char>::const_iterator BigInteger::begin() const
{
    return _nums.cbegin();
}

std::vector<char>::const_iterator BigInteger::end() const
{
    return _nums.cend();
}

std::vector<char>::const_reverse_iterator BigInteger::rbegin() const
{
    return _nums.crbegin();
}
        
std::vector<char>::const_reverse_iterator BigInteger::rend() const
{
    return _nums.crend();
}

char BigInteger::operator[](const size_t i) const
{
    return _nums[i];
}

char& BigInteger::operator[](const size_t i)
{
    return _nums[i];
}
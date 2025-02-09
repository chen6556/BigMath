#include <algorithm>
#include "FastBigInteger.hpp"

typedef long long ll;
const static BigInt SN_BI(ll(INT_MAX) + 1);
const static size_t LEN_SN = SN_BI.length(), SN = size_t(INT_MAX) + 1;

FastBigInteger::FastBigInteger(){}

FastBigInteger::FastBigInteger(const char* big_int)
{
    BigInt temp_int(big_int), big_int_b;
    _negative = temp_int.negative();
    BigInt big_int_a = temp_int.abs(), temp_num, ans(0ll);
    const BigInt zero(0ll), one(1ll), ten(10ll);
    size_t len_a = temp_int.length();
    while (big_int_a >= SN_BI)
    {
        while (len_a >= LEN_SN && big_int_a >= SN_BI)
        {
            temp_num = one;
            while (true)
            {
                big_int_b = SN_BI * temp_num * ten.pow(len_a - LEN_SN);
                
                if (len_a > LEN_SN && temp_num == one && big_int_b > big_int_a)
                {
                    --len_a; 
                    continue;
                }
                else if (big_int_a < big_int_b)
                {   
                    big_int_b = SN_BI * --temp_num * ten.pow(len_a - LEN_SN);
                    break;
                }
                ++temp_num;
            }
            big_int_a -= big_int_b;
            ans += (temp_num * ten.pow(len_a - LEN_SN));
            len_a = big_int_a.length();
        }
        if (_negative)
        {
            _nums.push_back(-big_int_a.to_int());
        }
        else
        {
            _nums.push_back(big_int_a.to_int());
        }
        big_int_a = ans;
        ans = zero;
    }
    if (_negative)
    {
        _nums.push_back(-big_int_a.to_int());
    }
    else
    {
        _nums.push_back(big_int_a.to_int());
    }
    while (_nums.size() > 1 && _nums.back() == 0)
    {
        _nums.pop_back();
    }
    std::reverse(_nums.begin(), _nums.end());
}

FastBigInteger::FastBigInteger(const FastBigInteger& big_int)
{
    _nums.assign(big_int._nums.cbegin(), big_int._nums.cend());
    _negative = big_int._negative;
}

FastBigInteger::FastBigInteger(const std::vector<int>& big_int)
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

FastBigInteger::FastBigInteger(const BigInt& big_int)
{
    BigInt temp_int(big_int), big_int_b;
    _negative = temp_int.negative();
    BigInt big_int_a = temp_int.abs(), temp_num, ans(0ll);
    const BigInt zero(0ll), one(1ll), ten(10ll);
    size_t len_a = temp_int.length();
    while (big_int_a >= SN_BI)
    {
        while (len_a >= LEN_SN && big_int_a >= SN_BI)
        {
            temp_num = one;
            while (true)
            {
                big_int_b = SN_BI * temp_num * ten.pow(len_a - LEN_SN);
                
                if (len_a > LEN_SN && temp_num == one && big_int_b > big_int_a)
                {
                    --len_a; 
                    continue;
                }
                else if (big_int_a < big_int_b)
                {   
                    big_int_b = SN_BI * --temp_num * ten.pow(len_a - LEN_SN);
                    break;
                }
                ++temp_num;
            }
            big_int_a -= big_int_b;
            ans += (temp_num * ten.pow(len_a - LEN_SN));
            len_a = big_int_a.length();
        }
        if (_negative)
        {
            _nums.push_back(-big_int_a.to_int());
        }
        else
        {
            _nums.push_back(big_int_a.to_int());
        }
        big_int_a = ans;
        ans = zero;
    }
    if (_negative)
    {
        _nums.push_back(-big_int_a.to_int());
    }
    else
    {
        _nums.push_back(big_int_a.to_int());
    }
    while (_nums.size() > 1 && _nums.back() == 0)
    {
        _nums.pop_back();
    }
    std::reverse(_nums.begin(), _nums.end());
}

FastBigInteger::FastBigInteger(long long n)
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
            _nums.push_back(n % SN);
            n /= SN;
        }
        std::reverse(_nums.begin(), _nums.end());
    }
}

FastBigInteger::~FastBigInteger(){}

/* --------------------------------------------------------- */

bool FastBigInteger::operator>(const FastBigInteger& big_int) const
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
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
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

bool FastBigInteger::operator<(const FastBigInteger& big_int) const
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
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
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

bool FastBigInteger::operator==(const FastBigInteger& big_int) const
{
    if (_negative != big_int._negative || _nums.size() != big_int._nums.size())
    {
        return false;
    }
    else
    {
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        return it_a == end_of_a;
    }
}

bool FastBigInteger::operator!=(const FastBigInteger& big_int) const
{
    if (_negative != big_int._negative || _nums.size() != big_int._nums.size())
    {
        return true;
    }
    else
    {
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
        while (it_a != end_of_a && *it_a == *it_b)
        {
            ++it_a;
            ++it_b;
        }
        return it_a != end_of_a;
    }
}

bool FastBigInteger::operator>=(const FastBigInteger& big_int) const
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
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
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

bool FastBigInteger::operator<=(const FastBigInteger& big_int) const
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
        std::vector<int>::const_iterator it_a = _nums.cbegin(), it_b = big_int._nums.cbegin(), end_of_a = _nums.cend();
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

bool FastBigInteger::negative() const
{
    return _negative;
}

size_t FastBigInteger::length() const
{
    return _nums.size();
}

FastBigInteger FastBigInteger::abs() const
{
    if (_negative)
    {
        std::vector<int> temp;
        for (const int ch : _nums)
        {
            temp.push_back(-ch);
        }
        return FastBigInteger(temp);
    }
    else
    {
        return *this;
    }
}

FastBigInteger FastBigInteger::opposite() const
{
    return -*this;
}

FastBigInteger FastBigInteger::opposite(const bool inplace)
{
    if (*this == FastBigInteger(0ll))
    {
        return *this;
    }
    if (inplace)
    {
        _negative = !_negative;
        std::vector<int>::iterator it = _nums.begin(), end = _nums.end();
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

FastBigInteger FastBigInteger::pow(const FastBigInteger& big_int) const
{
    if (big_int <= FastBigInteger(0ll))
    {
        return FastBigInteger(1ll);
    }
    FastBigInteger temp(*this);
    FastBigInteger i(1ll);
    const FastBigInteger two(2ll);
    while (i < big_int)
    {
        i *= two;
        if (i >= big_int)
        {
            if (i == big_int)
            {
                temp *= temp;
            }
            else
            {
                i /= two;
            }
            break;
        }
        temp *= temp;
    }
    while (i < big_int)
    {
        temp *= *this;
        ++i;
    }

    return temp;
}

FastBigInteger FastBigInteger::pow(const size_t n) const
{
    if (n == 0)
    {
        return FastBigInteger(1ll);
    }
    FastBigInteger temp(*this);
    size_t i = 1;
    while (i < n)
    {
        i *= 2;
        if (i >= n)
        {
            if (i == n)
            {
                temp *= temp;
            }
            else
            {
                i /= 2;
            }
            break;
        }
        temp *= temp;
    }
    while (i < n)
    {
        temp *= *this;
        ++i;
    }
    return temp;
}

FastBigInteger FastBigInteger::factorial() const
{
    if (*this == FastBigInteger(0ll))
    {
        return FastBigInteger(1ll);
    }
    FastBigInteger ans(this->abs()), count(this->abs());
    const FastBigInteger two(2ll);
    while (count > two)
    {
        ans *= --count;
    }
    return ans;
}

FastBigInteger operator-(const FastBigInteger& big_int)
{
    if (big_int == FastBigInteger(0ll))
    {
        return big_int;
    }
    std::vector<int> temp;
    for (const int ch : big_int._nums)
    {
        temp.push_back(-ch);
    }
    return FastBigInteger(temp);
}

/* --------------------------------------------------------- */

FastBigInteger FastBigInteger::operator+(const FastBigInteger& big_int) const
{
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int> * nums_a, * nums_b;
    std::vector<int>::const_reverse_iterator it_a, it_b, end_of_a;
    bool negative_a, negative_b;
    
    if (this->abs() < big_int.abs())
    {
        nums_a = const_cast<std::vector<int>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<int>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<int>*>(&_nums);
        nums_b = const_cast<std::vector<int>*>(&(big_int._nums));
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
            if (negative_a && ll(*it_a) + ll(*it_b) + ll(temp_num) > 0) // 借位
            {
                temp_nums.push_back(((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN - SN) % SN);
                temp_num = (ll(*(it_b++)) - ll(*(it_a++)) + SN + ll(temp_num)) / SN > 0 ? 1 : 0;
            }
            else if (negative_b && ll(*it_b) + ll(*it_a) + ll(temp_num) < 0) // 借位
            {
                temp_nums.push_back(((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN + SN) % SN);
                temp_num = (ll(*(it_b++)) - ll(*(it_a++)) - SN + ll(temp_num)) / SN < 0 ? -1 : 0;
            }
            else // 不用借位
            {
                temp_nums.push_back((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN);
                temp_num = (ll(*(it_a++)) + ll(*(it_b++)) + ll(temp_num)) / SN;
            }
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(*(it_b++)) + ll(temp_num)) / SN;
        }
    }
    while (it_a != end_of_a)
    {
        if (negative_a && ll(*it_a) + ll(temp_num) > 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN - SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) + SN) / SN > 0 ? 1 : 0;
        }
        else if (!negative_a && ll(*it_a) + ll(temp_num) < 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN + SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) - SN) / SN < 0 ? -1 : 0;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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
    return FastBigInteger(temp_nums);
}

FastBigInteger FastBigInteger::operator-(const FastBigInteger& big_int) const
{
    return *this + (-big_int);
}

FastBigInteger FastBigInteger::operator*(const FastBigInteger& big_int) const
{
    const FastBigInteger zero(0ll);
    if (*this == zero || big_int == zero)
    {
        return zero;
    }
    std::vector<int> temp_nums_mul, temp_nums_add, ans_nums;
    std::vector<int> temp_nums_muls[10];
    int temp_num = 0;
    std::vector<int> * nums_a, * nums_b;
    std::vector<int>::const_reverse_iterator it_a, it_b, end_of_a;
    std::vector<int>::const_iterator it_add, end_of_add, it_mul, end_of_mul;
    if (_nums.size() < big_int._nums.size())
    {
        nums_a = const_cast<std::vector<int>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<int>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<int>*>(&_nums);
        nums_b = const_cast<std::vector<int>*>(&(big_int._nums));
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
                temp_nums_mul.push_back((ll(*it_a) * ll(*it_b) + ll(temp_num)) % SN);
                temp_num = (ll(*(it_a++)) * ll(*it_b) + ll(temp_num)) / SN;
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
            ans_nums.push_back((ll(*it_mul) + ll(*it_add) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_mul++)) + ll(*(it_add++)) + ll(temp_num)) / SN;
        }
        while (it_mul != end_of_mul)
        {
            ans_nums.push_back((ll(*it_mul) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_mul++)) + ll(temp_num)) / SN;
        }
        if (temp_num != 0)
        {
            ans_nums.push_back(temp_num);
            temp_num = 0;
        }        
    }
    std::reverse(ans_nums.begin(), ans_nums.end());
    return FastBigInteger(ans_nums);
}

FastBigInteger FastBigInteger::operator/(const FastBigInteger& big_int) const
{
    FastBigInteger big_int_a = this->abs(), big_int_b, temp_num, ans(0ll);
    const FastBigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), sn(size_t(INT_MAX) + 1);
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
            big_int_b = abs_of_big_int * temp_num * sn.pow(len_a - len_b);
            
            if (len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * sn.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        ans += (temp_num * sn.pow(len_a - len_b));
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

FastBigInteger FastBigInteger::operator%(const FastBigInteger& big_int) const
{
    FastBigInteger big_int_a = this->abs(), big_int_b, temp_num;
    const FastBigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), sn(size_t(INT_MAX) + 1);
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
            big_int_b = abs_of_big_int * temp_num * sn.pow(len_a - len_b);
            
            if (len_a > 1 && len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * sn.pow(len_a - len_b);
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

void FastBigInteger::operator=(const FastBigInteger& big_int)
{
    _negative = big_int._negative;
    _nums.assign(big_int._nums.cbegin(), big_int._nums.cend());
}

/* --------------------------------------------------------- */

void FastBigInteger::operator+=(const FastBigInteger& big_int)
{
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int> * nums_a, * nums_b;
    std::vector<int>::const_reverse_iterator it_a, it_b, end_of_a;
    bool negative_a, negative_b;
    if (this->abs() < big_int.abs())
    {
        nums_a = const_cast<std::vector<int>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<int>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<int>*>(&_nums);
        nums_b = const_cast<std::vector<int>*>(&(big_int._nums));
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
            if (negative_a && ll(*it_a) + ll(*it_b) + ll(temp_num) > 0) // 借位
            {
                temp_nums.push_back(((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN - SN) % SN);
                temp_num = (ll(*(it_b++)) - ll(*(it_a++)) + SN + ll(temp_num)) / SN > 0 ? 1 : 0;
            }
            else if (negative_b && ll(*it_b) + ll(*it_a) + ll(temp_num) < 0) // 借位
            {
                temp_nums.push_back(((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN + SN) % SN);
                temp_num = (ll(*(it_b++)) - ll(*(it_a++)) - SN + ll(temp_num)) / SN < 0 ? -1 : 0;
            }
            else // 不用借位
            {
                temp_nums.push_back((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN);
                temp_num = (ll(*(it_a++)) + ll(*(it_b++)) + ll(temp_num)) / SN;
            }
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(*it_b) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(*(it_b++)) + ll(temp_num)) / SN;
        }
    }
    while (it_a != end_of_a)
    {
        if (negative_a && ll(*it_a) + ll(temp_num) > 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN - SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) + SN) / SN;
        }
        else if (!negative_a && ll(*it_a) + ll(temp_num) < 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN + SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) - SN) / SN;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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

void FastBigInteger::operator-=(const FastBigInteger& big_int)
{
    *this += (-big_int);
}

void FastBigInteger::operator*=(const FastBigInteger& big_int)
{
    const FastBigInteger zero(0ll);
    if (*this == zero || big_int == zero)
    {
        _negative = false;
        _nums.clear();
        _nums.push_back(0);
        return;
    }
    std::vector<int> temp_nums_mul, temp_nums_add, ans_nums;
    std::vector<int> temp_nums_muls[10];
    int temp_num = 0;
    std::vector<int> * nums_a, * nums_b;
    std::vector<int>::const_reverse_iterator it_a, it_b, end_of_a;
    std::vector<int>::const_iterator it_add, end_of_add, it_mul, end_of_mul;
    if (_nums.size() < big_int._nums.size())
    {
        nums_a = const_cast<std::vector<int>*>(&(big_int._nums));
        nums_b = const_cast<std::vector<int>*>(&_nums);
    }
    else
    {
        nums_a = const_cast<std::vector<int>*>(&_nums);
        nums_b = const_cast<std::vector<int>*>(&(big_int._nums));
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
                temp_nums_mul.push_back((ll(*it_a) * ll(*it_b) + ll(temp_num)) % SN);
                temp_num = (ll(*(it_a++)) * ll(*it_b) + ll(temp_num)) / SN;
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
            ans_nums.push_back((ll(*it_mul) + ll(*it_add) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_mul++)) + ll(*(it_add++)) + ll(temp_num)) / SN;
        }
        while (it_mul != end_of_mul)
        {
            ans_nums.push_back((ll(*it_mul) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_mul++)) + ll(temp_num)) / SN;
        }
        if (temp_num != 0)
        {
            ans_nums.push_back(temp_num);
            temp_num = 0;
        }        
    }
    _nums.assign(ans_nums.crbegin(), ans_nums.crend());
    _negative = _nums.front() < 0;
}

void FastBigInteger::operator/=(const FastBigInteger& big_int)
{
    FastBigInteger big_int_a = this->abs(), big_int_b, temp_num, ans(0ll);
    const FastBigInteger abs_of_big_int = big_int.abs(), zero(0ll), one(1ll), sn(size_t(INT_MAX) + 1);
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
            big_int_b = abs_of_big_int * temp_num * sn.pow(len_a - len_b);
            
            if (len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * sn.pow(len_a - len_b);
                break;
            }
            ++temp_num;
        }
        big_int_a -= big_int_b;
        ans += (temp_num * sn.pow(len_a - len_b));
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

void FastBigInteger::operator%=(const FastBigInteger& big_int)
{
    FastBigInteger big_int_a = this->abs(), big_int_b, zero(0ll), one(1ll), temp_num;
    const FastBigInteger abs_of_big_int = big_int.abs(), sn(ll(INT_MAX) + 1);
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
            big_int_b = abs_of_big_int * temp_num * sn.pow(len_a - len_b);
            
            if (len_a > 1 && len_a > len_b && temp_num == one && big_int_b > big_int_a)
            {
                --len_a; 
                continue;
            }
            else if (big_int_a < big_int_b)
            {   
                big_int_b = abs_of_big_int * --temp_num * sn.pow(len_a - len_b);
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

FastBigInteger& FastBigInteger::operator++()
{
    if ((_negative && _nums.back() != 0) || (!_negative && _nums.back() != INT_MAX))
    {
        _nums.back()++;
        return *this;
    }
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (_negative && *it_a == 0) // 借位
    {
        temp_nums.push_back(INT_MIN);
        temp_num = 1;
        ++it_a;
    }
    else // 不用借位
    {
        temp_nums.push_back((ll(*it_a) + 1) % SN);
        temp_num = (ll(*(it_a++)) + 1) / SN;
    }
    while (it_a != end_of_a)
    {
        if (_negative && ll(*it_a) + ll(temp_num) > 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN - SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) + SN) / SN;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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

FastBigInteger FastBigInteger::operator++(const int)
{
    if ((_negative && _nums.back() != 0) || (!_negative && _nums.back() != INT_MAX))
    {
        FastBigInteger temp(*this);
        temp._nums.back()++;
        return temp;
    }
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (_negative && *it_a == 0) // 借位
    {
        temp_nums.push_back(INT_MIN);
        temp_num = 1;
        ++it_a;
    }
    else // 不用借位
    {
        temp_nums.push_back((ll(*it_a) + 1) % SN);
        temp_num = (ll(*(it_a++)) + 1) / SN;
    }
    while (it_a != end_of_a)
    {
        if (_negative && ll(*it_a) + ll(temp_num) > 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN - SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) + SN) / SN;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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
    FastBigInteger temp(*this);
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return temp;
}

FastBigInteger& FastBigInteger::operator--()
{
    if ((_negative && _nums.back() != -INT_MAX) || (!_negative && _nums.back() != 0))
    {
        _nums.back()--;
        return *this;
    }
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (!_negative && _nums.size() > 1 && *it_a == 0) // 借位
    {
        temp_nums.push_back(INT_MAX);
        temp_num = -1;
        ++it_a;
    }
    else // 不用借位
    {
        temp_nums.push_back((ll(*it_a) - 1) % SN);
        temp_num = (ll(*(it_a++)) - 1) / SN;
    }
    while (it_a != end_of_a)
    {
        if (!_negative && ll(*it_a) + ll(temp_num) < 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN + SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) - SN) / SN;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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

FastBigInteger FastBigInteger::operator--(const int)
{
    if ((_negative && _nums.back() != -INT_MAX) || (!_negative && _nums.back() != 0))
    {
        FastBigInteger temp(*this);
        temp._nums.back()--;
        return temp;
    }
    std::vector<int> temp_nums;
    int temp_num = 0;
    std::vector<int>::const_reverse_iterator it_a = _nums.crbegin(), end_of_a = _nums.crend();
    if (!_negative && _nums.size() > 1 && *it_a == 0) // 借位
    {
        temp_nums.push_back(INT_MAX);
        temp_num = -1;
        ++it_a;
    }
    else // 不用借位
    {
        temp_nums.push_back((ll(*it_a) - 1) % SN);
        temp_num = (ll(*(it_a++)) - 1) / SN;
    }
    while (it_a != end_of_a)
    {
        if (!_negative && ll(*it_a) + ll(temp_num) < 0)
        {
            temp_nums.push_back(((ll(*it_a) + ll(temp_num)) % SN + SN) % SN);
            temp_num = (ll(temp_num) - ll(*(it_a++)) - SN) / SN;
        }
        else
        {
            temp_nums.push_back((ll(*it_a) + ll(temp_num)) % SN);
            temp_num = (ll(*(it_a++)) + ll(temp_num)) / SN;
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
    FastBigInteger temp(*this);
    _nums.assign(temp_nums.crbegin(), temp_nums.crend());
    _negative = _nums.front() < 0;
    return temp;
}

/* --------------------------------------------------------- */

std::string FastBigInteger::to_str() const
{
    BigInt ans(0ll), temp(1ll);
    size_t i = 0;
    std::vector<int>::const_reverse_iterator it = _nums.crbegin();
    const std::vector<int>::const_reverse_iterator end = _nums.crend();
    while (it != end)
    {
        ans += (BigInt(*it++) * temp);
        temp *= SN_BI;
    }
    return ans.to_str();
}

BigInt FastBigInteger::to_BigInt() const
{
    std::vector<int>::const_reverse_iterator it_a = _nums.crbegin(), it_b = it_a;
    const std::vector<int>::const_reverse_iterator end = _nums.crend(); 
    const size_t step = _nums.size() / Constant::CPU_CORES;
    BigInt ans(0ll);
    if (step > 2)
    {
        std::vector<std::thread> threads;
        unsigned char i = 0;
        std::vector<BigInt> output;
        while ( i < Constant::CPU_CORES - 1)
        {   
            for (size_t j = 0; j < step; ++j, ++it_b);
            threads.push_back(std::thread(&FastBigInteger::to_BigInt_subfunction, step*i, it_a, it_b, std::ref(output)));
            it_a = it_b;
            ++i;
        }
        threads.push_back(std::thread(&FastBigInteger::to_BigInt_subfunction, step*i, it_a, end, std::ref(output)));
        for (std::thread& t : threads)
        {
            t.join();
        }
        for (const BigInt& value : output)
        {
            ans += value;
        }
    }
    else
    {
        BigInt temp(1ll);
        while (it_a != end)
        {
            ans += (BigInt(*it_a++) * temp);
            temp *= SN_BI;
        }
    }
    return ans;
}

/* --------------------------------------------------------- */

void FastBigInteger::to_BigInt_subfunction(size_t index, std::vector<int>::const_reverse_iterator it, const std::vector<int>::const_reverse_iterator end, std::vector<BigInt>& output)
{
    BigInt ans(0ll), temp = SN_BI.pow(index);
    while (it != end)
    {
        ans += (BigInt(*it++) * temp);
        temp *= SN_BI;
    }
    output.push_back(ans);
}

std::ostream& operator<<(std::ostream& o, const FastBigInteger& big_int)
{
    std::vector<int>::const_reverse_iterator it_a = big_int._nums.crbegin(), it_b = it_a;
    const std::vector<int>::const_reverse_iterator end = big_int._nums.crend();
    const size_t step = big_int.length() / Constant::CPU_CORES;
    BigInt ans(0ll);
    if (step > 2)
    {
        unsigned char i = 0;
        std::vector<std::thread> threads;
        std::vector<BigInt> output;
        while ( i < Constant::CPU_CORES - 1)
        {   
            for (size_t j = 0; j < step; ++j, ++it_b);
            threads.push_back(std::thread(&FastBigInteger::to_BigInt_subfunction, step*i, it_a, it_b, std::ref(output)));
            it_a = it_b;
            ++i;
        }
        threads.push_back(std::thread(&FastBigInteger::to_BigInt_subfunction, step*i, it_a, end, std::ref(output)));
        for (std::thread& t : threads)
        {
            t.join();
        }
        for (const BigInt& value : output)
        {
            ans += value;
        }
    }
    else
    {
        BigInt temp(1ll);
        while (it_a != end)
        {
            ans += (BigInt(*it_a++) * temp);
            temp *= SN_BI;
        }
    }
    o << ans;
    return o;
}
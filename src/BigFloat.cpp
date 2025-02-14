#include "BigFloat.hpp"


const BigFloat BigFloat::ZERO = BigInteger::ZERO;
const BigFloat BigFloat::ONE = BigInteger::ONE;

BigFloat::BigFloat(){}

BigFloat::~BigFloat(){}

BigFloat::BigFloat(const char big_float)
{
    _int_part = BigInt(static_cast<long long>(big_float));
}

BigFloat::BigFloat(const char *big_float)
{
    _negative = *big_float == 45;
    std::string temp(big_float);
    if (temp.find('.') != std::string::npos)
    {
        size_t index = temp.find_first_of('.'), end = temp.length() - 1;
        _int_part = BigInt(temp.substr(0, index).c_str());
        while (temp[end] == '0')
        {
            --end;
        }
        if (end > index)
        {
            if (_negative)
            {
                _float_part = BigInt(('-'+temp.substr(index+1, end-index)+'\0').c_str());
            }
            else
            {
                _float_part = BigInt((temp.substr(index+1, end-index)+'\0').c_str());
            }
            _digits = end - index - _float_part.length();
        }
    }
    else
    {
        _int_part = BigInt(big_float);
    }
    accuracy = std::max(accuracy, _digits+_float_part.length());
}

BigFloat::BigFloat(const BigFloat &big_float)
{
    _negative = big_float._negative;
    _int_part = big_float._int_part;
    _float_part = big_float._float_part;
    _digits = big_float._digits;
    accuracy = std::max(accuracy, big_float.accuracy);
}

BigFloat::BigFloat(const BigInt &big_int)
{
    _negative = big_int.negative();
    _int_part = big_int;
    accuracy = 20;
}

/* --------------------------------------------------------- */

bool BigFloat::operator>(const BigFloat &big_float) const
{
    if (_int_part != big_float._int_part)
    {
        return _int_part > big_float._int_part;
    }
    BigInt temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits - _float_part.length() - _digits, 0);
        return temp > big_float._float_part;
    }
    else
    {
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() + _digits - big_float._float_part.length() - big_float._digits, 0);
        return _float_part > temp;
    }
}

bool BigFloat::operator<(const BigFloat &big_float) const
{
    if (_int_part != big_float._int_part)
    {
        return _int_part < big_float._int_part;
    }
    BigInt temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits - _float_part.length() - _digits, 0);
        return temp < big_float._float_part;
    }
    else
    {
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() + _digits - big_float._float_part.length() - big_float._digits, 0);
        return _float_part < temp;
    }
}

bool BigFloat::operator==(const BigFloat &big_float) const
{
    return _digits == big_float._digits && _int_part == big_float._int_part && _float_part == big_float._float_part;
}

bool BigFloat::operator!=(const BigFloat &big_float) const
{
    return _digits != big_float._digits || _int_part != big_float._int_part || _float_part != big_float._float_part;
}

bool BigFloat::operator>=(const BigFloat &big_float) const
{
    if (_int_part != big_float._int_part)
    {
        return _int_part > big_float._int_part;
    }
    BigInt temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits - _float_part.length() - _digits, 0);
        return temp >= big_float._float_part;
    }
    else
    {
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() + _digits - big_float._float_part.length() - big_float._digits, 0);
        return _float_part >= temp;
    }
}

bool BigFloat::operator<=(const BigFloat &big_float) const
{
    if (_int_part != big_float._int_part)
    {
        return _int_part < big_float._int_part;
    }
    BigInt temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits - _float_part.length() - _digits, 0);
        return temp <= big_float._float_part;
    }
    else
    {
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() + _digits - big_float._float_part.length() - big_float._digits, 0);
        return _float_part <= temp;
    }
}

/* --------------------------------------------------------- */

bool BigFloat::negative() const
{
    return _negative;
}

BigFloat BigFloat::round(const BigInt &big_int) const
{
    if (_digits + _float_part.length() <= big_int.to_sizet())
    {
        return *this;
    }
    BigFloat temp(*this);
    if (big_int.to_sizet() <= _digits)
    {
        temp._float_part._nums.clear();
        temp._float_part._nums.push_back(0);
        temp._digits = 0;
    }
    else
    {
        temp._float_part._nums.erase(temp._float_part._nums.begin() + (big_int.to_sizet() - _digits), temp._float_part._nums.end());
    }
    return temp;
}

BigFloat BigFloat::round(const size_t n) const
{
    if (_digits + _float_part.length() <= n)
    {
        return *this;
    }
    BigFloat temp(*this);
    if (n <= _digits)
    {
        temp._float_part._nums.clear();
        temp._float_part._nums.push_back(0);
        temp._digits = 0;
    }
    else
    {
        temp._float_part._nums.erase(temp._float_part._nums.begin() + (n - _digits), temp._float_part._nums.end());
    }
    return temp;
}

BigFloat &BigFloat::round(const BigInt &big_int, const bool inplace)
{
    if (_digits + _float_part.length() <= big_int.to_sizet())
    {
        return *this;
    }
    if (big_int.to_sizet() <= _digits)
    {
        _float_part._nums.clear();
        _float_part._nums.push_back(0);
        _digits = 0;
    }
    else
    {
        _float_part._nums.erase(_float_part._nums.begin() + (big_int.to_sizet() - _digits), _float_part._nums.end());
    }
    return *this;
}

BigFloat &BigFloat::round(const size_t n, const bool inplace)
{
    if (_digits + _float_part.length() <= n)
    {
        return *this;
    }
    if (n <= _digits)
    {
        _float_part._nums.clear();
        _float_part._nums.push_back(0);
        _digits = 0;
    }
    else
    {
        _float_part._nums.erase(_float_part._nums.begin() + (n - _digits), _float_part._nums.end());
    }
    return *this;
}

BigFloat BigFloat::abs() const
{
    if (_negative)
    {
        BigFloat temp;
        temp._int_part = _int_part.opposite();
        temp._float_part = _float_part.opposite();
        temp._digits = _digits;
        return temp;
    }
    else
    {
        return *this;
    }
}

BigFloat BigFloat::opposite() const
{
    return -*this;
}

BigFloat &BigFloat::opposite(const bool inplace)
{
    if (*this == BigFloat::ZERO)
    {
        return *this;
    }
    _negative = !_negative;
    _int_part.opposite(true);
    _float_part.opposite(true);
    return *this;
} 

BigFloat BigFloat::pow(const BigFloat &big_float) const
{
    if (big_float <= BigFloat::ZERO)
    {
        return BigFloat::ONE;
    }
    BigFloat temp(*this);
    BigInt i(1ll);
    while (i < big_float._int_part)
    {
        i *= BigInteger::TWO;
        if (i >= big_float._int_part)
        {
            if (i == big_float._int_part)
            {
                temp *= temp;
            }
            else
            {
                i /= BigInteger::TWO;
            }
            break;
        }
        temp *= temp;
    }
    while (i < big_float._int_part)
    {
        temp *= *this;
        ++i;
    }
    
    return temp;
}

BigFloat BigFloat::pow(const size_t n) const
{
    if (n == 0)
    {
        return BigFloat::ONE;
    }
    BigFloat temp(*this);
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

BigFloat BigFloat::rad(const BigFloat &big_flaot) const
{
    if (*this == BigFloat::ZERO || *this == BigFloat::ONE || *this == BigFloat("-1"))
    {
        return *this;
    }
    const BigFloat n(big_flaot.abs()), m = n - BigFloat::ONE, target = this->abs();
    BigFloat temp = target / n;
    temp.accuracy = accuracy;
    BigFloat end;
    if (accuracy > 0)
    {
        end._float_part._nums.back() = 1;
        end._digits = accuracy - 1;
    }
    else
    {
        end = BigFloat::ONE;
    }
    while ((temp.pow(n) - target).abs() >= end)
    {
        temp -= ((temp.pow(n) - target) / (n * temp.pow(m)));
    }
    if (temp._digits + temp._float_part.length() > accuracy)
    {
        if (temp._digits >= accuracy)
        {
            temp._float_part = BigInteger::ZERO;
            temp._digits = 0;
        }
        else
        {
            temp._float_part._nums.erase(temp._float_part._nums.begin() + (accuracy - _digits),
                temp._float_part._nums.end());
        }
    }
    if (_negative && n._int_part % BigInteger::TWO == BigInteger::ONE)
    {
        return -temp;
    }
    else
    {
        return temp;
    }
}

BigFloat BigFloat::rad(const size_t n) const
{
    if (*this == BigFloat::ZERO || *this == BigFloat::ONE || *this == BigFloat("-1"))
    {
        return *this;
    }
    const size_t m = n - 1;
    BigInt n_big_int(m);
    BigFloat temp = this->abs() / n_big_int;
    while ((temp.pow(n) - *this).abs() >= BigFloat("0.1").pow(accuracy))
    {
        temp -= ((temp.pow(n) - *this) / (temp.pow(m) * n_big_int));
    }
    if (temp._digits + temp._float_part.length() > accuracy)
    {
        if (temp._digits >= accuracy)
        {
            temp._float_part = BigInteger::ZERO;
            temp._digits = 0;
        }
        else
        {
            temp._float_part /= BigInt(10ll).pow(accuracy - _digits);
        }
    }
    if (_negative && n % 2 == 1)
    {
        return -temp;
    }
    else
    {
        return temp;
    }
}

BigFloat operator-(const BigFloat &big_float)
{
    BigFloat temp;
    temp._int_part = -big_float._int_part;
    temp._float_part = -big_float._float_part;
    temp._digits = big_float._digits;
    temp._negative = !big_float._negative;
    return temp;
}

/* --------------------------------------------------------- */

BigFloat BigFloat::operator+(const BigFloat &big_float) const
{
    BigFloat ans;
    BigInt num_a, num_b, temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        num_a = _int_part;
        num_a._nums.insert(num_a._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() - _float_part.length() + big_float._digits - _digits, 0);
        num_a += temp;

        num_b = big_float._int_part;
        num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        num_b += big_float._float_part;
        num_a += num_b;

        if (num_a.length() > big_float._float_part.length() + big_float._digits)
        {
            ans._int_part._negative = num_a._negative;
            ans._int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - big_float._float_part.length() - big_float._digits);
        }
        temp = ans._int_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        ans._float_part = num_a - temp;
        ans._digits = big_float._float_part.length() + big_float._digits - ans._float_part.length();
    }
    else
    {
        num_a = _int_part;
        num_a._nums.insert(num_a._nums.end(), _float_part.length() + _digits, 0);
        num_a += _float_part;

        num_b = big_float._int_part;
        num_b._nums.insert(num_b._nums.end(), _float_part.length() + _digits, 0);
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() - big_float._float_part.length() + _digits - big_float._digits, 0);
        num_b += temp;
        num_a += num_b;

        if (num_a.length() > _float_part.length() + _digits)
        {
            ans._int_part._negative = num_a._negative;
            ans._int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - _float_part.length() - _digits);
        }
        temp = ans._int_part;
        temp._nums.insert(temp._nums.end(), _float_part.length() + _digits, 0);
        ans._float_part = num_a - temp;
        ans._digits = _float_part.length() + _digits - ans._float_part.length();
    }
    ans._negative = num_a._negative;
    while (!ans._float_part._nums.empty() && ans._float_part._nums.back() == 0)
    {
        ans._float_part._nums.pop_back();
    }
    return ans;
}

BigFloat BigFloat::operator-(const BigFloat &big_float) const
{
    return *this + (-big_float);
}

BigFloat BigFloat::operator*(const BigFloat &big_float) const
{
    if (*this == BigFloat::ZERO || big_float == BigFloat::ZERO)
    {
        return BigFloat::ZERO;
    }
    BigFloat ans;
    BigInt num_a, num_b;
    const BigInt ten(10ll);
    num_a = _int_part;
    num_a._nums.insert(num_a._nums.end(), _float_part.length() + _digits, 0);
    num_a += _float_part;
    num_b = big_float._int_part;
    num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
    num_b += big_float._float_part;
    num_a *= num_b;

    ans._int_part._negative = num_a._negative;
    ans._int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - (big_float._float_part.length() + big_float._digits + _float_part.length() + _digits));
    num_b = ans._int_part;
    num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits + _float_part.length() + _digits, 0);
    ans._float_part = num_a - num_b;
    ans._digits = ans._float_part == BigInteger::ZERO ? 0 : big_float._float_part.length() + big_float._digits + _float_part.length() + _digits - ans._float_part.length();
    ans._negative = num_a._negative;
    while (!ans._float_part._nums.empty() && ans._float_part._nums.back() == 0)
    {
        ans._float_part._nums.pop_back();
    }
    return ans;
}

BigFloat BigFloat::operator/(const BigFloat &big_float) const
{
    if (*this == BigFloat::ZERO)
    {
        return *this;
    }
    else if (this->abs() == big_float.abs())
    {
        return _negative == big_float._negative ? BigFloat::ONE : BigFloat("-1");
    }
    const size_t acc = std::max(accuracy, big_float.accuracy),
                len_of_float_part = 2 * acc + _float_part.length() + _digits - big_float._float_part.length() - big_float._digits;
    BigFloat ans;
    BigInt num_a, num_b;
    num_a = _int_part;
    num_a._nums.insert(num_a._nums.end(), _float_part.length() + _digits, 0);
    num_a += _float_part;

    num_b = big_float._int_part;
    num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
    num_b += big_float._float_part;
    num_a._nums.insert(num_a._nums.end(), acc + acc, 0);
    num_a /= num_b;

    ans.accuracy = acc;
    ans._int_part._negative = num_a._negative;
    if (num_a.length() > len_of_float_part)
    {
        ans._int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - len_of_float_part);
    }
    if (ans._int_part._nums.empty())
    {
        ans._int_part._nums.push_back(0);
    }
    num_b = ans._int_part;
    num_b._nums.insert(num_b._nums.end(), len_of_float_part, 0);
    ans._float_part = num_a - num_b;
    ans._negative = num_a._negative;
    ans._digits = (ans._float_part == BigInteger::ZERO ? 0 : len_of_float_part - ans._float_part.length());
    while (!ans._float_part._nums.empty() && ans._float_part._nums.back() == 0)
    {
        ans._float_part._nums.pop_back();
    }

    if (ans._digits + ans._float_part.length() > ans.accuracy)
    {
        if (ans._digits >= ans.accuracy)
        {
            ans._float_part = BigInteger::ZERO;
            ans._digits = 0;
        }
        else
        {
            if (ans._float_part.length() > ans._digits + ans._float_part.length() - ans.accuracy)
            {
                ans._float_part._nums.erase(ans._float_part._nums.end() - (ans._digits + ans._float_part.length() - ans.accuracy), ans._float_part._nums.end());
            }
            else
            {
                ans._float_part._nums.clear();
                ans._float_part._nums.push_back(0);
            }
        }
    }
    return ans;
}

BigFloat &BigFloat::operator=(const BigFloat &big_float)
{
    _negative = big_float._negative;
    _int_part = big_float._int_part;
    _float_part = big_float._float_part;
    _digits = big_float._digits;
    accuracy = std::max(accuracy, big_float.accuracy);
    return *this;
}

BigFloat &BigFloat::operator=(const BigInt &big_int)
{
    _negative = big_int.negative();
    _int_part = big_int;
    _float_part = BigInteger::ZERO;
    _digits = 0;
    return *this;
}

/* --------------------------------------------------------- */

void BigFloat::operator+=(const BigFloat &big_float)
{
    BigInt num_a, num_b, temp;
    if (_float_part.length() + _digits <= big_float._float_part.length() + big_float._digits)
    {
        num_a = _int_part;
        num_a._nums.insert(num_a._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        temp = _float_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits - _float_part.length() - _digits, 0);
        num_a += temp;

        num_b = big_float._int_part;
        num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        num_b += big_float._float_part;
        num_a += num_b;

        _int_part._negative = num_a._negative;
        _int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - (big_float._float_part.length() + big_float._digits));
        temp = _int_part;
        temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits, 0);
        _float_part = num_a - temp;
        _digits =  big_float._float_part.length() + big_float._digits - _float_part.length();
    }
    else
    {
        const size_t len_of_float_part = _float_part.length();
        num_a = _int_part;
        num_a._nums.insert(num_a._nums.end(), len_of_float_part + _digits, 0);
        num_a += _float_part ;

        num_b = big_float._int_part;
        num_b._nums.insert(num_b._nums.end(), len_of_float_part + _digits, 0);
        temp = big_float._float_part;
        temp._nums.insert(temp._nums.end(), len_of_float_part - big_float._float_part.length() + _digits - big_float._digits, 0);
        num_a += num_b;

        _int_part = num_a;
        _int_part._nums.insert(_int_part._nums.end(), len_of_float_part + _digits, 0);
        temp = _int_part;
        temp._nums.insert(temp._nums.end(), len_of_float_part + _digits, 0);
        _float_part = num_a - temp;
        _digits =  len_of_float_part + _digits - _float_part.length();
    }
    _negative = num_a.negative();
    while (!_float_part._nums.empty() && _float_part._nums.back() == 0)
    {
        _float_part._nums.pop_back();
    }
}

void BigFloat::operator-=(const BigFloat &big_float)
{
    *this += (-big_float);
}

void BigFloat::operator*=(const BigFloat &big_float)
{
    if (*this == BigFloat::ZERO || big_float == BigFloat::ZERO)
    {
        *this = BigFloat::ZERO;
    }
    BigInt num_a, num_b, temp;
    const BigInt ten(10ll);
    const size_t len_of_float_part = _float_part.length();
    num_a = _int_part;
    num_a._nums.insert(num_a._nums.end(), len_of_float_part + _digits, 0);
    num_a += _float_part;

    num_b = big_float._int_part;
    num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
    num_b += big_float._float_part;
    num_a *= num_b;

    _int_part._negative = num_a._negative;
    _int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - (big_float._float_part.length() + big_float._digits + len_of_float_part + _digits));
    temp = _int_part;
    temp._nums.insert(temp._nums.end(), big_float._float_part.length() + big_float._digits + len_of_float_part + _digits, 0);
    _float_part = num_a - temp;
    _digits =  big_float._float_part.length() + big_float._digits + len_of_float_part + _digits - _float_part.length();
    _negative = num_a.negative();
    while (!_float_part._nums.empty() && _float_part._nums.back() == 0)
    {
        _float_part._nums.pop_back();
    }
}

void BigFloat::operator/=(const BigFloat &big_float)
{
    if (*this == BigFloat::ZERO)
    {
        return;
    }
    else if (this->abs() == big_float.abs())
    {
        *this = _negative == big_float._negative ? BigFloat::ONE : BigFloat("-1");
    }
    const size_t acc = std::max(accuracy, big_float.accuracy),
                len_of_float_part = 2 * acc + _float_part.length() + _digits - big_float._float_part.length() - big_float._digits;
    BigInt num_a, num_b;
    const BigInt ten(10ll);
    num_a = _int_part;
    num_a._nums.insert(num_a._nums.end(), _float_part.length() + _digits, 0);
    num_a += _float_part;

    num_b = big_float._int_part;
    num_b._nums.insert(num_b._nums.end(), big_float._float_part.length() + big_float._digits, 0);
    num_b += big_float._float_part;
    num_a._nums.insert(num_a._nums.end(), acc + acc, 0);
    num_a /= num_b;

    accuracy = acc;
    _int_part._negative = num_a._negative;
    if (num_a.length() > len_of_float_part)
    {
        _int_part._nums.assign(num_a._nums.begin(), num_a._nums.end() - len_of_float_part);
    }
    if (_int_part._nums.empty())
    {
        _int_part._nums.push_back(0);
    }
    num_b = _int_part;
    num_b._nums.insert(num_b._nums.end(), len_of_float_part, 0);
    _float_part = num_a - num_b;
    _negative = num_a._negative;
    _digits = _float_part == BigInteger::ZERO ? 0 : len_of_float_part - _float_part.length();

    while (!_float_part._nums.empty() && _float_part._nums.back() == 0)
    {
        _float_part._nums.pop_back();
    }
    if (_digits + _float_part.length() > accuracy)
    {
        if (_digits >= accuracy)
        {
            _float_part = BigInteger::ZERO;
            _digits = 0;
        }
        else
        {
            if (_float_part.length() > _digits + _float_part.length() - accuracy)
            {
                _float_part._nums.erase(_float_part._nums.end() - (_digits + _float_part.length() - accuracy), _float_part._nums.end());
            }
            else
            {
                _float_part._nums.clear();
                _float_part._nums.push_back(0);
            }
        }
    }
}

/* --------------------------------------------------------- */

BigFloat &BigFloat::operator++()
{
    if (_negative && _float_part != BigInteger::ZERO)
    {
        *this += BigFloat::ONE;
    }
    else
    {
        ++_int_part;
        _negative = _int_part.negative();
    }
    return *this;
}

BigFloat BigFloat::operator++(const int)
{
    BigFloat temp(*this);
    if (_negative && _float_part != BigInteger::ZERO)
    {
        *this += BigFloat::ONE;
    }
    else
    {
        ++_int_part;
        _negative = _int_part.negative();
    }
    return temp;
}

BigFloat &BigFloat::operator--()
{
    if (!_negative && _float_part != BigInteger::ZERO)
    {
        *this += BigFloat("-1");
    }
    else
    {
        --_int_part;
        _negative = _int_part.negative();
    }
    return *this;
}

BigFloat BigFloat::operator--(const int)
{
    BigFloat temp(*this);
    if (!_negative && _float_part != BigInteger::ZERO)
    {
        *this += BigFloat("-1");
    }
    else
    {
        --_int_part;
        _negative = _int_part.negative();
    }
    return temp;
}

/* --------------------------------------------------------- */

std::string BigFloat::to_str() const
{
    if (_negative && _int_part == BigInteger::ZERO)
    {
        return '-' + _int_part.to_str().substr(0, _int_part.to_str().length()-1) + '.' + _float_part.abs().to_str();
    }
    else
    {
        return _int_part.to_str().substr(0, _int_part.to_str().length()-1) + '.' + _float_part.abs().to_str();
    }
}

BigInt BigFloat::to_big_int() const
{
    return _int_part;
}

std::ostream &operator<<(std::ostream &o, const BigFloat &big_float)
{
    if (big_float._negative && big_float._int_part == BigInteger::ZERO)
    {
        o << '-';
    }
    o << big_float._int_part;
    if (big_float._float_part.length() == 0 || big_float._float_part == BigInteger::ZERO)
    {
        return o;
    }
    o << '.';
    for (size_t i = 0; i < big_float._digits; ++i)
    {
        o << '0';
    }
    o << big_float._float_part.abs();
    return o;
}

/* --------------------------------------------------------- */

size_t BigFloat::length() const
{
    return _int_part.length() + _float_part.length() + _digits;
}

size_t BigFloat::length_of_int_part() const
{
    return _int_part.length();
}

size_t BigFloat::length_of_float_part() const
{
    return _float_part.length();
}

/* --------------------------------------------------------- */

std::vector<char>::const_iterator BigFloat::ibegin() const
{
    return _int_part.begin();
}

std::vector<char>::const_iterator BigFloat::iend() const
{
    return _int_part.end();
}

std::vector<char>::const_reverse_iterator BigFloat::irbegin() const
{
    return _int_part.rbegin();
}

std::vector<char>::const_reverse_iterator BigFloat::irend() const
{
    return _int_part.rend();
}

std::vector<char>::const_iterator BigFloat::fbegin() const
{
    return _float_part.begin();
}

std::vector<char>::const_iterator BigFloat::fend() const
{
    return _float_part.end();
}

std::vector<char>::const_reverse_iterator BigFloat::frbegin() const
{
    return _float_part.rbegin();
}

std::vector<char>::const_reverse_iterator BigFloat::frend() const
{
    return _float_part.rend();
}

char BigFloat::operator[](const long long i) const
{
    if (i >= 0)
    {
        return _int_part[i];
    }
    else
    {
        return _float_part[_float_part.length() + _digits + i];
    }  
}

char& BigFloat::operator[](const long long i)
{
    if (i >= 0)
    {
        return _int_part[i];
    }
    else
    {
        return _float_part[_float_part.length() + _digits + i];
    }  
}
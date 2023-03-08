#include "BigMath.hpp"

BigFloat sin(const BigFloat& big_float, const size_t& n)
{
    BigFloat temp(big_float);
    if (big_float.abs() > Constant::Duo_Pi_100)
    {
        temp -= Constant::Duo_Pi_100 * (temp / Constant::Duo_Pi_100).round(0, true);
        temp.round(big_float.accuracy, true);
        temp.accuracy = big_float.accuracy;
    }
    temp.accuracy = std::max(n*2+n/2, big_float.accuracy);
    const BigFloat square_of_big_float = temp * temp;
    BigFloat factorial_of_count('1'), count('1');
    bool flag = true;
    BigFloat ans = temp; 
    for (size_t i = 0; i < 10; ++i)
    {
        temp *= square_of_big_float;
        factorial_of_count *= ++count;
        factorial_of_count *= ++count;
        if (flag)
        {
            ans -= ( temp / factorial_of_count);
        }
        else
        {
            ans += ( temp / factorial_of_count);
        }
        flag = !flag;
    }
    for (size_t i = 10; i < n; ++i)
    {
        temp *= square_of_big_float;
        factorial_of_count *= ++count;
        factorial_of_count *= ++count;
        if (flag)
        {
            ans -= ( temp / factorial_of_count);
        }
        else
        {
            ans += ( temp / factorial_of_count);
        }
        flag = !flag;
    }
    return ans;
}

BigFloat cos(const BigFloat& big_float, const size_t& n)
{
    BigFloat copy_of_big_float(big_float);
    if (big_float.abs() > Constant::Duo_Pi_100)
    {
        copy_of_big_float -= Constant::Duo_Pi_100 * (copy_of_big_float / Constant::Duo_Pi_100).round(0, true);
        copy_of_big_float.round(big_float.accuracy, true);
        copy_of_big_float.accuracy = big_float.accuracy;
    }
    const BigFloat square_of_big_float = copy_of_big_float * copy_of_big_float;
    BigFloat temp('1'), factorial_of_count('1'), count('0');
    temp.accuracy = std::max(n*2+n/2, big_float.accuracy);
    bool flag = true;
    BigFloat ans = temp; 
    for (size_t i = 0; i < 10; ++i)
    {
        temp *= square_of_big_float;
        factorial_of_count *= ++count;
        factorial_of_count *= ++count;
        if (flag)
        {
            ans -= ( temp / factorial_of_count);
        }
        else
        {
            ans += ( temp / factorial_of_count);
        }
        flag = !flag;
    }
    for (size_t i = 10; i < n; ++i)
    {
        temp *= square_of_big_float;
        factorial_of_count *= ++count;
        factorial_of_count *= ++count;
        if (flag)
        {
            ans -= ( temp / factorial_of_count);
        }
        else
        {
            ans += ( temp / factorial_of_count);
        }
        flag = !flag;
    }
    return ans;
}

BigFloat tan(const BigFloat& big_float, const size_t& n)
{
    BigFloat temp(big_float);
    if (big_float.abs() > Constant::Duo_Pi_100)
    {
        temp -= Constant::Duo_Pi_100 * (temp / Constant::Duo_Pi_100).round(0, true);
    }
    temp.accuracy = std::max(n*2+n/2, big_float.accuracy);
    temp.round(temp.accuracy, true);
    BigFloat value_of_sin, value_of_cos;
    std::thread sin_thread([&]{value_of_sin = sin(temp, n);});
    std::thread cos_thread([&]{value_of_cos = cos(temp, n);});
    sin_thread.join();
    cos_thread.join();
    return value_of_sin / value_of_cos;
}

/* --------------------------------------------------------- */

BigInt factorial(const BigInt& big_int)
{
    if (big_int == BigInt('0'))
    {
        return BigInt('1');
    }
    BigInt ans(big_int.abs()), count(big_int.abs());
    const BigInt two('2');
    while (count > two)
    {
        ans *= --count;
    }
    return ans;
}

BigInt factorial(const size_t& n)
{
    if (n == 0)
    {
        return BigInt('1');
    }
    BigInt ans(n), count(n);
    for (size_t i = 2; i < n; ++i)
    {
        ans *= --count;
    }
    return ans;
}

BigIntF factorial(const BigIntF& big_int)
{
    if (big_int == BigIntF('0'))
    {
        return BigIntF('1');
    }
    BigIntF ans(big_int.abs()), count(big_int.abs());
    const BigIntF two('2');
    while (count > two)
    {
        ans *= --count;
    }
    return ans;
}

/* --------------------------------------------------------- */

BigFloat sqrt(const BigInt& big_int, const size_t& n)
{
    BigFloat output;
    output.accuracy = std::max(output.accuracy, n);
    BigInt ans, num_a, num_b;
    const BigInt twenty("20"), zero('0');
    std::list<char>::const_iterator it = big_int.begin();
    const size_t end = big_int.length();
    if (end % 2 == 0)
    {
        const char& f = *it;
        util::append(ans, char(std::sqrt(f * 10 + *++it)));
        util::append(num_a, f * 10 + *it++ - *ans.begin() * *ans.begin());
    }
    else
    {
        util::append(ans, char(std::sqrt(*it)));
        util::append(num_a, *it++ - *ans.begin() * *ans.begin());
    }
    for (size_t i = 2 - end % 2; i < end; i += 2)
    {
        util::append(num_a, *it++);
        util::append(num_a, *it++);
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    util::copy_to_int_part(output, ans);
    if (num_a == zero)
    {
        return output;
    }
    for (size_t i = 0; i < n; ++i)
    {
        util::append(num_a, 0);
        util::append(num_a, 0);
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    ans %= BigInt("10").pow(ans.length() - output.length_of_int_part());
    util::copy_to_float_part(output, ans);
    return output;
}

BigFloat sqrt(const BigFloat& big_float, const size_t& n)
{
    BigFloat output;
    output.accuracy = std::max(output.accuracy, n);
    BigInt ans, num_a, num_b;
    const BigInt twenty("20"), zero('0');
    std::list<char>::const_iterator it = big_float.ibegin();
    size_t end = big_float.length_of_int_part();
    if (end % 2 == 0)
    {
        const char& f = *it;
        util::append(ans, char(std::sqrt(f * 10 + *++it)));
        util::append(num_a, f * 10 + *it++ - *ans.begin() * *ans.begin());
    }
    else
    {
        util::append(ans, char(std::sqrt(*it)));
        util::append(num_a, *it++ - *ans.begin() * *ans.begin());
    }
    for (size_t i = 2 - end % 2; i < end; i += 2)
    {
        util::append(num_a, *it++);
        util::append(num_a, *it++);
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    util::copy_to_int_part(output, ans);
    if (num_a == zero && *big_float.fbegin() == 0)
    {
        return output;
    }
    it = big_float.fbegin();
    end = big_float.length_of_float_part();
    const size_t digits = big_float.length() - big_float.length_of_int_part() - big_float.length_of_float_part();
    for (size_t i = 0; i < digits; i += 2)
    {
        util::append(num_a, 0);
        if (i + 2 <= digits)
        {
            util::append(num_a, 0);
        }
        else
        {
            util::append(num_a, *it++);
        }
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    const std::list<char>::const_iterator end_of_float_part = big_float.fend();
    for (size_t i = digits % 2; i < end; i += 2)
    {
        util::append(num_a, *it++);
        if (it != end_of_float_part)
        {
            util::append(num_a, *it++);
        }
        else
        {
            util::append(num_a, 0);
        }
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    if (ans.length() - output.length_of_int_part() >= n)
    {
        util::copy_to_float_part(output, ans);
        return output;
    }
    end = n + output.length_of_int_part() - ans.length() ;
    for (size_t i = 0; i < end; ++i)
    {
        util::append(num_a, 0);
        util::append(num_a, 0);
        num_b = zero;
        while ((ans * twenty + num_b) * num_b <= num_a)
        {
            ++num_b;
        }
        if (*num_b.begin() == 0)
        {
            util::append(ans, 0);
        }
        else
        {
            --num_b;
            num_a -= (ans * twenty + num_b) * num_b;
            util::append(ans, *num_b.begin());
        }
    }
    ans %= BigInt("10").pow(ans.length() - output.length_of_int_part());
    util::copy_to_float_part(output, ans);
    return output;
}

BigFloat pi(const size_t& n)
{
    if (n <= 100)
    {
       return n > 20 ? Constant::Pi_100.round(n) : Constant::Pi;
    }

    const BigFloat a = sqrt(BigInt('2'), n) * BigFloat('2') / BigFloat("9801");
    const BigInt four('4'), b("1103"), c("26390"), d("396");

    BigFloat temp('0'), temp_a, temp_b;
    temp.accuracy = std::max(temp.accuracy, n);
    temp_a.accuracy = temp.accuracy, temp_b.accuracy = temp.accuracy;
    const BigInt times(n/8+1);
    for (BigInt k('0'); k < times; ++k)
    {
        temp_a = factorial(four * k) * (b + c * k);
        temp_b = factorial(k).pow(4) * d.pow(four * k);
        temp += temp_a / temp_b;
    }
    temp *= a;
    temp.accuracy = temp.length_of_float_part();
    BigFloat ans((BigFloat('1') / temp).round(n > 20 ? n : 20, true));
    ans.accuracy = n > 20 ? n : 20;
    return ans;
}

BigFloat e(const size_t& n)
{
    if (n <= 100)
    {
        return n > 20 ? Constant::E_100.round(n) : Constant::E;
    }
    BigFloat temp('2'), temp_a('1'), temp_b('1');
    temp.accuracy = n > 20 ? n : 20;
    for (size_t i = 0; i < n; ++i)
    {
        temp_a /= ++temp_b;
        temp += temp_a;
    }
    return temp;
}

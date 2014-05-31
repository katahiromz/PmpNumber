/////////////////////////////////////////////////////////////////////////////
// PmpNumber --- polymorphic, multiprecision number class
// See file "ReadMe.txt" and "License.txt".
/////////////////////////////////////////////////////////////////////////////

#include "PmpNumber.hpp"

PmpNumber& PmpNumber::operator+=(const PmpNumber& num)
{
    pmp_integer_type    i;
    pmp_floating_type   f;
    switch(m_inner->m_type)
    {
    case Inner::INTEGER:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            i = *m_inner->m_integer;
            i += *num.m_inner->m_integer;
            assign(i);
            break;

        case Inner::FLOATING:
            f = pmp_floating_type(*m_inner->m_integer);
            f += *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    case Inner::FLOATING:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = *m_inner->m_floating;
            f += static_cast<pmp_floating_type>(*num.m_inner->m_integer);
            assign(f);
            break;

        case Inner::FLOATING:
            f = *m_inner->m_floating;
            f += *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;
    }
    return *this;
}

PmpNumber& PmpNumber::operator-=(const PmpNumber& num)
{
    pmp_integer_type    i;
    pmp_floating_type   f;
    switch(m_inner->m_type)
    {
    case Inner::INTEGER:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            i = *m_inner->m_integer;
            i -= *num.m_inner->m_integer;
            assign(i);
            break;

        case Inner::FLOATING:
            f = pmp_floating_type(*m_inner->m_integer);
            f -= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    case Inner::FLOATING:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = *m_inner->m_floating;
            f -= static_cast<pmp_floating_type>(*num.m_inner->m_integer);
            assign(f);
            break;

        case Inner::FLOATING:
            f = *m_inner->m_floating;
            f -= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;
    }
    return *this;
}

PmpNumber& PmpNumber::operator*=(const PmpNumber& num)
{
    pmp_integer_type    i;
    pmp_floating_type   f;
    switch(m_inner->m_type)
    {
    case Inner::INTEGER:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            i = *m_inner->m_integer;
            i *= *num.m_inner->m_integer;
            assign(i);
            break;

        case Inner::FLOATING:
            f = pmp_floating_type(*m_inner->m_integer);
            f *= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    case Inner::FLOATING:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = *m_inner->m_floating;
            f *= static_cast<pmp_floating_type>(*num.m_inner->m_integer);
            assign(f);
            break;

        case Inner::FLOATING:
            f = *m_inner->m_floating;
            f *= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;
    }
    return *this;
}

PmpNumber& PmpNumber::operator/=(const PmpNumber& num)
{
    pmp_integer_type    i;
    pmp_floating_type   f;
    switch(m_inner->m_type)
    {
    case Inner::INTEGER:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            if (b_mp::gcd(*m_inner->m_integer, *num.m_inner->m_integer) == 1)
            {
                f = static_cast<pmp_floating_type>(*m_inner->m_integer);
                f /= static_cast<pmp_floating_type>(*num.m_inner->m_integer);
                assign(f);
            }
            else
            {
                i = *m_inner->m_integer;
                i /= *num.m_inner->m_integer;
                assign(i);
            }
            break;

        case Inner::FLOATING:
            f = pmp_floating_type(*m_inner->m_integer);
            f /= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    case Inner::FLOATING:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = static_cast<pmp_floating_type>(*m_inner->m_integer);
            f /= static_cast<pmp_floating_type>(*num.m_inner->m_integer);
            assign(f);
            break;

        case Inner::FLOATING:
            f = *m_inner->m_floating;
            f /= *num.m_inner->m_floating;
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    default:
        assert(0);
        break;
    }
    return *this;
}

PmpNumber& PmpNumber::operator%=(const PmpNumber& num)
{
    pmp_integer_type    i;
    pmp_floating_type   f;
    switch(m_inner->m_type)
    {
    case Inner::INTEGER:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            i = *m_inner->m_integer;
            i %= *num.m_inner->m_integer;
            assign(i);
            break;

        case Inner::FLOATING:
            f = pmp_floating_type(*m_inner->m_integer);
            f = b_mp::fmod(f, *num.m_inner->m_floating);
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    case Inner::FLOATING:
        switch(num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = *m_inner->m_floating;
            f = b_mp::fmod(f, static_cast<pmp_floating_type>(*num.m_inner->m_integer));
            assign(f);
            break;

        case Inner::FLOATING:
            f = *m_inner->m_floating;
            f = b_mp::fmod(f, *num.m_inner->m_floating);
            assign(f);
            break;

        default:
            assert(0);
            break;
        }
        break;

    default:
        assert(0);
        break;
    }
    return *this;
}

bool PmpNumber::is_zero() const
{
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        return m_inner->m_integer->is_zero();

    case Inner::FLOATING:
        return m_inner->m_floating->is_zero();

    default:
        assert(0);
        return false;
    }
}

std::string PmpNumber::str() const
{
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        return m_inner->m_integer->str();

    case Inner::FLOATING:
        return m_inner->m_floating->str();

    default:
        assert(0);
        return "";
    }
}

pmp_integer_type PmpNumber::to_i() const
{
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        return *m_inner->m_integer;

    case Inner::FLOATING:
        return pmp_integer_type(m_inner->m_floating->str());

    default:
        assert(0);
        return 0;
    }
}

pmp_floating_type PmpNumber::to_f() const
{
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        return pmp_floating_type(*m_inner->m_integer);

    case Inner::FLOATING:
        return *m_inner->m_floating;

    default:
        assert(0);
        return 0;
    }
}

int PmpNumber::compare(const PmpNumber& num) const
{
    pmp_floating_type f;
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        switch (num.m_inner->m_type)
        {
        case Inner::INTEGER:
            return m_inner->m_integer->compare(*num.m_inner->m_integer);

        case Inner::FLOATING:
            f = static_cast<pmp_floating_type>(*m_inner->m_integer);
            return f.compare(*num.m_inner->m_floating);

        default:
            assert(0);
            return 0;
        }

    case Inner::FLOATING:
        switch (num.m_inner->m_type)
        {
        case Inner::INTEGER:
            f = static_cast<pmp_floating_type>(*num.m_inner->m_integer);
            return m_inner->m_floating->compare(f);

        case Inner::FLOATING:
            return m_inner->m_floating->compare(*num.m_inner->m_floating);

        default:
            assert(0);
            return 0;
        }

    default:
        assert(0);
        return 0;
    }
}

void PmpNumber::trim()
{
    pmp_integer_type    i;
    pmp_floating_type   f;

    switch (m_inner->m_type)
    {
    case PmpNumber::Inner::INTEGER:
        break;

    case PmpNumber::Inner::FLOATING:
        i = pmp_integer_type(m_inner->m_floating->str());
        f = static_cast<pmp_floating_type>(i);
        if (f == *m_inner->m_floating)
            *this = i;
        break;

    default:
        assert(0);
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Non-member functions

PmpNumber operator-(const PmpNumber& num1)
{
    switch (num1.m_inner->m_type)
    {
    case PmpNumber::Inner::INTEGER:
        return PmpNumber(static_cast<pmp_integer_type>(-(*num1.m_inner->m_integer)));

    case PmpNumber::Inner::FLOATING:
        return PmpNumber(static_cast<pmp_floating_type>(-(*num1.m_inner->m_floating)));

    default:
        assert(0);
        return 0;
    }
}

template <class CharT>
std::basic_ostream<CharT>&
operator<<(std::basic_ostream<CharT>& o, const PmpNumber& num)
{
    switch (num.m_inner->m_type)
    {
    case PmpNumber::Inner::INTEGER:
        o << num.m_inner->m_integer->str();
        break;

    case PmpNumber::Inner::FLOATING:
        o << num.m_inner->m_floating->str();
        break;

    default:
        assert(0);
        break;
    }
    return o;
}


namespace std
{
    PmpNumber floor(const PmpNumber& num1)
    {
        switch (num1.m_inner->m_type)
        {
        case PmpNumber::Inner::INTEGER:
            return num1;

        case PmpNumber::Inner::FLOATING:
            return PmpNumber(std::floor(*num1.m_inner->m_floating));

        default:
            assert(0);
            return 0;
        }
    }

    PmpNumber ceil(const PmpNumber& num1)
    {
        switch (num1.m_inner->m_type)
        {
        case PmpNumber::Inner::INTEGER:
            return num1;

        case PmpNumber::Inner::FLOATING:
            return PmpNumber(std::ceil(*num1.m_inner->m_floating));

        default:
            assert(0);
            return 0;
        }
    }
} // namespace std

/////////////////////////////////////////////////////////////////////////////
// unit test and example

#ifdef UNITTEST
    int main(void)
    {
        PmpNumber n1(100);
        PmpNumber n2(200.0);
        PmpNumber n3;

        n3 = n1;
        n3 += n2;
        assert(n3 == 300.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 -= n2;
        assert(n3 == -100.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 *= n2;
        assert(n3 == 20000.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 /= n2;
        assert(n3 == 0.5);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 %= n2;
        assert(n3 == 100.0);
        std::cout << n3 << std::endl;

        n3 = n1;
        n3 += 20;
        assert(n3 == 120);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 -= 20;
        assert(n3 == 80);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 *= 20;
        assert(n3 == 2000);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 /= 20;
        assert(n3 == 5);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 %= 20;
        assert(n3 == 0);
        std::cout << n3 << std::endl;

        n3 = n1;
        n3 += 20.0;
        assert(n3 == 120.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 -= 20.0;
        assert(n3 == 80.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 *= 20.0;
        assert(n3 == 2000.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 /= 20.0;
        assert(n3 == 5.0);
        std::cout << n3 << std::endl;
        n3 = n1;
        n3 %= 20.0;
        assert(n3 == 0.0);
        std::cout << n3 << std::endl;

        n3 = n1 + n2;
        assert(n3 == 300.0);
        std::cout << n3 << std::endl;
        n3 = n1 - n2;
        assert(n3 == -100.0);
        std::cout << n3 << std::endl;
        n3 = n1 * n2;
        assert(n3 == 20000.0);
        std::cout << n3 << std::endl;
        n3 = n1 / n2;
        assert(n3 == 0.5);
        std::cout << n3 << std::endl;
        n3 = n1 % n2;
        assert(n3 == 100.0);
        std::cout << n3 << std::endl;

        n3 = n1 + 20;
        assert(n3 == 120);
        std::cout << n3 << std::endl;
        n3 = n1 - 20;
        assert(n3 == 80);
        std::cout << n3 << std::endl;
        n3 = n1 * 20;
        assert(n3 == 2000);
        std::cout << n3 << std::endl;
        n3 = n1 / 20;
        assert(n3 == 5);
        std::cout << n3 << std::endl;
        n3 = n1 % 20;
        assert(n3 == 0);
        std::cout << n3 << std::endl;

        n3 = n1 + 20.0;
        assert(n3 == 120.0);
        std::cout << n3 << std::endl;
        n3 = n1 - 20.0;
        assert(n3 == 80.0);
        std::cout << n3 << std::endl;
        n3 = n1 * 20.0;
        assert(n3 == 2000.0);
        std::cout << n3 << std::endl;
        n3 = n1 / 20.0;
        assert(n3 == 5.0);
        std::cout << n3 << std::endl;
        n3 = n1 % 20.0;
        assert(n3 == 0.0);
        std::cout << n3 << std::endl;

        n3 = std::sin(n1);
        std::cout << n3 << std::endl;
        n3 = std::sin(n2);
        std::cout << n3 << std::endl;
        n3 = std::cos(n1);
        std::cout << n3 << std::endl;
        n3 = std::cos(n2);
        std::cout << n3 << std::endl;
        n3 = std::tan(n1);
        std::cout << n3 << std::endl;
        n3 = std::tan(n2);
        std::cout << n3 << std::endl;

        PmpNumber n4(1.2);
        std::cout << n4.convert_to<int>() << std::endl;
        std::cout << n4.convert_to<__int64>() << std::endl;
        std::cout << n4.convert_to<float>() << std::endl;
        std::cout << n4.convert_to<double>() << std::endl;
        std::cout << n4.convert_to<long double>() << std::endl;

        return 0;
    }
#endif  // def UNITTEST

/////////////////////////////////////////////////////////////////////////////

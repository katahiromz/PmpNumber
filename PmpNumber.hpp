/////////////////////////////////////////////////////////////////////////////
// PmpNumber --- polymorphic, multiprecision number class
// See file "ReadMe.txt" and "License.txt".
/////////////////////////////////////////////////////////////////////////////

#ifndef PMPNUMBER_HPP_
#define PMPNUMBER_HPP_

#ifndef __cplusplus
    #error You must use C++ compiler to compile this source.  You lose!
#endif

#include <algorithm>    // for std::swap
#include <iostream>     // for std::basic_ostream
#include <string>       // for std::string
#include <cmath>        // for math functions
#include <cassert>      // for assert

/////////////////////////////////////////////////////////////////////////////
// smart pointers

#ifndef shared_ptr
    #if (__cplusplus >= 201103L)
        #include <memory>
        using std::shared_ptr;
        using std::make_shared;
    #else
        // boost::shared_ptr
        #include <Boost/shared_ptr.hpp>
        using boost::shared_ptr;

        // boost::make_shared
        #include <boost/make_shared.hpp>
        using boost::make_shared;
    #endif
#endif  // ndef shared_ptr

/////////////////////////////////////////////////////////////////////////////
// Boost.Multiprecision

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#define b_mp        boost::multiprecision

typedef b_mp::cpp_int               pmp_integer_type;
typedef b_mp::cpp_dec_float_50      pmp_floating_type;
//typedef b_mp::cpp_dec_float_100     pmp_floating_type;

/////////////////////////////////////////////////////////////////////////////

class PmpNumber;

namespace std
{
    PmpNumber abs(const PmpNumber& num1);
    PmpNumber fabs(const PmpNumber& num1);
    PmpNumber sqrt(const PmpNumber& num1);
    PmpNumber floor(const PmpNumber& num1);
    PmpNumber ceil(const PmpNumber& num1);
    PmpNumber exp(const PmpNumber& num1);
    PmpNumber log(const PmpNumber& num1);
    PmpNumber log10(const PmpNumber& num1);
    PmpNumber cos(const PmpNumber& num1);
    PmpNumber sin(const PmpNumber& num1);
    PmpNumber tan(const PmpNumber& num1);
    PmpNumber acos(const PmpNumber& num1);
    PmpNumber asin(const PmpNumber& num1);
    PmpNumber atan(const PmpNumber& num1);
    PmpNumber cosh(const PmpNumber& num1);
    PmpNumber sinh(const PmpNumber& num1);
    PmpNumber tanh(const PmpNumber& num1);
    PmpNumber pow(const PmpNumber& num1, const PmpNumber& num2);
    PmpNumber fmod(const PmpNumber& num1, const PmpNumber& num2);
    PmpNumber atan2(const PmpNumber& num1, const PmpNumber& num2);
} // namespace std

/////////////////////////////////////////////////////////////////////////////

class PmpNumber
{
public:
    PmpNumber() : m_inner(make_shared<Inner>(0)) { }
    PmpNumber(int i) : m_inner(make_shared<Inner>(i)) { }
    PmpNumber(__int64 i) : m_inner(make_shared<Inner>(i)) { }
    PmpNumber(double f) : m_inner(make_shared<Inner>(f)) { }
    PmpNumber(long double f) : m_inner(make_shared<Inner>(f)) { }
    PmpNumber(const pmp_integer_type& i) : m_inner(make_shared<Inner>(i)) { }
    PmpNumber(const pmp_floating_type& f) : m_inner(make_shared<Inner>(f)) { }
    PmpNumber(const PmpNumber& num) : m_inner(num.m_inner) { }

    PmpNumber& operator=(const PmpNumber& num)
    {
        m_inner = num.m_inner;
        return *this;
    }

    void assign(const pmp_integer_type& i)
    {
        m_inner = make_shared<Inner>(i);
    }

    void assign(const pmp_floating_type& f)
    {
        m_inner = make_shared<Inner>(f);
    }

    void assign(const PmpNumber& num)
    {
        m_inner = num.m_inner;
    }

    PmpNumber& operator+=(const PmpNumber& num);
    PmpNumber& operator-=(const PmpNumber& num);
    PmpNumber& operator*=(const PmpNumber& num);
    PmpNumber& operator/=(const PmpNumber& num);
    PmpNumber& operator%=(const PmpNumber& num);

    PmpNumber& operator++()
    {
        *this = *this + 1;
        return *this;
    }

    PmpNumber& operator--()
    {
        *this = *this - 1;
        return *this;
    }

    PmpNumber operator++(int)
    {
        PmpNumber num(*this);
        this->operator++();
        return num;
    }

    PmpNumber operator--(int)
    {
        PmpNumber num(*this);
        this->operator--();
        return num;
    }

    bool is_zero() const;
    bool operator!() const { return is_zero(); }
    std::string     str() const;

    pmp_integer_type    to_i() const;   // to integer
    pmp_floating_type   to_f() const;   // to floating

    void trim();

    template <typename T>
    T convert_to();

    bool is_i() const { return m_inner->m_type == Inner::INTEGER; }
    bool is_f() const { return m_inner->m_type == Inner::FLOATING; }

    int compare(int n) const
    {
        return compare(static_cast<double>(n));
    }

    int compare(__int64 n) const
    {
        return compare(static_cast<double>(n));
    }

    int compare(double d) const
    {
        return compare(static_cast<PmpNumber>(d));
    }

    int compare(long double d) const
    {
        return compare(static_cast<PmpNumber>(d));
    }

    int compare(const PmpNumber& num) const;

    void swap(PmpNumber& num)
    {
        m_inner.swap(num.m_inner);
    }

    friend inline PmpNumber operator+(const PmpNumber& num1)
    {
        return num1;
    }

    friend inline PmpNumber operator-(const PmpNumber& num1);

    friend inline PmpNumber operator+(const PmpNumber& num1, const PmpNumber& num2)
    {
        PmpNumber num(num1);
        num += num2;
        return num;
    }

    friend inline PmpNumber operator-(const PmpNumber& num1, const PmpNumber& num2)
    {
        PmpNumber num(num1);
        num -= num2;
        return num;
    }

    friend inline PmpNumber operator*(const PmpNumber& num1, const PmpNumber& num2)
    {
        PmpNumber num(num1);
        num *= num2;
        return num;
    }

    friend inline PmpNumber operator/(const PmpNumber& num1, const PmpNumber& num2)
    {
        PmpNumber num(num1);
        num /= num2;
        return num;
    }

    friend inline PmpNumber operator%(const PmpNumber& num1, const PmpNumber& num2)
    {
        PmpNumber num(num1);
        num %= num2;
        return num;
    }

    friend inline PmpNumber operator==(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) == 0;
    }

    friend inline PmpNumber operator!=(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) != 0;
    }

    friend inline PmpNumber operator<(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) < 0;
    }

    friend inline PmpNumber operator>(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) > 0;
    }

    friend inline PmpNumber operator<=(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) <= 0;
    }

    friend inline PmpNumber operator>=(const PmpNumber& num1, const PmpNumber& num2)
    {
        return num1.compare(num2) >= 0;
    }

    template <class CharT>
    friend std::basic_ostream<CharT>&
    operator<<(std::basic_ostream<CharT>& o, const PmpNumber& num);

    friend PmpNumber std::abs(const PmpNumber& num1);
    friend PmpNumber std::fabs(const PmpNumber& num1);
    friend PmpNumber std::sqrt(const PmpNumber& num1);
    friend PmpNumber std::floor(const PmpNumber& num1);
    friend PmpNumber std::ceil(const PmpNumber& num1);
    friend PmpNumber std::exp(const PmpNumber& num1);
    friend PmpNumber std::log(const PmpNumber& num1);
    friend PmpNumber std::log10(const PmpNumber& num1);
    friend PmpNumber std::cos(const PmpNumber& num1);
    friend PmpNumber std::sin(const PmpNumber& num1);
    friend PmpNumber std::tan(const PmpNumber& num1);
    friend PmpNumber std::acos(const PmpNumber& num1);
    friend PmpNumber std::asin(const PmpNumber& num1);
    friend PmpNumber std::atan(const PmpNumber& num1);
    friend PmpNumber std::cosh(const PmpNumber& num1);
    friend PmpNumber std::sinh(const PmpNumber& num1);
    friend PmpNumber std::tanh(const PmpNumber& num1);
    friend PmpNumber std::pow(const PmpNumber& num1, const PmpNumber& num2);
    friend PmpNumber std::fmod(const PmpNumber& num1, const PmpNumber& num2);
    friend PmpNumber std::atan2(const PmpNumber& num1, const PmpNumber& num2);

protected:
    struct Inner
    {
        enum Type
        {
            INTEGER, FLOATING
        };

        Type            m_type;
        pmp_integer_type *  m_integer;
        pmp_floating_type * m_floating;

        Inner() : m_type(INTEGER), m_integer(new pmp_integer_type())
        {
        }

        Inner(int i) :
            m_type(INTEGER),
            m_integer(new pmp_integer_type(i)),
            m_floating(NULL)
        {
        }

        explicit Inner(__int64 i) :
            m_type(INTEGER),
            m_integer(new pmp_integer_type(i)),
            m_floating(NULL)
        {
        }

        Inner(double f) :
            m_type(FLOATING),
            m_integer(NULL),
            m_floating(new pmp_floating_type(f))
        {
        }

        explicit Inner(long double f) :
            m_type(FLOATING),
            m_integer(NULL),
            m_floating(new pmp_floating_type(f))
        {
        }

        Inner(const pmp_integer_type& i) :
            m_type(INTEGER),
            m_integer(new pmp_integer_type(i)),
            m_floating(NULL)
        {
        }

        Inner(const pmp_floating_type& f) :
            m_type(FLOATING),
            m_integer(NULL),
            m_floating(new pmp_floating_type(f))
        {
        }

        Inner(const Inner& inner) :
            m_type(inner.m_type),
            m_integer(inner.m_integer ? new pmp_integer_type(*inner.m_integer) : NULL),
            m_floating(inner.m_floating ? new pmp_floating_type(*inner.m_floating) : NULL)
        {
        }

        ~Inner()
        {
            delete m_integer;
            delete m_floating;
        }
    }; // struct Inner
    shared_ptr<Inner> m_inner;
}; // class PmpNumber

inline PmpNumber std::abs(const PmpNumber& num1)
{
    return PmpNumber(std::fabs(num1.to_f()));
}

inline PmpNumber std::fabs(const PmpNumber& num1)
{
    return PmpNumber(std::fabs(num1.to_f()));
}

inline PmpNumber std::sqrt(const PmpNumber& num1)
{
    return PmpNumber(std::sqrt(num1.to_f()));
}

template <typename T>
inline T PmpNumber::convert_to()
{
    switch (m_inner->m_type)
    {
    case Inner::INTEGER:
        return m_inner->m_integer->convert_to<T>();

    case Inner::FLOATING:
        return m_inner->m_floating->convert_to<T>();

    default:
        assert(0);
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Non-member functions

namespace std
{
    inline void swap(PmpNumber& num1, PmpNumber& num2)
    {
        num1.swap(num2);
    }

    inline PmpNumber exp(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(exp(num1.to_f())));
    }

    inline PmpNumber log(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(log(num1.to_f())));
    }

    inline PmpNumber log10(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(log10(num1.to_f())));
    }

    inline PmpNumber cos(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(cos(num1.to_f())));
    }

    inline PmpNumber sin(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(sin(num1.to_f())));
    }

    inline PmpNumber tan(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(tan(num1.to_f())));
    }

    inline PmpNumber acos(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(acos(num1.to_f())));
    }

    inline PmpNumber asin(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(asin(num1.to_f())));
    }

    inline PmpNumber atan(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(atan(num1.to_f())));
    }

    inline PmpNumber cosh(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(cosh(num1.to_f())));
    }

    inline PmpNumber sinh(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(sinh(num1.to_f())));
    }

    inline PmpNumber tanh(const PmpNumber& num1)
    {
        using namespace std;
        return PmpNumber(static_cast<pmp_floating_type>(tanh(num1.to_f())));
    }

    inline PmpNumber pow(const PmpNumber& num1, const PmpNumber& num2)
    {
        return PmpNumber(std::pow(num1.to_f(), num2.to_f()));
    }

    inline PmpNumber fmod(const PmpNumber& num1, const PmpNumber& num2)
    {
        return PmpNumber(std::fmod(num1.to_f(), num2.to_f()));
    }

    inline PmpNumber atan2(const PmpNumber& num1, const PmpNumber& num2)
    {
        return PmpNumber(std::atan2(num1.to_f(), num2.to_f()));
    }
} // namespace std

/////////////////////////////////////////////////////////////////////////////

#endif  // ndef PMPNUMBER_HPP_

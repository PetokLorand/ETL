#ifndef ET_FUNDAMENTAL_EXPRESSION_HPP
#define ET_FUNDAMENTAL_EXPRESSION_HPP

#include <cstdint>

namespace et
{

template <typename TValue>
class FundamentalExpression : public BaseExpression<FundamentalExpression<TValue>>
{
public:
    FundamentalExpression(TValue value) : m_value(value) {}

    template <typename TProjection>
    TValue operator()(TProjection) { return m_value; }

    operator TValue() { return m_value; }

private:
    TValue m_value;
};

using Int8Expression = FundamentalExpression<std::int8_t>;
using Int16Expression = FundamentalExpression<std::int16_t>;
using Int32Expression = FundamentalExpression<std::int32_t>;
using Int64Expression = FundamentalExpression<std::int64_t>;

using Uint8Expression = FundamentalExpression<std::uint8_t>;
using Uint16Expression = FundamentalExpression<std::uint16_t>;
using Uint32Expression = FundamentalExpression<std::uint32_t>;
using Uint64Expression = FundamentalExpression<std::uint64_t>;

using Float32Expression = FundamentalExpression<float>;
using Flaot64Expression = FundamentalExpression<double>;

using BoolExpression = FundamentalExpression<bool>;
using CharExpression = FundamentalExpression<char>;

#define DefineFundamentalExpressionLiteral(TValue, VSuffix, TLiteral)                                                                       \
FundamentalExpression<TValue> operator""_##VSuffix (TLiteral value) { return  FundamentalExpression<TValue>{static_cast<TValue>(value)}; }  \

namespace literals
{

DefineFundamentalExpressionLiteral(std::int8_t, i8, unsigned long long int);
DefineFundamentalExpressionLiteral(std::int16_t, i16, unsigned long long int);
DefineFundamentalExpressionLiteral(std::int32_t, i32, unsigned long long int);
DefineFundamentalExpressionLiteral(std::int64_t, i64, unsigned long long int);
DefineFundamentalExpressionLiteral(std::uint8_t, u8, unsigned long long int);
DefineFundamentalExpressionLiteral(std::uint16_t, u16, unsigned long long int);
DefineFundamentalExpressionLiteral(std::uint32_t, u32, unsigned long long int);
DefineFundamentalExpressionLiteral(std::uint64_t, u64, unsigned long long int);
DefineFundamentalExpressionLiteral(float, f32, long double);
DefineFundamentalExpressionLiteral(double, f64, long double);

}//namespace literals
}//namespace et

#endif//ET_FUNDAMENTAL_EXPRESSION_HPP
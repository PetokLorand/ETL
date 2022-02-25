#ifndef ET_OPERATOR_HPP
#define ET_OPERATOR_HPP

namespace et
{

struct Plus
{
    decltype(auto) operator()(auto&& operand) { return +operand; }
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs + rhs; }
};

struct Minus
{
    decltype(auto) operator()(auto&& operand) { return -operand; }
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs - rhs; }
};

struct Asterisk
{
    decltype(auto) operator()(auto&& operand) { return *operand; }
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs * rhs; }
};

struct Slash
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs / rhs; }
};

struct Percent
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs % rhs; }
};

struct PlusEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs += rhs; }
};

struct MinusEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs -= rhs; }
};

struct AsteriskEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs *= rhs; }
};

struct SlashEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs /= rhs; }
};

struct PercentEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs %= rhs; }
};

struct Ampersand
{
    decltype(auto) operator()(auto&& operand) { return &operand; }
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs & rhs; }
};

struct Pipe
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs | rhs; }
};

struct Circumflex
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs ^ rhs; }
};

struct DoubleLessThan
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs << rhs; }
};

struct DoubleGreaterThan
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs >> rhs; }
};

struct Tilde
{
    decltype(auto) operator()(auto&& operand) { return ~operand; }
};

struct AmpersandEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs &= rhs; }
};

struct PipeEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs |= rhs; }
};

struct CircumflexEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs ^= rhs; }
};

struct DoubleLessThanEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs <<= rhs; }
};

struct DoubleGreaterThanEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs >>= rhs; }
};

struct DoubleEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs == rhs; }
};

struct ExclamationEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs != rhs; }
};

struct LessThan
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs < rhs; }
};

struct GreaterThan
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs > rhs; }
};

struct LessThanOrEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs <= rhs; }
};

struct GreaterThanOrEqual
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs >= rhs; }
};

struct DoubleAmpersand
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs && rhs; }
};

struct DoublePipe
{
    decltype(auto) operator()(auto&& lhs, auto&& rhs) { return lhs || rhs; }
};

struct Exclamation
{
    decltype(auto) operator()(auto&& operand) { return !operand; }
};

struct PrefixDoublePlus
{
    decltype(auto) operator()(auto&& operand) { return ++operand; }
};

struct PostfixDoublePlus
{
    decltype(auto) operator()(auto&& operand) { return operand++; }
};

struct PrefixDoubleMinus
{
    decltype(auto) operator()(auto&& operand) { return --operand; }
};

struct PostfixDoubleMinus
{
    decltype(auto) operator()(auto&& operand) { return operand--; }
};

}//namespace et

#endif//ET_OPERATOR_HPP
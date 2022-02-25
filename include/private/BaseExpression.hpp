#ifndef ET_BASE_EXPRESSION_HPP
#define ET_BASE_EXPRESSION_HPP

#include <type_traits>

namespace et
{

template <typename TResult, typename TExpression = TResult>
class BaseExpression {};

template <typename TResult, typename TExpression>
struct IsBaseExpression 
    : public std::is_base_of<BaseExpression<TResult, std::decay_t<TExpression>>, std::decay_t<TExpression>> 
{};

}//namespace et

#endif//ET_BASE_EXPRESSION_HPP
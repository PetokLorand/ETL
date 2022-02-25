#ifndef ET_EXPRESSION_INTERFACE_HPP
#define ET_EXPRESSION_INTERFACE_HPP

namespace et
{

template <typename TResult, typename TExpression>
class ExpressionInterface {};

#define DefineExpressionInterfaceMethod(TExpression, VMethodName, TOperation, TOperationResult, TArgEXpressionResults)      \
template <typename... TArgExpressions>                                                                                      \
requires std::conjunction_v<IsBaseExpression<TArgEXpressionResults, TArgExpressions>...>                                    \
decltype(auto) VMethodName (TArgExpressions&&... args)                                                                      \
{                                                                                                                           \
    return CompositeExpression<TOperation, TOperationResult, TExpression, TArgExpressions...>(std::forward<TExpression>(static_cast<TExpression&>(*this)), args...);\
}                                                                                                                           \

}//namespace et

#endif//ET_EXPRESSION_INTERFACE_HPP
#ifndef ET_COMPOSITE_EXPRESSION_HPP
#define ET_COMPOSITE_EXPRESSION_HPP

#include "BaseExpression.hpp"
#include "ExpressionInterface.hpp"
#include "ExpressionProjections.hpp"

#include <tuple>

namespace et
{

template <typename TOperation, typename TOperationResult, typename... TSubExpressions>
class CompositeExpression
    : public BaseExpression<TOperationResult, CompositeExpression<TOperation, TOperationResult, TSubExpressions...>>
    , public ExpressionInterface<TOperationResult, CompositeExpression<TOperation, TOperationResult, TSubExpressions...>>
{
public:
    CompositeExpression(TSubExpressions... subExpressions)
        : m_subExpressions(std::forward<TSubExpressions>(subExpressions)...) 
    {}

    template <typename Projection = IdentityProjection>
    decltype(auto) operator()(Projection projection = {}) 
    { 
        auto lambda = [&projection](auto&&... args){ return TOperation{}(projection, std::forward<decltype(args)>(args)...); };
        return std::apply(lambda, m_subExpressions);
    }

private:
    std::tuple<TSubExpressions...> m_subExpressions;
};

}//namespace et

#endif//ET_COMPOSITE_EXPRESSION_HPP
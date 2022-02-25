#ifndef ET_EXPRESSION_PROJECTIONS_HPP
#define ET_EXPRESSION_PROJECTIONS_HPP

namespace et
{

class IdentityProjection
{
public:
    template <typename TExpression>
    decltype(auto) operator()(TExpression&& expression)
    {
        return std::forward<TExpression>(expression);
    }
};

template <typename TIdxExpression>
class SubscriptProjection
{
public:
    SubscriptProjection(TIdxExpression&& index) : m_index(std::move(index)) {}
    SubscriptProjection(const TIdxExpression& index) : m_index(index) {}

    template <typename TExpression>
    decltype(auto) operator()(TExpression&& expression)
    {
        return expression[m_index];
    }

private:
    TIdxExpression m_index;
};

}//namespace et

#endif//ET_EXPRESSION_PROJECTIONS_HPP
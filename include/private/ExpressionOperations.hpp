#ifndef ET_EXPRESSION_OPERATIONS_HPP
#define ET_EXPRESSION_OPERATIONS_HPP

#include "Operators.hpp"
#include "ExpressionProjections.hpp"

namespace et
{

template <typename TProjectionFunctor>
class ProjectionOperation
{
public:
    template <typename TProjection, typename TMainExpression, typename... TProjectionExpressions>
    decltype(auto) operator()(TProjection&&, TMainExpression&& mainExpression, TProjectionExpressions&&... projectionExpressions)
    {
        return mainExpression(TProjectionFunctor{ std::forward<TProjectionExpressions>(projectionExpressions)... });
    }
};

#define DefineBinaryOperation(VOperationName, TOperator)                                                                                            \
template <typename TLhsExpressionResult, typename TRhsExpressionResult>                                                                             \
class VOperationName                                                                                                                                \
{                                                                                                                                                   \
public:                                                                                                                                             \
    template <typename TProjection, typename TLhsExpression, typename TRhsExpression>                                                               \
    decltype(auto) operator()(TProjection&& projection, TLhsExpression&& lhs, TRhsExpression&& rhs)                                                 \
    {                                                                                                                                               \
        return TOperator{}(projection(std::forward<TLhsExpression>(lhs))(projection), projection(std::forward<TRhsExpression>(rhs))(projection));   \
    }                                                                                                                                               \
}                                                                                                                                                   \

#define DefineUnaryOperation(VOperationName, TOperator)                                                                                             \
template <typename TExpressionResult>                                                                                                               \
class VOperationName                                                                                                                                \
{                                                                                                                                                   \
public:                                                                                                                                             \
    template <typename TProjection, typename TExpression>                                                                                           \
    decltype(auto) operator()(TProjection&& projection, TExpression&& expression)                                                                   \
    {                                                                                                                                               \
        return TOperator{}(projection(std::forward<TExpression>(expression))(projection));                                                          \
    }                                                                                                                                               \
}                                                                                                                                                   \

// Arithmetic Operations
DefineBinaryOperation(AdditionOperation, Plus);
DefineBinaryOperation(SubtractionOperation, Minus);
DefineBinaryOperation(MultiplicationOperation, Asterisk);
DefineBinaryOperation(DivisionOperation, Slash);
DefineBinaryOperation(ModuloOperation, Percent);
DefineUnaryOperation(PositiveOperation, Plus);
DefineUnaryOperation(NegationOperation, Minus);
DefineBinaryOperation(AdditionAssignmentOperation, PlusEqual);
DefineBinaryOperation(SubtractionAssignmentOperation, MinusEqual);
DefineBinaryOperation(MultiplicationAssignmentOperation, AsteriskEqual);
DefineBinaryOperation(DivisionAssignmentOperation, SlashEqual);
DefineBinaryOperation(ModuloAssignmentOperation, PercentEqual);

// Bitwise Operations
DefineBinaryOperation(BitAndOperation, Ampersand);
DefineBinaryOperation(BitOrOperation, Pipe);
DefineBinaryOperation(BitXorOperation, Circumflex);
DefineBinaryOperation(BitLeftShiftOperation, DoubleLessThan);
DefineBinaryOperation(BitRightShiftOperation, DoubleGreaterThan);
DefineUnaryOperation(BitNegationOperation, Tilde);
DefineBinaryOperation(BitAndAssignmentOperation, AmpersandEqual);
DefineBinaryOperation(BitOrAssignmentOperation, PipeEqual);
DefineBinaryOperation(BitXorAssignmentOperation, CircumflexEqual);
DefineBinaryOperation(BitLeftShiftAssignmentOperation, DoubleLessThanEqual);
DefineBinaryOperation(BitRightShiftAssignmentOperation, DoubleGreaterThanEqual);

// Comparison Operations
DefineBinaryOperation(EqualityOperation, DoubleEqual);
DefineBinaryOperation(NonEqualityOperation, ExclamationEqual);
DefineBinaryOperation(LessThanOperation, LessThan);
DefineBinaryOperation(GreaterThanOperation, GreaterThan);
DefineBinaryOperation(LessThanOrEqualOperation, LessThanOrEqual);
DefineBinaryOperation(GreaterThanOrEqualOperation, GreaterThanOrEqual);

// Logic Operations
DefineBinaryOperation(LogicAndOperation, DoubleAmpersand);
DefineBinaryOperation(LogicOrOperation, DoublePipe);
DefineUnaryOperation(LogicNegationOperation, Exclamation);

// Increment & Decrement Operations
DefineUnaryOperation(PrefixIncrementOperation, PrefixDoublePlus);
DefineUnaryOperation(PostfixIncrementOperation, PostfixDoublePlus);
DefineUnaryOperation(PrefixDecrementOperation, PrefixDoubleMinus);
DefineUnaryOperation(PostfixDecrementOperation, PostfixDoubleMinus); 

// Access Operations
DefineUnaryOperation(DereferentiationOperation, Asterisk);

}//namespace et

#endif//ET_EXPRESSION_OPERATIONS_HPP
#ifndef ET_EXPRESSION_GENERATOR_HPP
#define ET_EXPRESSION_GENERATOR_HPP

#include "BaseExpression.hpp"
#include "ExpressionOperations.hpp"
#include "ExpressionProjections.hpp"
#include "CompositeExpression.hpp"

namespace et
{

template <typename TOperation, typename TOperationResult, typename... TSubExpressionResults>
class ExpressionGenerator
{
public:
    template <typename... TSubExpressions>
    static constexpr bool check = std::conjunction_v<IsBaseExpression<TSubExpressionResults, TSubExpressions>...>;

    template <typename... TSubExpressions>
    decltype(auto) operator()(TSubExpressions&&... subExpressions)
    {
        return CompositeExpression<TOperation, TOperationResult, TSubExpressions...>(std::forward<TSubExpressions>(subExpressions)...);
    }
};

#define DefineBinaryExpressionGenerator(VGeneratorName, VOperatorName, TOperation)                                                          \
template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>\
class VGeneratorName                                                                                                                        \
{                                                                                                                                           \
private:                                                                                                                                    \
    using Operation = TOperation<TLhsExpressionResult, TRhsExpressionResult>;                                                               \
    using Generator = ExpressionGenerator<Operation, TOperationResult, TLhsExpressionResult, TRhsExpressionResult>;                         \
                                                                                                                                            \
public:                                                                                                                                     \
    template <typename TLhsExpression, typename TRhsExpression>                                                                             \
    requires Generator::template check<TLhsExpression, TRhsExpression>                                                                      \
    friend decltype(auto) VOperatorName (TLhsExpression&& lhs, TRhsExpression&& rhs)                                                        \
    {                                                                                                                                       \
        return Generator{}(std::forward<TLhsExpression>(lhs), std::forward<TRhsExpression>(rhs));                                           \
    }                                                                                                                                       \
}                                                                                                                                           \

#define DefineUnaryExpressionGenerator(VGeneratorName, VOperatorName, TOperation)                                                           \
template <typename TOperationResult, typename TExpressionResult = TOperationResult>                                                         \
class VGeneratorName                                                                                                                        \
{                                                                                                                                           \
private:                                                                                                                                    \
    using Generator = ExpressionGenerator<TOperation<TExpressionResult>, TOperationResult, TExpressionResult>;                              \
                                                                                                                                            \
public:                                                                                                                                     \
    template <typename TExpression>                                                                                                         \
    requires Generator::template check<TExpression>                                                                                         \
    friend decltype(auto) VOperatorName (TExpression&& expression)                                                                          \
    {                                                                                                                                       \
        return Generator{}(std::forward<TExpression>(expression));                                                                          \
    }                                                                                                                                       \
}                                                                                                                                           \

#define DefineAlternativeUnaryExpressionGenerator(VGeneratorName, VOperatorName, TOperation)                                                \
template <typename TOperationResult, typename TExpressionResult = TOperationResult>                                                         \
class VGeneratorName                                                                                                                        \
{                                                                                                                                           \
private:                                                                                                                                    \
    using Generator = ExpressionGenerator<TOperation<TExpressionResult>, TOperationResult, TExpressionResult>;                              \
                                                                                                                                            \
public:                                                                                                                                     \
    template <typename TExpression>                                                                                                         \
    requires Generator::template check<TExpression>                                                                                         \
    friend decltype(auto) VOperatorName (TExpression&& expression, int)                                                                     \
    {                                                                                                                                       \
        return Generator{}(std::forward<TExpression>(expression));                                                                          \
    }                                                                                                                                       \
}                                                                                                                                           \

// Arithmetic Expression Generators
DefineBinaryExpressionGenerator(AdditionExpressionGenerator, operator+, AdditionOperation);
DefineBinaryExpressionGenerator(SubtractionExpressionGenerator, operator-, SubtractionOperation);
DefineBinaryExpressionGenerator(MultiplicationExpressionGenerator, operator*, MultiplicationOperation);
DefineBinaryExpressionGenerator(DivisionExpressionGenerator, operator/, DivisionOperation);
DefineBinaryExpressionGenerator(ModuloExpressionGenerator, operator%, ModuloOperation);
DefineUnaryExpressionGenerator(NegationExpressionGenerator, operator-, NegationOperation);
DefineBinaryExpressionGenerator(AdditionAssignmentExpressionGenerator, operator+=, AdditionAssignmentOperation);
DefineBinaryExpressionGenerator(SubtractionAssignmentExpressionGenerator, operator-=, SubtractionAssignmentOperation);
DefineBinaryExpressionGenerator(MultiplicationAssignmentExpressionGenerator, operator*=, MultiplicationAssignmentOperation);
DefineBinaryExpressionGenerator(DivisionAssignmentExpressionGenerator, operator/=, DivisionAssignmentOperation);
DefineBinaryExpressionGenerator(ModuloAssignmentExpressionGenerator, operator%=, ModuloAssignmentOperation);

// Bitwise Expression Generators
DefineBinaryExpressionGenerator(BitAndExpressionGenerator, operator&, BitAndOperation);
DefineBinaryExpressionGenerator(BitOrExpressionGenerator, operator|, BitOrOperation);
DefineBinaryExpressionGenerator(BitXorExpressionGenerator, operator^, BitXorOperation);
DefineBinaryExpressionGenerator(BitLeftShiftExpressionGenerator, operator<<, BitLeftShiftOperation);
DefineBinaryExpressionGenerator(BitRightShiftExpressionGenerator, operator>>, BitRightShiftOperation);
DefineUnaryExpressionGenerator(BitNegationExpressionGenerator, operator~, BitNegationOperation);
DefineBinaryExpressionGenerator(BitAndAssignmentExpressionGenerator, operator&=, BitAndAssignmentOperation);
DefineBinaryExpressionGenerator(BitOrAssignmentExpressionGenerator, operator|=, BitOrAssignmentOperation);
DefineBinaryExpressionGenerator(BitXorAssignmentExpressionGenerator, operator^=, BitXorAssignmentOperation);
DefineBinaryExpressionGenerator(BitLeftShiftAssignmentExpressionGenerator, operator<<=, BitLeftShiftAssignmentOperation);
DefineBinaryExpressionGenerator(BitRightShiftAssignmentExpressionGenerator, operator>>=, BitRightShiftAssignmentOperation);

// Comparison Expression Generators
DefineBinaryExpressionGenerator(EqualityExpressionGenerator, operator==, EqualityOperation);
DefineBinaryExpressionGenerator(NonEqualityExpressionGenerator, operator!=, NonEqualityOperation);
DefineBinaryExpressionGenerator(LessThanExpressionGenerator, operator<, LessThanOperation);
DefineBinaryExpressionGenerator(GreaterThanExpressionGenerator, operator>, GreaterThanOperation);
DefineBinaryExpressionGenerator(LessThanOrEqualExpressionGenerator, operator<=, LessThanOrEqualOperation);
DefineBinaryExpressionGenerator(GreaterThanOrEqualExpressionGenerator, operator>=, GreaterThanOrEqualOperation);

// Logic Expression Generators
DefineBinaryExpressionGenerator(LogicAndExpressionGenerator, operator&&, LogicAndOperation);
DefineBinaryExpressionGenerator(LogicOrExpressionGenerator, operator||, LogicOrOperation);
DefineUnaryExpressionGenerator(LogicNegationExpressionGenerator, operator!, LogicNegationOperation);

// Increment & Decrement Expression Generators
DefineUnaryExpressionGenerator(PrefixIncrementExpressionGenerator, operator++, PrefixIncrementOperation);
DefineAlternativeUnaryExpressionGenerator(PostfixIncrementExpressionGenerator, operator++, PostfixIncrementOperation);
DefineUnaryExpressionGenerator(PrefixDecrementExpressionGenerator, operator--, PrefixDecrementOperation);
DefineAlternativeUnaryExpressionGenerator(PostfixDecrementExpressionGenerator, operator--, PostfixDecrementOperation);

// Access Expression Generators
DefineUnaryExpressionGenerator(DereferentiationExpressionOperation, operator*, DereferentiationOperation);

template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>
class ArithmeticExpressionGenerators 
    : public AdditionExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public SubtractionExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public MultiplicationExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public DivisionExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public ModuloExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public NegationExpressionGenerator<TOperationResult, TLhsExpressionResult>
    , public AdditionAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public SubtractionAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public MultiplicationAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public DivisionAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public ModuloAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
{};

template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>
class BitExpressionGenerators
    : public BitAndExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitOrExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitXorExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitLeftShiftExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitRightShiftExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitNegationExpressionGenerator<TOperationResult, TLhsExpressionResult>
    , public BitAndAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitOrAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitXorAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitLeftShiftAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public BitRightShiftAssignmentExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
{};

template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>
class ComparisonExpressionGenerators
    : public EqualityExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public NonEqualityExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public LessThanExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public GreaterThanExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public LessThanOrEqualExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public GreaterThanOrEqualExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
{};

template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>
class LogicExpressionGenerators
    : public LogicAndExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public LogicOrExpressionGenerator<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public LogicNegationExpressionGenerator<TOperationResult, TLhsExpressionResult>
{};

template <typename TOperationResult, typename TExpressionResult = TOperationResult>
class IncrementAndDecrementExpressionGenerators
    : public PrefixIncrementExpressionGenerator<TOperationResult, TExpressionResult>
    , public PostfixIncrementExpressionGenerator<TOperationResult, TExpressionResult>
    , public PrefixDecrementExpressionGenerator<TOperationResult, TExpressionResult>
    , public PostfixDecrementExpressionGenerator<TOperationResult, TExpressionResult>
{};

template <typename TOperationResult, typename TExpressionResult = TOperationResult>
class AccessExpressionGenerators
    : public DereferentiationExpressionOperation<TOperationResult, TExpressionResult>
{};

template <typename TOperationResult, typename TLhsExpressionResult = TOperationResult, typename TRhsExpressionResult = TLhsExpressionResult>
class AllExpressionGenerators
    : public ArithmeticExpressionGenerators<TOperationResult, TLhsExpressionResult, TRhsExpressionResult> 
    , public BitExpressionGenerators<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public ComparisonExpressionGenerators<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public LogicExpressionGenerators<TOperationResult, TLhsExpressionResult, TRhsExpressionResult>
    , public IncrementAndDecrementExpressionGenerators<TOperationResult, TLhsExpressionResult>
    , public AccessExpressionGenerators<TOperationResult, TLhsExpressionResult>
{};

}// namespace et

#endif//ET_EXPRESSION_GENERATOR_HPP
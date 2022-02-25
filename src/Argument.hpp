#pragma once
#include "ExpressionTemplates.hpp"

struct Argument
    : public et::BaseExpression<Argument>
    , public et::AllExpressionGenerators<Argument>
{
    Argument(int value) : m_value(value) { ++ctor; } 
    ~Argument() { ++dtor; }
    Argument(const Argument& rhs) : m_value(rhs.m_value) { ++copyCtor; }
    Argument(Argument&& rhs) : m_value(rhs.m_value) { rhs.m_value = 0; ++moveCtor; }
    Argument& operator=(const Argument& rhs) { m_value = rhs.m_value; ++copyAssign; return *this; }
    Argument& operator=(Argument&& rhs) { m_value = rhs.m_value; rhs.m_value = 0; ++moveAssign; return *this; }
 
    et::Int32Expression operator()(auto projection) { (void)projection; ++access; return m_value; }
    et::Int32Expression operator[](std::size_t idx) { return m_value - idx; }

    int m_value;

    static void print()
    {
        std::cout << "ctor: " << ctor << std::endl; 
        std::cout << "dtor: " << dtor << std::endl; 
        std::cout << "copyCtor: " << copyCtor << std::endl; 
        std::cout << "moveCtor: " << moveCtor << std::endl; 
        std::cout << "copyAssign: " << copyAssign << std::endl; 
        std::cout << "moveAssign: " << moveAssign << std::endl;
        std::cout << "access: " << access << std::endl; 
    }

    inline static int ctor { 0 }; 
    inline static int dtor { 0 }; 
    inline static int copyCtor { 0 }; 
    inline static int moveCtor { 0 }; 
    inline static int copyAssign { 0 }; 
    inline static int moveAssign { 0 };
    inline static int access { 0 }; 
};


template <typename TExpression>
class et::ExpressionInterface<Argument, TExpression>
{
public:
    DefineExpressionInterfaceMethod(TExpression, operator[], ProjectionOperation<SubscriptProjection<Uint64Expression>>, Int32Expression, Uint64Expression)
};
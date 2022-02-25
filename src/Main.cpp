#include <iostream>
#include "ExpressionTemplates.hpp"
#include "Argument.hpp"

class Scalar
    : public et::BaseExpression<Scalar>
    , public et::AdditionExpressionGenerator<Scalar> 
{
public:
    Scalar(int value) : m_value(value) {}

    et::Int32Expression operator()(auto&&) { return m_value; }

private:
    int m_value;
};

int main()
{
    using namespace et::literals;
    {
        Argument x(10);
        Argument y(5);
        Argument z(2);

        auto result = (x * y - x /  z)[3_u64];
        std::cout << result() << std::endl;    
    }

    // auto result = (Argument{2} + Argument{3})[1_u64];
    // std::cout << result() << std::endl;

    Argument::print();

    return 0; 
}

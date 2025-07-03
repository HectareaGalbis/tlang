
#include "objects.hpp"
#include "package.hpp"
#include <iostream>
#include <optional>

// --------------------------------------------------------------------------------

integer::integer(int64_t _value)
    : value(_value)
{
}

std::shared_ptr<expr> integer::eval(lexical_environment& lex_env [[maybe_unused]]) const
{
    return std::make_shared<integer>(value);
}

void integer::print() const
{
    std::cout << this->value;
}

// --------------------------------------------------------------------------------

symbol::symbol(const std::string& _name)
    : name(_name)
{
}

std::shared_ptr<expr> symbol::eval(lexical_environment& lex_env) const
{
    std::optional<std::shared_ptr<symbol>> maybe_symbol = package.find_symbol(this->name);
    if (maybe_symbol)
        return lex_env.get_value(*maybe_symbol);
    else
        throw std::runtime_error("Symbol not bound.");
}

void symbol::print() const
{
    std::cout << this->name;
}

// --------------------------------------------------------------------------------

std::shared_ptr<expr> list::eval(lexical_environment& lex_env) const
{
    std::shared_ptr<symbol> func_name = std::dynamic_pointer_cast<symbol>(elements[0]);
    if (!func_name)
        throw std::runtime_error("Expected a symbol denoting a procedure.");
    if (!func_name->function)
        throw std::runtime_error("The symbol " + func_name->name + " does not denote a procedure.");
    std::vector<std::shared_ptr<expr>> arguments;
    for (size_t i = 1; i < elements.size(); i++)
        arguments.push_back(elements[i]);
    return func_name->function->apply(lex_env, arguments);
}

;

void list::print() const
{
    std::cout << "(";
    if (!this->elements.empty()) {
        this->elements.front()->print();
        for (size_t i = 1; i < this->elements.size(); i++) {
            std::cout << " ";
            this->elements[i]->print();
        }
    }
    std::cout << ")";
}

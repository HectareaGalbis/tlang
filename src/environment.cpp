
#include "environment.hpp"
#include "objects.hpp"

bool lexical_environment::is_symbol_bound(const std::shared_ptr<symbol>& symbol)
{
    bool is_bound = values.contains(symbol);

    if (is_bound && values[symbol].empty())
        throw std::runtime_error("Corrupted symbol");

    return is_bound;
}

void lexical_environment::push_value(const std::shared_ptr<symbol>& symbol, const std::shared_ptr<expr>& value)
{
    values[symbol].push_back(value);
}

void lexical_environment::pop_value(const std::shared_ptr<symbol>& symbol)
{
    if (!is_symbol_bound(symbol))
        throw std::runtime_error("The symbol " + symbol->name + " is not bound");

    values[symbol].pop_back();

    if (values[symbol].empty())
        values.erase(symbol);
}

std::shared_ptr<expr> lexical_environment::get_value(const std::shared_ptr<symbol>& symbol)
{
    if (!is_symbol_bound(symbol))
        throw std::runtime_error("The symbol " + symbol->name + " is not bound");

    return values[symbol].back();
}

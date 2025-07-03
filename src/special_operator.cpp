
#include "special_operator.hpp"
#include "objects.hpp"
#include "package.hpp"
#include <iostream>
#include <memory>

void intern_special_operators()
{
    intern_special_operator(progn);
    intern_special_operator(let);
    intern_special_operator(quote);
}

// --------------------------------------------------------------------------------

std::shared_ptr<expr> progn::apply(
    lexical_environment& lex_env [[maybe_unused]],
    const std::vector<std::shared_ptr<expr>>& arguments)
{
    if (arguments.empty()) {
        return std::make_shared<nil>();
    }
    for (size_t i = 0; i < arguments.size() - 1; i++) {
        arguments[i]->eval(lex_env);
    }
    return arguments.back()->eval(lex_env);
}

// --------------------------------------------------------------------------------

static std::vector<std::pair<std::shared_ptr<symbol>, std::shared_ptr<expr>>> parseBindings(
    const std::shared_ptr<list>& bindings)
{
    std::vector<std::pair<std::shared_ptr<symbol>, std::shared_ptr<expr>>> parsedBindings;

    for (const std::shared_ptr<expr>& element : bindings->elements) {
        const std::shared_ptr<list> binding = std::dynamic_pointer_cast<list>(element);
        if (!binding)
            throw std::runtime_error("Expected a binding clause (a list).");
        if (binding->elements.size() != 2)
            throw std::runtime_error("The binding clause must have 2 elements.");
        const std::shared_ptr<symbol> var = std::dynamic_pointer_cast<symbol>(binding->elements[0]);
        if (!var)
            throw std::runtime_error("The first element of the binding clause must be a symbol");
        const std::shared_ptr<expr>& value = binding->elements[1];
        parsedBindings.emplace_back(std::move(var), value);
    }

    return parsedBindings;
}

static std::vector<std::pair<std::shared_ptr<symbol>, std::shared_ptr<expr>>> evaluateBindings(
    lexical_environment& lex_env,
    const std::vector<std::pair<std::shared_ptr<symbol>, std::shared_ptr<expr>>>& bindings)
{
    std::vector<std::pair<std::shared_ptr<symbol>, std::shared_ptr<expr>>> evaluatedBindings;

    for (const auto& [var, value] : bindings) {
        evaluatedBindings.emplace_back(var, value->eval(lex_env));
    }

    return evaluatedBindings;
}

std::shared_ptr<expr> let::apply(
    lexical_environment& lex_env,
    const std::vector<std::shared_ptr<expr>>& arguments)
{
    if (arguments.empty())
        throw std::runtime_error("let needs at least a list");

    const std::shared_ptr<list> bindings = std::dynamic_pointer_cast<list>(arguments.front());
    if (!bindings)
        throw std::runtime_error("Expected a list.");
    auto parsedBindings = parseBindings(bindings);
    auto evaluatedBindings = evaluateBindings(lex_env, parsedBindings);

    if (arguments.size() == 1)
        return std::make_shared<nil>();

    for (const auto& [var, value] : evaluatedBindings)
        lex_env.push_value(var, value);
    for (size_t i = 1; i < arguments.size() - 1; i++)
        arguments[i]->eval(lex_env);
    std::shared_ptr<expr> result = arguments.back()->eval(lex_env);
    for (const auto& [var, value] : evaluatedBindings)
        lex_env.pop_value(var);

    return result;
}

// --------------------------------------------------------------------------------

std::shared_ptr<expr> quote::apply(
    lexical_environment& lex_env [[maybe_unused]],
    const std::vector<std::shared_ptr<expr>>& arguments)
{
    if (arguments.size() != 1)
        throw std::runtime_error("Expected only one argument.");
    return arguments[0];
}


#pragma once

#include "grammar.hpp"
#include "linenoise.h"
#include "objects.hpp"
#include "package.hpp"
#include <iostream>
#include <memory>
#include <tao/pegtl.hpp>

namespace peg = tao::pegtl;

template <typename Rule>
struct make_ast;

class ast {
private:
    std::vector<std::vector<std::shared_ptr<expr>>> expressions_stack;

public:
    ast()
    {
        linenoiseSetMultiLine(1);
        linenoiseHistorySetMaxLen(100);
    }

    void push_layer()
    {
        this->expressions_stack.emplace_back();
    }

    std::vector<std::shared_ptr<expr>> pop_layer()
    {
        std::vector<std::shared_ptr<expr>> expressions = this->expressions_stack.back();
        this->expressions_stack.pop_back();
        return expressions;
    }

    void add_expr(const std::shared_ptr<expr>& expression)
    {
        this->expressions_stack.back().push_back(expression);
    }

    void read()
    {
        expressions_stack.clear();
        this->push_layer();
        char* line = linenoise("tlang> ");
        peg::string_input in(line, "stdin");
        peg::parse<lex::tlang, make_ast>(in, *this);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }

    void eval(lexical_environment& lex_env)
    {
        for (std::shared_ptr<expr>& expression : this->expressions_stack.front()) {
            expression = expression->eval(lex_env);
        }
    }

    void print() const
    {
        if (this->expressions_stack.front().empty()) {
            std::cout << ";; No values" << std::endl;
        } else {
            for (const std::shared_ptr<expr>& expression : this->expressions_stack.front()) {
                expression->print();
                std::cout << std::endl;
            }
        }
    }
};

template <typename Rule>
struct make_ast {
    template <typename ActionInput>
    static void apply(ActionInput& in [[maybe_unused]], ast& ast [[maybe_unused]]) { }
};

// integer
template <>
struct make_ast<lex::integer> {
    template <typename ActionInput>
    static void apply(ActionInput& in, ast& ast)
    {
        int64_t value = atoll(in.string().c_str());
        ast.add_expr(std::make_shared<integer>(value));
    }
};

// symbol
template <>
struct make_ast<lex::symbol> {
    template <typename ActionInput>
    static void apply(ActionInput& in, ast& ast)
    {
        std::shared_ptr<symbol>& sym = package.intern_symbol(in.string());
        ast.add_expr(sym);
    }
};

// list
template <>
struct make_ast<lex::lparen> {
    template <typename ActionInput>
    static void apply(ActionInput& in [[maybe_unused]], ast& ast)
    {
        ast.push_layer();
    }
};

template <>
struct make_ast<lex::rparen> {
    template <typename ActionInput>
    static void apply(ActionInput& in [[maybe_unused]], ast& ast)
    {
        std::vector<std::shared_ptr<expr>> elements = ast.pop_layer();
        if (elements.empty())
            ast.add_expr(std::make_shared<nil>());
        else
            ast.add_expr(std::make_shared<list>(std::move(elements)));
    }
};

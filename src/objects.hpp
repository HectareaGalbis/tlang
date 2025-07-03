
#pragma once

#include "environment.hpp"
#include "procedure.hpp"
#include <memory>
#include <vector>

struct expr {
    virtual std::shared_ptr<expr> eval(lexical_environment& lex_env) const = 0;
    virtual void print() const = 0;

    virtual operator bool() const { return true; }
};

// integer
struct integer : expr {
    int64_t value;

    integer(int64_t _value);

    virtual std::shared_ptr<expr> eval(lexical_environment& lex_env [[maybe_unused]]) const override;
    virtual void print() const override;
};

// symbol
struct symbol : expr {
    std::string name;
    std::vector<std::shared_ptr<expr>> values;
    std::shared_ptr<procedure> function;

    symbol(const std::string& _name);

    virtual std::shared_ptr<expr> eval(lexical_environment& lex_env) const override;
    virtual void print() const override;
};

// list
struct list : expr {
    std::vector<std::shared_ptr<expr>> elements;

    template <typename Elements>
    list(Elements&& _elements)
        : elements(std::forward<Elements>(_elements))
    {
    }

    virtual std::shared_ptr<expr> eval(lexical_environment& lex_env) const override;
    virtual void print() const override;
};

// nil
struct nil : list {
    nil()
        : list(std::vector<std::shared_ptr<expr>>())
    {
    }

    virtual operator bool() const override { return false; }
};

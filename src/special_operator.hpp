
#pragma once

#include "procedure.hpp"

#define declare_special_operator(name)                                     \
    class name : public procedure {                                        \
    public:                                                                \
        virtual std::shared_ptr<expr> apply(                               \
            lexical_environment& lex_env,                                  \
            const std::vector<std::shared_ptr<expr>>& arguments) override; \
    }

#define intern_special_operator(name)                                    \
    std::shared_ptr<symbol>& name##_func = package.intern_symbol(#name); \
    name##_func->function = std::make_shared<name>();

void intern_special_operators();

declare_special_operator(progn);
declare_special_operator(let);
declare_special_operator(quote);

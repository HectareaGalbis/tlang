
#pragma once

#include "environment.hpp"

struct symbol;
struct expr;

class procedure {
public:
    virtual std::shared_ptr<expr> apply(
        lexical_environment& lex_env,
        const std::vector<std::shared_ptr<expr>>& arguments)
        = 0;
};

// class procedure : public procedure {
// private:
//     std::vector<std::shared_ptr<expr>> body;

// public:
//     template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
//     procedure(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body);

//     virtual std::shared_ptr<expr> apply(const std::vector<std::shared_ptr<expr>>& parameters) = 0;
// };

// template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
// procedure::procedure(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body)
//     : procedure(
//           std::forward<LEX_ENV>(_lex_env),
//           std::forward<ARGUMENTS>(_arguments))
//     , body(std::forward<BODY>(_body))
// {
// }

// class function : public procedure {
// private:
//     std::vector<std::shared_ptr<expr>> body;

// public:
//     template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
//     function(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body);

//     virtual std::shared_ptr<expr> apply(const std::vector<std::shared_ptr<expr>>& parameters) override;
// };

// template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
// function::function(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body)
//     : procedure(
//           std::forward<LEX_ENV>(_lex_env),
//           std::forward<ARGUMENTS>(_arguments),
//           std::forward<BODY>(_body))
// {
// }

// class macro : public procedure {
// private:
//     std::vector<std::shared_ptr<expr>> body;

// public:
//     template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
//     macro(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body);

//     // Apply or expand??
//     virtual std::shared_ptr<expr> apply(const std::vector<std::shared_ptr<expr>>& parameters) override;
// };

// template <typename LEX_ENV, typename ARGUMENTS, typename BODY>
// macro::macro(LEX_ENV&& _lex_env, ARGUMENTS&& _arguments, BODY&& _body)
//     : procedure(
//           std::forward<LEX_ENV>(_lex_env),
//           std::forward<ARGUMENTS>(_arguments),
//           std::forward<BODY>(_body))
// {
// }


#include "procedure.hpp"
#include "objects.hpp"
#include <utility>

// std::shared_ptr<expr> applicator::apply(
//     const std::vector<std::shared_ptr<expr>>& parameters,
//     const std::vector<std::shared_ptr<expr>>& body)
// {
//     if (arguments.size() != parameters.size())
//         throw std::runtime_error("Numero de argumentos incorrecto");

//     for (size_t i = 0; i < arguments.size(); i++) {
//         lex_env.push_value(arguments[i], parameters[i]);
//     }
//     for (size_t i = 0; i < body.size() - 1; i++) {
//         body[i]->eval(lex_env);
//     }
//     std::shared_ptr<expr> result = body.back()->eval(lex_env);
//     for (size_t i = 0; i < arguments.size(); i++) {
//         lex_env.pop_value(arguments[i]);
//     }

//     return result;
// }

// std::shared_ptr<expr> function::apply(const std::vector<std::shared_ptr<expr>>& parameters)
// {
//     std::vector<std::shared_ptr<expr>> evaluated_parameters;
//     for (const std::shared_ptr<expr>& parameter : parameters) {
//         evaluated_parameters.push_back(parameter->eval(lex_env));
//     }

//     return applicator::apply(evaluated_parameters, body);
// }

// std::shared_ptr<expr> macro::apply(const std::vector<std::shared_ptr<expr>>& parameters)
// {
//     return applicator::apply(parameters, body);
// }

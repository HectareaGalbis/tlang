
#include "parser.hpp"
#include "special_operator.hpp"

int main()
{
    intern_special_operators();

    while (true) {
        try {
            ast ast;
            ast.read();
            lexical_environment lex_env;
            ast.eval(lex_env);
            ast.print();
        } catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}

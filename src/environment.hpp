
#pragma once

#include <map>
#include <memory>
#include <vector>

struct symbol;
struct expr;

class lexical_environment {
private:
    std::map<std::shared_ptr<symbol>, std::vector<std::shared_ptr<expr>>> values;

public:
    bool is_symbol_bound(const std::shared_ptr<symbol>& symbol);

    void push_value(const std::shared_ptr<symbol>& symbol, const std::shared_ptr<expr>& value);

    void pop_value(const std::shared_ptr<symbol>& symbol);

    std::shared_ptr<expr> get_value(const std::shared_ptr<symbol>& symbol);
};

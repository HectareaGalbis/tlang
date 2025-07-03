
#pragma once

#include "objects.hpp"
#include <iostream>
#include <map>
#include <optional>

class packages {
private:
    std::map<std::string, std::shared_ptr<symbol>> symbols;

public:
    std::optional<std::shared_ptr<symbol>> find_symbol(const std::string& name);
    std::shared_ptr<symbol>& intern_symbol(const std::string& name);
};

extern packages package;

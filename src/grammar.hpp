
#pragma once

#include <tao/pegtl.hpp>

namespace lex {

namespace peg = tao::pegtl;

// Anything decl
struct anything;

// Terminals
struct symbol
    : peg::identifier { };

struct integer
    : peg::seq<peg::opt<peg::sor<peg::one<'+'>, peg::one<'-'>>>, peg::plus<peg::digit>> { };

struct lparen
    : peg::one<'('> { };

struct rparen
    : peg::one<')'> { };

// Mid level terms (uses terminals)
struct atom
    : peg::sor<symbol, integer> { };

struct list
    : peg::seq<lparen, peg::star<anything>, rparen> { };

// Anything impl
struct anything
    : peg::sor<peg::space, atom, list> { };

// Language
struct tlang
    : peg::seq<peg::star<anything>, peg::eolf> { };

}

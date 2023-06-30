#pragma once
#include "peg_parser/generator.h"

#include <cmath>
#include <iostream>
#include <unordered_map>

namespace tick {
template <class T = void>
class SQL {
 public:
  using VariableMap = std::unordered_map<std::string, T>;
  SQL() {
    auto& g = calculator;
    g.setSeparator(g["Whitespace"] << "[\t ]");

    g["Expression"] << "Set | Sum";
    g["Set"] << "Name '=' Sum" >> [](auto e, auto& v) {
      return v[e[0].string()] = e[1].evaluate(v);
    };
    g["Sum"] << "Add | Subtract | Product";
    g["Product"] << "Multiply | Divide | Exponent";
    g["Exponent"] << "Power | Atomic";
    g["Atomic"] << "Number | Brackets | Variable";
    g["Brackets"] << "'(' Sum ')'";
    g["Add"] << "Sum '+' Product" >> [](auto e, auto& v) {
      return e[0].evaluate(v) + e[1].evaluate(v);
    };
    g["Subtract"] << "Sum '-' Product" >> [](auto e, auto& v) {
      return e[0].evaluate(v) - e[1].evaluate(v);
    };
    g["Multiply"] << "Product '*' Exponent" >> [](auto e, auto& v) {
      return e[0].evaluate(v) * e[1].evaluate(v);
    };
    g["Divide"] << "Product '/' Exponent" >> [](auto e, auto& v) {
      return e[0].evaluate(v) / e[1].evaluate(v);
    };
    g["Power"] << "Atomic ('^' Exponent)" >> [](auto e, auto& v) {
      return pow(e[0].evaluate(v), e[1].evaluate(v));
    };
    g["Variable"] << "Name" >> [](auto e, auto& v) {
      return v[e[0].string()];
    };
    g["Name"] << "[a-zA-Z] [a-zA-Z0-9]*";
    g["Number"] << "'-'? [0-9]+ ('.' [0-9]+)?" >> [](auto e, auto&) {
      return stod(e.string());
    };

    g.setStart(g["Expression"]);
  }

  ~SQL(){};

  int exec() {

    std::cout << "Enter an expression to be evaluated.\n";

    VariableMap variables;

    while (true) {
      std::string str;
      std::cout << "> ";
      getline(std::cin, str);
      if (str == "q" || str == "quit") {
        break;
      }
      try {
        auto result = calculator.run(str, variables);
        std::cout << str << " = " << result << std::endl;
      } catch (peg_parser::SyntaxError& error) {
        auto syntax = error.syntax;
        std::cout << "  ";
        std::cout << std::string(syntax->begin, ' ');
        std::cout << std::string(syntax->length(), '~');
        std::cout << "^\n";
        std::cout << "  "
                  << "Syntax error while parsing " << syntax->rule->name
                  << std::endl;
      }
    }

    return 0;
  }

 private:
  peg_parser::ParserGenerator<T, VariableMap&> calculator;
};
}  // namespace tick

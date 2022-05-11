#include "expr.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::string s; 
    std::cout << "Enter the expression\n";
    std::cin >> s;
    auto* ast = BuildAST::build(s);
    std::cout <<"S-Expression:";
    std::cout << ast->str(ast) << std::endl;
    std::cout << ast->evaluate()<<std::endl;
    }


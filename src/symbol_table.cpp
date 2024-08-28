#include "symbol_table.hpp"
#include <stdexcept>


void SymbolTable::declareVariable(const std::string& name, VarType type){
    if(table.find(name) != table.end()){
        throw std::runtime_error("SemanticError: Variable " + name + " pahilei DECLARE garieko chha!");
    }
    table[name] = type;
}

VarType SymbolTable::lookupVariable(const std::string& name){
    if(table.find(name)==table.end()){
        throw std::runtime_error("SemanticError: Variable " + name + " DECLARE bhaisakeko chha!");
    }
    return table[name];
}
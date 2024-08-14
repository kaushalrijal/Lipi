#include "symbol_table.hpp"
#include <stdexcept>


void SymbolTable::declareVariable(const std::string& name, const std::string& type){
    if(table.find(name) != table.end()){
        throw std::runtime_error("Variable " + name + " already declared.");
    }
    table[name] = type;
}

std::string SymbolTable::lookupVariable(const std::string& name){
    if(table.find(name)==table.end()){
        throw std::runtime_error("Variable " + name + " not declared");
    }
}